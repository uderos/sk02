#include "stdafx.h"
#include "Board.h"


Board::Board() :
	cells_ptr_(std::make_unique<cells_t>())
{
	create_sets();
}

Board::Board(const Board & rv) :
	cells_ptr_(std::make_unique<cells_t>(*rv.cells_ptr_))
{
	create_sets();
}

Board::Board(Board && rv) :
	cells_ptr_(std::move(rv.cells_ptr_))
{
}

Board::~Board()
{
}

Cell & Board::operator()(const int rx, const int cx)
{
	return get_cell(rx, cx);
}

Cell & Board::get_cell(const int rx, const int cx)
{
	validate_indexes(rx, cx, __FILE__, __LINE__);

	const int idx = (rx * BOARD_SIZE) + cx;
	return (*cells_ptr_)[idx];
}

const Cell & Board::get_cell(const int rx, const int cx) const
{
	validate_indexes(rx, cx, __FILE__, __LINE__);

	const int idx = (rx * BOARD_SIZE) + cx;
	return (*cells_ptr_)[idx];
}

CellRefSet & Board::get_set(const int idx)
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

CellRefSet & Board::get_set(const eCellSetType type, const int idx)
{
	return *(sets_[type][idx]);
}

bool Board::is_solved() const
{
	for (std::size_t idx = 0; idx < cells_ptr_->size(); ++idx)
			if (!(*cells_ptr_)[idx].is_solved())
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
			new_set_ptr->add_cell(get_cell(rx, cx));

		sets_[eCellSetType::CS_ROW][rx] = std::move(new_set_ptr);
	}

	// Create columns
	for (int cx = 0; cx < BOARD_SIZE; ++cx)
	{
		auto new_set_ptr = std::make_unique<CellRefSet>(eCellSetType::CS_COLUMN, cx);

		for (int rx = 0; rx < BOARD_SIZE; ++rx)
			new_set_ptr->add_cell(get_cell(rx, cx));

		sets_[eCellSetType::CS_COLUMN][cx] = std::move(new_set_ptr);
	}

	// Create groups
	const int step = BOARD_SIZE / GROUP_SIZE;
	int group_idx = 0;
	for (int rx = 0; rx < BOARD_SIZE; rx += step)
	{
		for (int cx = 0; cx < BOARD_SIZE; cx += step)
		{
			auto new_set_ptr = std::make_unique<CellRefSet>(eCellSetType::CS_GROUP, cx);

			for (int rj = 0; rj < step; ++rj)
				for (int cj = 0; cj < step; ++cj)
					new_set_ptr->add_cell(get_cell(rx + rj, cx + cj));

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

void Board::cell_updated_notify(Cell & cell)
{
	const Cell * cell_ptr(&cell);
	const Cell * first_cell_ptr = &((*cells_ptr_)[0]);
	const std::ptrdiff_t ptr_diff = (cell_ptr - first_cell_ptr);
	const unsigned int ptr_diff_uint = static_cast<unsigned int>(ptr_diff);
	const auto idx = ptr_diff_uint / sizeof(&cell);

	const int rx = idx / BOARD_SIZE;
	const int cx = idx % BOARD_SIZE;
	const int grx = (cx / GROUP_SIZE) + (BOARD_SIZE * (rx / BOARD_SIZE));

	dirty_sets.insert(sets_[eCellSetType::CS_ROW][rx].get());
}

CellRefSet * Board::get_next_dirty_set()
{
	CellRefSet * set_ptr = nullptr;

	if (!dirty_sets.empty())
	{
		set_ptr = *(dirty_sets.begin());
		dirty_sets.erase(set_ptr);
	}

	return set_ptr;
}


