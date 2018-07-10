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

/////////////////////////////////////////////////////////////////////
// PRIVATE METHODS
/////////////////////////////////////////////////////////////////////

std::string Cell::to_string() const
{
	static constexpr std::size_t str_len = 12;
	static constexpr char BLANK = ' ';

	std::ostringstream oss;

	if (is_solved())
	{
		oss << '[' << digit_ << ']';
	}
	else
	{
		oss << '(';
		for (std::size_t i = 0; i < candidates_.size(); ++i)
		{
			std::size_t d = candidates_.size() - i - 1;
			if (candidates_.test(d))
				oss << d;
		}
		oss << ')';
	}

	const std::string temp_str(std::move(oss.str()));
	const std::size_t temp_str_len = temp_str.length();
	const std::size_t nleft  = (str_len - temp_str_len) / 2;
	const std::size_t nright = (str_len - nleft - temp_str_len);

	const std::string result = 	std::string(nleft, BLANK) + 
								temp_str + 
								std::string(nright, BLANK);
	return result;
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

