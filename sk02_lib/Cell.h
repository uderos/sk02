#pragma once

#include "common.h"

class Cell
{
public:
	Cell();
	virtual ~Cell();

	void set(const int digit);

	int get() const;

	bool is_solved() const;

	void clear_candidate(const int digit);

	bool has_candidate(const int digit) const;

	std::string to_string() const;

private:

	enum { NULL_DIGIT_VALUE = (-1) };

	int digit_;

	std::bitset<NUM_DIGITS> candidates_;

	void validate_digit(
		const int digit, 
		const char * file_name, 
		const unsigned line_number) const;
};

