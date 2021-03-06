#include "stdafx.h"
#include "Board.h"


Board::Board()
{
	create_sets();

	for (int tx = 0; tx < eCellSetType::NUM_CELL_SET_TYPES; ++tx)
		for (int idx = 0; idx < BOARD_SIZE; ++idx)
			add_dirty_set(eCellSetType(tx), idx);
}

Board::Board(const Board & rv)
{
	copy_from(rv);
}



//Board::Board(Board && rv) :
//	cells_ptr_(std::move(rv.cells_ptr_))
//{
//}

Board::~Board()
{
}

Board & Board::operator=(const Board & rv)
{
	copy_from(rv);
	return (*this);
}


void Board::copy_from(const Board & rv)
{
	cell_list_ = rv.cell_list_;

	for (int tx = 0; tx < eCellSetType::NUM_CELL_SET_TYPES; ++tx)
		for (int idx = 0; idx < BOARD_SIZE; ++idx)
			sets_[tx][idx] = std::make_unique<CellRefSet>(*rv.sets_[tx][idx]);

	for (const auto & raw_idx : rv.dirty_sets_)
		dirty_sets_.insert(raw_idx);
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
		auto new_set_ptr = std::make_unique<CellRefSet>(eCellSetType::CS_ROW, rx);

		for (int cx = 0; cx < BOARD_SIZE; ++cx)
			new_set_ptr->add_cell(rx, cx);

		sets_[eCellSetType::CS_ROW][rx] = std::move(new_set_ptr);
	}

	// Create columns
	for (int cx = 0; cx < BOARD_SIZE; ++cx)
	{
		auto new_set_ptr = std::make_unique<CellRefSet>(eCellSetType::CS_COLUMN, cx);

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
			auto new_set_ptr = std::make_unique<CellRefSet>(eCellSetType::CS_GROUP, group_idx);

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
	const bool board_solved = is_solved();

	std::ostringstream oss;
	oss << frame << std::endl;

	for (int rx = 0; rx < BOARD_SIZE; ++rx)
	{
		for (int cx = 0; cx < BOARD_SIZE; ++cx)
		{
			if (board_solved)
				oss << 1 + get_cell(rx, cx).get_digit();
			else
				oss << get_cell(rx, cx).to_string();
		}
		oss << std::endl;
	}


	oss << frame << std::endl;

	return oss.str();
}

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
		std::cout << "Processing dirty set: " << set_ptr->to_string()
			<< " n=" << dirty_sets_.size()
			<< std::endl; // UBEDEBUG
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
		std::cout << "Clear cell candidate:"
			<< " rx=" << cell_coords.rx
			<< " cx=" << cell_coords.cx
			<< " d=" << digit
			<< " u=" << cell_updated
			<< std::endl; // UBEDEBUG

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
		std::cout << "Clear cell candidates:"
			<< " rx=" << cell_coords.rx
			<< " cx=" << cell_coords.cx
			<< " c=" << target_candidates.to_string()
			<< " u=" << cell_updated
			<< std::endl; // UBEDEBUG

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
		std::cout << "Set cell digit:"
			<< " rx=" << cell_coords.rx
			<< " cx=" << cell_coords.cx
			<< " d=" << digit
			<< " u=" << cell_updated
			<< std::endl; // UBEDEBUG

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
	std::cout << "Cell updated: rx=" << rx << " cx=" << cx << std::endl; // UBEDEBUG
//	std::cout << "Updated Board:\n" << to_string() << std::endl;
	add_dirty_set(eCellSetType::CS_ROW, rx);
	add_dirty_set(eCellSetType::CS_COLUMN, cx);

	const int gx = calc_group_index(rx, cx);
	add_dirty_set(eCellSetType::CS_GROUP, gx);
}

void Board::add_dirty_set(const eCellSetType type, const int idx)
{
	const int key = (type << 16) + (idx & 0xFFFF);
	
	if (dirty_sets_.find(key) == dirty_sets_.end())
		std::cout << "New dirty set: " << CellRefSet::to_string(type, idx)
			<< " (t=" << type << " idx=" << idx << ')'
			<< " n=" << dirty_sets_.size()
			<< std::endl; // UBEDEBUG

	dirty_sets_.insert(key);


}

bool Board::is_valid() const
{
	for (int tx = 0; tx < eCellSetType::NUM_CELL_SET_TYPES; ++tx)
	{
		for (int idx = 0; idx < BOARD_SIZE; ++idx)
		{
			const bool valid_set = is_set_valid(get_set(eCellSetType(tx), idx));
			if (! valid_set)
				return false;
		}
	}

	return true;
}

bool Board::is_set_valid(const CellRefSet & cell_set) const
{
	bool is_valid = true;

	// No repeated digits
	{
		std::bitset<CellRefSet::NUM_CELLS> digits;
		for (int i = 0; is_valid && i < CellRefSet::NUM_CELLS; ++i)
		{
			const cell_coords_t cell_coords(cell_set.get_cell(i));
			const Cell & cell(get_cell(cell_coords.rx, cell_coords.cx));
			if (cell.is_solved())
			{
				if (digits.test(cell.get_digit()))
				{
					is_valid = false;
					std::cout << "Invalid cell set: " << cell_set.to_string() << std::endl;
				}
				digits.set(cell.get_digit());
			}
		}
	}

	return is_valid;
}

