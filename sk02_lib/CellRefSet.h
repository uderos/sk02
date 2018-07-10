#pragma once

#include "common.h"

class Cell; // forward declaration

class CellRefSet
{
public:
	CellRefSet(const eCellSetType type, const int index);
	virtual ~CellRefSet();

	void add_cell(Cell & cell);

	Cell & get_cell(const int index);

private:

	using cell_ptr_t = std::array<Cell *, BOARD_SIZE>;

	const eCellSetType type_;
	const int index_;

	cell_ptr_t cell_ptr_list_;

};

