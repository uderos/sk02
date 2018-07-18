#pragma once

#include "Cell.h"
#include "CellRefSet.h"

class Board;


class Board
{
public:

	enum { NUM_CELL_SETS = BOARD_SIZE + BOARD_SIZE + BOARD_SIZE };

	Board();
	Board(const Board & rv);
	Board(Board && rv) = delete;

	virtual ~Board();

	const Cell & operator()(const int rx, const int cx) const;
	const Cell & operator()(const CellRefSet & cell_set, const int idx) const;
	const Cell & operator()(const cell_coords_t & cell_coords) const;



	const CellRefSet & get_set(const int idx) const;
	const CellRefSet & get_set(const eCellSetType type, const int idx) const;

	const CellRefSet * get_next_dirty_set();

	bool is_solved() const;

	void clear_cell_candidate(const cell_coords_t & cell_coords,
							  const int digit);
	void clear_cell_candidate(const cell_coords_t & cell_coords,
							  const Cell::cell_candidates_t & target_candidates);
	void set_cell_digit(const cell_coords_t & cell_coords,
						const int digit);

	std::string to_string() const;

private:
	enum { NUM_CELLS = BOARD_SIZE * BOARD_SIZE };

	std::array<Cell, NUM_CELLS> cell_list_;

	std::array<std::array<std::unique_ptr<CellRefSet>, BOARD_SIZE>, NUM_CELL_SET_TYPES> sets_;


	std::unordered_set<int> dirty_sets_;
//	std::set<int> dirty_sets_;

	Cell & get_cell(const int rx, const int cx);
	const Cell & get_cell(const int rx, const int cx) const;

	void validate_indexes(
		const int rx, 
		const int cx, 
		const char * file_name,
		const unsigned line_number) const;

	void create_sets();

	void process_updated_cell(const int rx, const int cx);

	int calc_group_index(const int rx, const int cx) const;

	void add_dirty_set(const eCellSetType type, const int idx);

};

