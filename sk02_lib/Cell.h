#pragma once

#include "common.h"

class Cell
{
public:

	using cell_candidates_t = std::bitset<NUM_DIGITS>;

	Cell();
	virtual ~Cell();

	bool set(const int digit);

	int get() const;

	bool is_solved() const;

	bool clear_candidate(const int digit);
	bool clear_candidate(const cell_candidates_t & target_candidates);

	bool has_candidate(const int digit) const;

	const cell_candidates_t & get_candidates() const;

	std::string to_string() const;

private:

	enum { NULL_DIGIT_VALUE = (-1) };

	int digit_;

	cell_candidates_t candidates_;

	void validate_digit(
		const int digit, 
		const char * file_name, 
		const unsigned line_number) const;
};

