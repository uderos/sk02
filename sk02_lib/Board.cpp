#include "stdafx.h"
#include "Board.h"


Board::Board()
{
	create_sets();

	for (int tx = 0; tx < eCellSetType::NUM_CELL_SET_TYPES; ++tx)
		for (int idx = 0; idx < BOARD_SIZE; ++idx)
			add_dirty_set(eCellSetType(tx), idx);
}

Board::Board(const Board & rv) :
	cell_list_(rv.cell_list_)
{
	for (int tx = 0; tx < eCellSetType::NUM_CELL_SET_TYPES; ++tx)
		for (int idx = 0; idx < BOARD_SIZE; ++idx)
			sets_[tx][idx] = std::make_unique<CellRefSet>(*rv.sets_[tx][idx]);

	for (const auto & raw_idx : rv.dirty_sets_)
		dirty_sets_.insert(raw_idx);
}

//Board::Board(Board && rv) :
//	cells_ptr_(std::move(rv.cells_ptr_))
//{
//}

Board::~Board()
{
}

const Cell & Board::operator()(const int rx, const int cx) const
{
	return get_cell(rx, cx);
}

const Cell & Board::operator()(const CellRefSet & cell_set, const int idx) const
{
	const cell_coords_t cell_coords = cell_set.get_cell(idx);
	return get_cell(cell_coords.rx, cell_coords.cx);
}

const Cell & Board::operator()(const cell_coords_t & cell_coords) const
{
	return get_cell(cell_coords.rx, cell_coords.cx);
}

Cell & Board::get_cell(const int rx, const int cx)
{
	validate_indexes(rx, cx, __FILE__, __LINE__);

	const int idx = (rx * BOARD_SIZE) + cx;
	return cell_list_[idx];
}

const Cell & Board::get_cell(const int rx, const int cx) const
{
	validate_indexes(rx, cx, __FILE__, __LINE__);

	const int idx = (rx * BOARD_SIZE) + cx;
	return cell_list_[idx];
}

const CellRefSet & Board::get_set(const int idx) const
{
	if ((idx < 0) || (idx >= (BOARD_SIZE * NUM_CELL_SET_TYPES)))
	{
		std::ostringstream oss;
		oss << "Invalid set_digit index=" << idx
			<< " at " << __FILE__ << ':' << __LINE__;
		throw std::runtime_error(oss.str());
	}

	const int type_idx = idx / BOARD_SIZE;
	const int set_idx = idx % BOARD_SIZE;

	return *(sets_[type_idx][set_idx]);
}

const CellRefSet & Board::get_set(const eCellSetType type, const int idx) const
{
	return *(sets_[type][idx]);
}

bool Board::is_solved() const
{
	for (std::size_t idx = 0; idx < cell_list_.size(); ++idx)
			if (!cell_list_[idx].is_solved())
				return false;
	return true;
}

void Board::validate_indexes(
	const int rx,
	const int cx,
	const char * file_name,
	const unsigned line_number) const
{
	if ((rx < 0) || (rx >= BOARD_SIZE))
	{
		std::ostringstream oss;
		oss << "Invalid row=" << rx
			<< " at " << file_name << ':' << line_number;
		throw std::runtime_error(oss.str());
	}

	if ((cx < 0) || (cx >= BOARD_SIZE))
	{
		std::ostringstream oss;
		oss << "Invalid column=" << cx
			<< " at " << file_name << ':' << line_number;
		throw std::runtime_error(oss.str());
	}
}

void Board::create_sets()
{
	// Create rows
	for (int rx = 0; rx < BOARD_SIZE; ++rx)
	{
		auto new_set_ptr = std::make_unique<CellRefSet>(eCellSetType::CS_ROW);

		for (int cx = 0; cx < BOARD_SIZE; ++cx)
			new_set_ptr->add_cell(rx, cx);

		sets_[eCellSetType::CS_ROW][rx] = std::move(new_set_ptr);
	}

	// Create columns
	for (int cx = 0; cx < BOARD_SIZE; ++cx)
	{
		auto new_set_ptr = std::make_unique<CellRefSet>(eCellSetType::CS_COLUMN);

		for (int rx = 0; rx < BOARD_SIZE; ++rx)
			new_set_ptr->add_cell(rx, cx);

		sets_[eCellSetType::CS_COLUMN][cx] = std::move(new_set_ptr);
	}

	// Create groups
	const int step = BOARD_SIZE / GROUP_SIZE;
	int group_idx = 0;
	for (int rx = 0; rx < BOARD_SIZE; rx += step)
	{
		for (int cx = 0; cx < BOARD_SIZE; cx += step)
		{
			auto new_set_ptr = std::make_unique<CellRefSet>(eCellSetType::CS_GROUP);

			for (int rj = 0; rj < step; ++rj)
				for (int cj = 0; cj < step; ++cj)
					new_set_ptr->add_cell(rx + rj, cx + cj);

			sets_[eCellSetType::CS_GROUP][group_idx++] = std::move(new_set_ptr);
		}
	}
}

std::string Board::to_string() const
{
	const std::string frame(BOARD_SIZE, '=');
	std::ostringstream oss;

	oss << frame << std::endl;

	for (int rx = 0; rx < BOARD_SIZE; ++rx)
	{
		for (int cx = 0; cx < BOARD_SIZE; ++cx)
		{
			oss << get_cell(rx, cx).to_string();
		}
		oss << std::endl;
	}


	oss << frame << std::endl;

	return oss.str();
}

//void Board::cell_updated_notify(Cell & cell)
//{
//	const Cell * cell_ptr(&cell);
//	const Cell * first_cell_ptr = &((*cells_ptr_)[0]);
//	const std::ptrdiff_t ptr_diff = (cell_ptr - first_cell_ptr);
//	const unsigned int ptr_diff_uint = static_cast<unsigned int>(ptr_diff);
//	const auto idx = ptr_diff_uint / sizeof(&cell);
//
//	const int rx = idx / BOARD_SIZE;
//	const int cx = idx % BOARD_SIZE;
//	const int grx = (cx / GROUP_SIZE) + (BOARD_SIZE * (rx / BOARD_SIZE));
//
//	dirty_sets_.insert(sets_[eCellSetType::CS_ROW][rx].get());
//}

const CellRefSet * Board::get_next_dirty_set()
{
	const CellRefSet * set_ptr = nullptr;

	if (!dirty_sets_.empty())
	{
		const int raw_idx = *(dirty_sets_.begin());
		const int tx = (raw_idx >> 16);
		const int idx = (raw_idx & 0xFFFF);
		set_ptr = sets_[tx][idx].get();
		dirty_sets_.erase(dirty_sets_.begin());
	}

	return set_ptr;
}

void Board::clear_cell_candidate(
	const cell_coords_t & cell_coords,
	const int digit)
{
	Cell & cell = get_cell(cell_coords.rx, cell_coords.cx);

	const bool cell_updated = cell.clear_candidate(digit);

	if (cell_updated)
		process_updated_cell(cell_coords.rx, cell_coords.cx);
}

void Board::clear_cell_candidate(
	const cell_coords_t & cell_coords,
	const Cell::cell_candidates_t & target_candidates)
{
	Cell & cell = get_cell(cell_coords.rx, cell_coords.cx);

	const bool cell_updated = cell.clear_candidate(target_candidates);

	if (cell_updated)
		process_updated_cell(cell_coords.rx, cell_coords.cx);
}

void Board::set_cell_digit(
	const cell_coords_t & cell_coords,
	const int digit)
{
	Cell & cell = get_cell(cell_coords.rx, cell_coords.cx);

	const bool cell_updated = cell.set_digit(digit);

	if (cell_updated)
		process_updated_cell(cell_coords.rx, cell_coords.cx);
}

int Board::calc_group_index(const int rx, const int cx) const
{
	validate_indexes(rx, cx, __FILE__, __LINE__);
	const int gx = (cx % GROUP_SIZE) + (GROUP_SIZE * (rx / GROUP_SIZE));
	return gx;
}

void Board::process_updated_cell(const int rx, const int cx)
{
	add_dirty_set(eCellSetType::CS_ROW, rx);
	add_dirty_set(eCellSetType::CS_COLUMN, cx);

	const int gx = calc_group_index(rx, cx);
	add_dirty_set(eCellSetType::CS_GROUP, gx);
}

void Board::add_dirty_set(const eCellSetType type, const int idx)
{
	dirty_sets_.insert((type << 16) + (idx & 0xFFFF));
}

