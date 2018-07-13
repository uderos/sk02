#pragma once

#include "common.h"

class CellRefSet; // forward declaration

class Cell
{
public:

	using cell_candidates_t = std::bitset<NUM_DIGITS>;

	Cell();
	virtual ~Cell();

	void assign_to_set(const eCellSetType type, CellRefSet * cell_set_ptr);

	bool set(const int digit);

	int get() const;

	bool is_solved() const;

	bool clear_candidate(const int digit);
	bool clear_candidate(const cell_candidates_t & target_candidates);

	bool has_candidate(const int digit) const;

	CellRefSet & get_set(const eCellSetType type);

	const cell_candidates_t & get_candidates() const;

	std::string to_string() const;

private:

	enum { NULL_DIGIT_VALUE = (-1) };

	int digit_;

	cell_candidates_t candidates_;

	std::array<CellRefSet *, NUM_CELL_SET_TYPES> set_ptr_list_;

	void validate_digit(
		const int digit, 
		const char * file_name, 
		const unsigned line_number) const;

	void set_dirty_flags();
};

