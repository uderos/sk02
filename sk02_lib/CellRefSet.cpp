#include "stdafx.h"
#include "Cell.h"
#include "CellRefSet.h"


CellRefSet::CellRefSet(const eCellSetType type, const int index) :
	type_(type),
	index_(index),
	dirty_flag_(false)
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
			return;
		}
	}

	throw std::runtime_error("Too many cells in set");
}

const Cell & CellRefSet::get_cell(const int index) const
{
	validate_cell_index(index);

	return *(cell_ptr_list_[index]);
}

Cell & CellRefSet::get_cell(const int index)
{
	validate_cell_index(index);

	return *(cell_ptr_list_[index]);
}

void CellRefSet::set_dirty_flag()
{
	dirty_flag_ = true;
}

void CellRefSet::clear_dirty_flag()
{
	dirty_flag_ = false;
}

bool CellRefSet::get_dirty_flag() const
{
	return dirty_flag_;
}


void CellRefSet::validate_cell_index(const int index) const
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
}


