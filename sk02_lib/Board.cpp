#include "stdafx.h"
#include "Board.h"


Board::Board() :
	cells_ptr_(std::make_unique<cells_t>())
{
}

Board::Board(const Board & rv) :
	cells_ptr_(std::make_unique<cells_t>(*rv.cells_ptr_))
{
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
	validate_indexes(rx, cx, __FILE__, __LINE__);

	return (*cells_ptr_)[rx][cx];
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


