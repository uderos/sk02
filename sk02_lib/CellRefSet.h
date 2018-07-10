#pragma once

#include "common.h"
#include "Cell.h"

class CellRefSet
{
public:
	CellRefSet(const eCellSetType type, const int index);
	virtual ~CellRefSet();

private:

	using cell_ptr_t = std::array<Cell *, BOARD_SIZE>;

	const eCellSetType type_;
	const int index_;

	cell_ptr_t cell_ptr_list_;

};

