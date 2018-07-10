#pragma once

#include "Cell.h"

class Board
{
public:
	Board();
	Board(const Board & rv);
	Board(Board && rv);

	virtual ~Board();

	Cell & operator()(const int rx, const int cx);

	bool is_solved() const;

private:
	using cells_t = std::array<std::array<Cell, BOARD_SIZE>, BOARD_SIZE>;

	std::unique_ptr<cells_t> cells_ptr_;

	void validate_indexes(
		const int rx, 
		const int cx, 
		const char * file_name,
		const unsigned line_number) const;


};

