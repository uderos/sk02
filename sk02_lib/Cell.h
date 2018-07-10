#pragma once

#include "common.h"

class CellRefSet; // forward declaration

class Cell
{
public:
	Cell();
	virtual ~Cell();

	void assign_to_set(const eCellSetType type, CellRefSet * cell_set_ptr);

	void set(const int digit);

	int get() const;

	bool is_solved() const;

	void clear_candidate(const int digit);

	bool has_candidate(const int digit) const;

	CellRefSet & get_set(const eCellSetType type);

	std::string to_string() const;

private:

	enum { NULL_DIGIT_VALUE = (-1) };

	int digit_;

	std::bitset<NUM_DIGITS> candidates_;

	std::array<CellRefSet *, NUM_CELL_SET_TYPES> set_ptr_list_;

	void validate_digit(
		const int digit, 
		const char * file_name, 
		const unsigned line_number) const;
};

