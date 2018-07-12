#include "stdafx.h"
#include "Cell.h"
#include "CellRefSet.h"


CellRefSet::CellRefSet(const eCellSetType type, const int index) :
	type_(type), 
	index_(index)
{
	for (auto & p : cell_ptr_list_)
		p = nullptr;
}

CellRefSet::~CellRefSet()
{
}

eCellSetType CellRefSet::get_type() const
{
	return type_;
}


void CellRefSet::add_cell(Cell & cell)
{
	Cell * cell_ptr(&cell);

	for (auto & p : cell_ptr_list_)
	{
		if (p == cell_ptr)
		{
			;
		}
		else if (!p)
		{
			p = cell_ptr;
			cell_ptr->assign_to_set(type_, this);
			return;
		}
	}

	throw std::runtime_error("Too many cells in set");
}

Cell & CellRefSet::get_cell(const int index)
{
	if ((index < 0) ||
		(std::size_t(index) >= cell_ptr_list_.size()))
	{
		std::ostringstream oss;
		oss << "Invalid cell index=" << index
			<< " at " << __FILE__ << ':' << __LINE__;
		throw std::runtime_error(oss.str());
	}

	auto cell_ptr = cell_ptr_list_[index];

	if (!cell_ptr)
	{
		std::ostringstream oss;
		oss << "No cell at index=" << index
			<< " at " << __FILE__ << ':' << __LINE__;
		throw std::runtime_error(oss.str());
	}

	return *(cell_ptr_list_[index]);
}


