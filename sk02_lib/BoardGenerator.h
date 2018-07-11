#pragma once


class Board; // forward declaration

class BoardGenerator
{
public:
	BoardGenerator();
	virtual ~BoardGenerator();

	std::unique_ptr<Board> generate(const std::string & file_name) const;
	std::unique_ptr<Board> generate(const std::vector<std::string> & text) const;

private:

	std::vector<std::string> load_from_file(const std::string & file_name) const;
	void validate_text(const std::vector<std::string> & text) const;
	bool is_digit(const char c) const;
	int char_to_int(const char c) const;
	void parse_single_row(
		Board & board, 
		const int row_index, 
		const std::string & text_line) const;

};

