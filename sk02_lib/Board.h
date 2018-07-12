#pragma once

#include "Cell.h"
#include "CellRefSet.h"

class Board
{
public:

	enum { NUM_CELL_SETS = BOARD_SIZE + BOARD_SIZE + BOARD_SIZE };

	Board();
	Board(const Board & rv);
	Board(Board && rv);

	virtual ~Board();

	Cell & operator()(const int rx, const int cx);
	CellRefSet & get_set(const int idx);

	bool is_solved() const;

	std::string to_string() const;

private:
	using cells_t = std::array<std::array<Cell, BOARD_SIZE>, BOARD_SIZE>;
	using cell_sets_t = std::vector<CellRefSet>;

	std::unique_ptr<cells_t> cells_ptr_;

	std::unique_ptr<cell_sets_t> cell_sets_ptr_;

	void validate_indexes(
		const int rx, 
		const int cx, 
		const char * file_name,
		const unsigned line_number) const;

	void create_sets();

};

