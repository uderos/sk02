#include "stdafx.h"
#include "Cell.h"


Cell::Cell() :
	digit_(NULL_DIGIT_VALUE)
{
	candidates_.set();

	for (auto & p : set_ptr_list_)
		p = nullptr;
}


Cell::~Cell()
{
}

void Cell::assign_to_set(
	const eCellSetType type,
	CellRefSet * cell_set_ptr)
{
	set_ptr_list_[type] = cell_set_ptr;
}


bool Cell::set(const int digit)
{
	validate_digit(digit, __FILE__, __LINE__);

	const bool cell_updated = (!is_solved());

	digit_ = digit;

	return cell_updated;
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

bool Cell::clear_candidate(const int digit)
{
	validate_digit(digit, __FILE__, __LINE__);

	const bool cell_updated = candidates_.test(digit);

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

	return cell_updated;
}

bool Cell::has_candidate(const int digit) const
{
	validate_digit(digit, __FILE__, __LINE__);

	const bool result = (is_solved() ?
		(digit == digit_) : candidates_.test(digit));

	return result;
}

CellRefSet & Cell::get_set(const eCellSetType type)
{
	auto set_ptr = set_ptr_list_[type];

	if (!set_ptr)
	{
		std::ostringstream oss;
		oss << "Unavailable cell set type=" << type
			<< " at " << __FILE__ << ":" << __LINE__;
		throw std::runtime_error(oss.str());
	}

	return (*set_ptr);
}


std::string Cell::to_string() const
{
	static constexpr std::size_t STR_LEN = 11;
	static constexpr char BLANK = ' ';

	std::ostringstream oss;

	if (is_solved())
	{
		oss << '[' << 1 + digit_ << ']';
	}
	else
	{
		oss << '(';
		for (std::size_t i = 0; i < candidates_.size(); ++i)
		{
			std::size_t d = candidates_.size() - i - 1;
			if (candidates_.test(d))
				oss << 1 + d;
		}
		oss << ')';
	}

	const std::string temp_str(std::move(oss.str()));
	const std::size_t temp_str_len = temp_str.length();
	const std::size_t nleft  = (STR_LEN - temp_str_len) / 2;
	const std::size_t nright = (STR_LEN - nleft - temp_str_len);

	const std::string result = 	std::string(nleft, BLANK) + 
								temp_str + 
								std::string(nright, BLANK);

	return result;
}


/////////////////////////////////////////////////////////////////////
// PRIVATE METHODS
/////////////////////////////////////////////////////////////////////

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

