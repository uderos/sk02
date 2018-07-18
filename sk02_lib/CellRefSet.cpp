#include "stdafx.h"
#include "Cell.h"
#include "CellRefSet.h"


CellRefSet::CellRefSet(const eCellSetType type) : type_(type)
{
}

CellRefSet::~CellRefSet()
{
}

eCellSetType CellRefSet::get_type() const
{
	return type_;
}


void CellRefSet::add_cell(const int rx, const int cx)
{
	cell_list_.emplace_back(rx, cx);

	if (cell_list_.size() > NUM_CELLS)
		throw std::runtime_error("Too many cells in set_digit");
}

cell_coords_t CellRefSet::get_cell(const int index) const
{
	validate_cell_index(index);

	return cell_coords_t(cell_list_[index].row_idx, cell_list_[index].col_idx);
}


void CellRefSet::validate_cell_index(const int index) const
{
	if ((index < 0) ||
		(std::size_t(index) >= cell_list_.size()))
	{
		std::ostringstream oss;
		oss << "Invalid cell index=" << index
			<< " at " << __FILE__ << ':' << __LINE__;
		throw std::runtime_error(oss.str());
	}

	if ((cell_list_[index].col_idx == NULL_COORDINATE) ||
		(cell_list_[index].row_idx == NULL_COORDINATE))
	{
		std::ostringstream oss;
		oss << "Invalid cell coords at index=" << index
			<< " rx=" << cell_list_[index].row_idx
			<< " cx=" << cell_list_[index].col_idx
			<< " at " << __FILE__ << ':' << __LINE__;
		throw std::runtime_error(oss.str());
	}
}


