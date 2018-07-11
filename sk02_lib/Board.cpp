#include "stdafx.h"
#include "Board.h"


Board::Board() :
	cells_ptr_(std::make_unique<cells_t>()),
	cell_sets_ptr_(std::make_unique<cell_sets_t>())
{
	create_sets();
}

Board::Board(const Board & rv) :
	cells_ptr_(std::make_unique<cells_t>(*rv.cells_ptr_)),
	cell_sets_ptr_(std::make_unique<cell_sets_t>())
{
	create_sets();
}

Board::Board(Board && rv) :
	cells_ptr_(std::move(rv.cells_ptr_)),
	cell_sets_ptr_(std::move(rv.cell_sets_ptr_))
{
}

Board::~Board()
{
}

Cell & Board::operator()(const int rx, const int cx)
{
	validate_indexes(rx, cx, __FILE__, __LINE__);

	return (*cells_ptr_)[rx][cx];
}

CellRefSet & Board::get_set(const int idx)
{
	if ((idx < 0) || (idx >= int(cell_sets_ptr_->size())))
	{
		std::ostringstream oss;
		oss << "Invalid set index=" << idx
			<< " at " << __FILE__ << ':' << __LINE__;
		throw std::runtime_error(oss.str());
	}

	return (*cell_sets_ptr_)[idx];
}

bool Board::is_solved() const
{
	for (int rx = 0; rx < BOARD_SIZE; ++rx)
		for (int cx = 0; cx < BOARD_SIZE; ++cx)
			if (!(*cells_ptr_)[rx][cx].is_solved())
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
		CellRefSet new_set(eCellSetType::CS_ROW, rx);

		for (int cx = 0; cx < BOARD_SIZE; ++cx)
			new_set.add_cell((*cells_ptr_)[rx][cx]);

		cell_sets_ptr_->push_back(new_set);
	}

	// Create columns
	for (int cx = 0; cx < BOARD_SIZE; ++cx)
	{
		CellRefSet new_set(eCellSetType::CS_COLUMN, cx);

		for (int rx = 0; rx < BOARD_SIZE; ++rx)
			new_set.add_cell((*cells_ptr_)[rx][cx]);

		cell_sets_ptr_->push_back(new_set);
	}

	// Create groups
	const int step = BOARD_SIZE / GROUP_SIZE;
	int group_idx = 0;
	for (int rx = 0; rx < BOARD_SIZE; rx += step)
	{
		for (int cx = 0; cx < BOARD_SIZE; cx += step)
		{
			CellRefSet new_set(eCellSetType::CS_ROW, group_idx++);

			for (int rj = 0; rj < step; ++rj)
				for (int cj = 0; cj < step; ++cj)
					new_set.add_cell((*cells_ptr_)[rx + rj][cx + cj]);

			cell_sets_ptr_->push_back(new_set);
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
			oss << (*cells_ptr_)[rx][cx].to_string();
		}
		oss << std::endl;
	}


	oss << frame << std::endl;

	return oss.str();
}

