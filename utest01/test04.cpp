#include "pch.h"
#include "sk02_lib.h"
#include "../sk02_lib/RuleUpdateCandidates.h"

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


TEST(RuleUpdateCandidatesTest, test01)
{

	Board board;

	std::cout << "BEFORE:\n" << board.to_string() << std::endl;

	RuleUpdateCandidates rule;
	rule.execute(board);

	//for (int rx = 0; rx < BOARD_SIZE; ++rx)
	//	for (int cx = 0; cx < BOARD_SIZE; ++cx)
	//		for (int digit = 0; digit < BOARD_SIZE; ++cx)
	//		EXPECT_FALSE(board(rx, cx).


	std::cout << "AFTER:\n" << board.to_string() << std::endl;

}
