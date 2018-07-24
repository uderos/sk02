#pragma once

#include "common.h"

class Cell; // forward declaration

class CellRefSet
{
public:

	enum { NUM_CELLS = BOARD_SIZE };

	CellRefSet(const eCellSetType type, const int set_idx);
	virtual ~CellRefSet();

	eCellSetType get_type() const;

	void add_cell(const int rx, const int cx);

	cell_coords_t get_cell(const int index) const;

	std::string to_string() const;

	static std::string to_string(const eCellSetType type, const int set_idx);

private:

	enum { NULL_COORDINATE = (-1) };

	struct cell_data_t
	{
		int row_idx;
		int col_idx;
		cell_data_t() : row_idx(NULL_COORDINATE), col_idx(NULL_COORDINATE) {};
		cell_data_t(const int rx, const int cx) : row_idx(rx), col_idx(cx) {};
	};

	std::vector<cell_data_t> cell_list_;

	const eCellSetType type_;

	const int set_index_;

	void validate_cell_index(const int index) const;
};

