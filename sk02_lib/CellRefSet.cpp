#include "stdafx.h"
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
