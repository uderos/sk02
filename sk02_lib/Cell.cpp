#include "stdafx.h"
#include "Cell.h"


Cell::Cell() :
	digit_(NULL_DIGIT_VALUE)
{
	candidates_.set();
}


Cell::~Cell()
{
}

void Cell::set(const int digit)
{
	validate_digit(digit, __FILE__, __LINE__);

	digit_ = digit;
}

int Cell::get() const
{
	if (! is_solved())
		throw std::runtime_error("Digit not available");

	return digit_;
}

bool Cell::is_solved() const
{
	return (digit_ != NULL_DIGIT_VALUE);
}

void Cell::clear_candidate(const int digit)
{
	validate_digit(digit, __FILE__, __LINE__);

	candidates_.reset(digit);

	if (!is_solved())
	{
		if (!candidates_.any())
			throw std::runtime_error("No candidates left");

		if (candidates_.count() == 1)
		{
			for (std::size_t d = 0; d < candidates_.size(); ++d)
			{
				if (candidates_.test(d))
				{
					set(d);
					break;
				}
			}
		}
	}
}

bool Cell::has_candidate(const int digit) const
{
	validate_digit(digit, __FILE__, __LINE__);

	const bool result = (is_solved() ?
		(digit == digit_) : candidates_.test(digit));

	return result;
}


std::string Cell::to_string() const
{
	std::ostringstream oss;

	if (is_solved())
	{
		oss << '[' << digit_ << ']';
	}
	else
	{
		oss << '(' << candidates_.to_string() << ')';
	}

	return oss.str();
}

void Cell::validate_digit(
	const int digit,
	const char * file_name,
	const unsigned line_number) const
{
	if ((digit < 0) || (digit >= NUM_DIGITS))
	{
		std::ostringstream oss;
		oss << "Invalid Digit: " << digit
			<< " at " << file_name
			<< ":" << line_number;
		throw std::runtime_error(oss.str());
	}
}

