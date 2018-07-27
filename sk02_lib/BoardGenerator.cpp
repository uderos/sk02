#include "stdafx.h"
#include "Board.h"
#include "BoardGenerator.h"
#include "common.h"

BoardGenerator::BoardGenerator()
{
}


BoardGenerator::~BoardGenerator()
{
}

std::unique_ptr<Board> BoardGenerator::generate(
	const std::string & file_name) const
{
	const auto text = load_from_file(file_name);

	return generate(text);
}

std::unique_ptr<Board> BoardGenerator::generate(
	const std::vector<std::string> & text) const
{
	validate_text(text);

	auto board_ptr = std::make_unique<Board>();

	for (int rx = 0; rx < int(text.size()); ++rx)
		parse_single_row(*board_ptr, rx, text[rx]);

	if (!board_ptr->is_valid())
	{
		std::cout << "BoardGenerator: invalid board:\n"
			<< board_ptr->to_string()
			<< std::endl;

		board_ptr.reset();
	}

	return board_ptr;
}

std::vector<std::string> BoardGenerator::load_from_file(const std::string & file_name) const
{
	const char COMMENT{ '"' };

	std::vector<std::string> text;

	std::ifstream ifs(file_name);
	if (!ifs)
	{
		std::ostringstream oss;
		oss << "Unable to open file: " << file_name;
		throw std::runtime_error(oss.str());
	}

	std::string line;
	while (std::getline(ifs, line))
		if ((line.size() > 0) && (line[0] != COMMENT))
			text.push_back(line);

	return text;
}

void BoardGenerator::validate_text(const std::vector<std::string> & text) const
{
	if (text.size() != std::size_t(BOARD_SIZE))
	{
		std::ostringstream oss;
		oss << "Invalid number of lines: " << text.size();
		throw std::runtime_error(oss.str());
	}

	for (const auto & s : text)
	{
		if (s.size() != BOARD_SIZE)
		{
			std::ostringstream oss;
			oss << "Invalid line length l=" << s.size()
				<< " line=" << s;;
			throw std::runtime_error(oss.str());
		}
	}
}

bool BoardGenerator::is_digit(const char c) const
{
	return ((c >= '0') && (c <= '9'));
}

int BoardGenerator::char_to_int(const char c) const
{
	return int(c - '0');
}

void BoardGenerator::parse_single_row(
	Board & board,
	const int row_index,
	const std::string & text_line) const
{
	const auto & row_set = board.get_set(eCellSetType::CS_ROW, row_index);

	for (std::size_t cx = 0; cx < text_line.size(); ++cx)
	{
		const char c = text_line[cx];
		if (is_digit(c))
			board.set_cell_digit(row_set.get_cell(cx), char_to_int(c) - 1);
	}
}
