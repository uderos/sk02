#include "pch.h"
#include "lib_include.h"

//static std::unique_ptr<Board> f_create_board_00()
//{
//	const std::vector<std::string> text{
//		".........",
//		"1........",
//		".........",
//		".........",
//		".........",
//		".........",
//		".........",
//		".......9.",
//		"........."
//	};
//
//	BoardGenerator bg;
//	return bg.generate(text);
//}

static void f_test_rule(
	const int target_row,
	const int target_col,
	const int target_digit,
	Board & board,
	const bool verbose = false)
{
	if (verbose)
		std::cout << "BEFORE:\n" << board.to_string() << std::endl;

	const int target_grp = (target_col / 3) + (3 * (target_row / 3));

	{
		const auto row_set = board.get_set(eCellSetType::CS_ROW, target_row);
		board.set_cell_digit(row_set.get_cell(target_col), target_digit);
	}

	RuleUpdateCandidates rule;
	rule.execute(board);

	if (verbose)
		std::cout << "AFTER:\n" << board.to_string() << std::endl;

	for (int rx = 0; rx < BOARD_SIZE; ++rx)
	{
		const auto & row(board.get_set(eCellSetType::CS_ROW, rx));

		for (int cx = 0; cx < BOARD_SIZE; ++cx)
		{
			const int gx = (cx / 3) + (3 * (rx / 3));

			for (int d = 0; d < NUM_DIGITS; ++d)
			{
				bool expected = false;
				if (board(rx, cx).is_solved())
					expected = (d == target_digit);
				else
					expected = (d != target_digit) ||
					((rx != target_row) && (cx != target_col) && (gx != target_grp));
				const bool actual = board(rx, cx).has_candidate(d);
				EXPECT_EQ(actual, expected);
			}
		}
	}
}


TEST(RuleUpdateCandidatesTest, test01)
{

	Board board;

	const int DIGIT = 2;
	const int ROW = 1; // 2nd row
	const int COL = 2; // 3rd column
	const int GRP = 0; // 1st group

	{
		const auto & row_set(board.get_set(eCellSetType::CS_ROW, ROW));
		board.set_cell_digit(row_set.get_cell(COL), DIGIT);
	}

	std::cout << "BEFORE:\n" << board.to_string() << std::endl;

	RuleUpdateCandidates rule;
	rule.execute(board);

	std::cout << "AFTER:\n" << board.to_string() << std::endl;

	for (int rx = 0; rx < BOARD_SIZE; ++rx)
	{
		const auto & row(board.get_set(eCellSetType::CS_ROW, rx));

		for (int cx = 0; cx < BOARD_SIZE; ++cx)
		{
			const int gx = (cx / 3) + (3 * (rx / 3));

			for (int d = 0; d < NUM_DIGITS; ++d)
			{
				bool expected = false;
				if (board(rx, cx).is_solved())
					expected = (d == DIGIT);
				else
					expected = (d != DIGIT) || 
					((rx != ROW) && (cx != COL) && (gx != GRP));
				const bool actual = board(rx, cx).has_candidate(d);
				EXPECT_EQ(actual, expected);
			}
		}
	}

}

TEST(RuleUpdateCandidatesTest, test02)
{
	const bool verbose = false;
	f_test_rule(0, 0, 0, Board(), verbose);
	f_test_rule(4, 0, 1, Board(), verbose);
	f_test_rule(8, 7, 2, Board(), verbose);
	f_test_rule(1, 8, 3, Board(), verbose);
}

