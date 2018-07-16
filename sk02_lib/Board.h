#pragma once

#include "Cell.h"
#include "CellRefSet.h"

class Board;


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
	CellRefSet & get_set(const eCellSetType type, const int idx);

	CellRefSet * get_next_dirty_set();

	bool is_solved() const;

	void cell_updated_notify(Cell & cell);

	std::string to_string() const;

private:
	enum { NUM_CELLS = BOARD_SIZE * BOARD_SIZE };

	using cells_t = std::array<Cell, NUM_CELLS>;

	std::unique_ptr<cells_t> cells_ptr_;

	std::array<std::array<std::unique_ptr<CellRefSet>, BOARD_SIZE>, NUM_CELL_SET_TYPES> sets_;

	std::unordered_set<CellRefSet *> dirty_sets;

	Cell & get_cell(const int rx, const int cx);
	const Cell & get_cell(const int rx, const int cx) const;

	void validate_indexes(
		const int rx, 
		const int cx, 
		const char * file_name,
		const unsigned line_number) const;

	void create_sets();

};

