#include "stdafx.h"
#include "Cell.h"
#include "CellRefSet.h"


CellRefSet::CellRefSet(const eCellSetType type, const int index) :
	type_(type), 
	index_(index)
{
	for (auto p : cell_ptr_list_)
		p = nullptr;
}

CellRefSet::~CellRefSet()
{
}

void CellRefSet::add_cell(Cell * cell_ptr)
{
	for (auto & p : cell_ptr_list_)
	{
		if (p == cell_ptr)
		{
			;
		}
		else if (!p)
		{
			p = cell_ptr;
			cell_ptr->assign_to_set(this);
			return;
		}
	}

	throw std::runtime_error("Too many cells in set");
}


