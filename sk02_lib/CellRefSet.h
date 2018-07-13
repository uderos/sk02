#pragma once

#include "common.h"

class Cell; // forward declaration

class CellRefSet
{
public:

	enum { NUM_CELLS = BOARD_SIZE };

	CellRefSet(const eCellSetType type, const int index);
	virtual ~CellRefSet();

	eCellSetType get_type() const;

	void add_cell(Cell & cell);

	const Cell & get_cell(const int index) const;
	Cell & get_cell(const int index);

private:

	using cell_ptr_t = std::array<Cell *, NUM_CELLS>;

	const eCellSetType type_;
	const int index_;

	cell_ptr_t cell_ptr_list_;

	void validate_cell_index(const int index) const;
};

