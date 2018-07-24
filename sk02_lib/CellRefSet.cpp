#include "stdafx.h"
#include "Cell.h"
#include "CellRefSet.h"


CellRefSet::CellRefSet(const eCellSetType type, const int set_idx) : 
	type_(type),
	set_index_(set_idx)
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
			<< " set " << to_string()
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
			<< " set " << to_string()
			<< " at " << __FILE__ << ':' << __LINE__;
		throw std::runtime_error(oss.str());
	}
}

std::string CellRefSet::to_string() const
{
	return to_string(type_, set_index_);
}

std::string CellRefSet::to_string(const eCellSetType type, const int set_idx)
{
	std::ostringstream oss;
	switch (type)
	{
	case eCellSetType::CS_ROW:		oss << 'R';	break;
	case eCellSetType::CS_COLUMN:	oss << 'C';	break;
	case eCellSetType::CS_GROUP:	oss << 'G';	break;
	default: oss << '?' << type << '?';			break;
	}

	oss << set_idx;

	return oss.str();
}


