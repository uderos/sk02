#include "pch.h"
#include "sk02_lib.h"
#include "../sk02_lib/RuleCandidateTuples.h"

TEST(RuleCandidatesTuplesTest, test01)
{
	Board board;

	const int ROW = 0;	// 1st row
	const int GRP = 0;	// 1st group
	const int DIGIT1 = 2;
	const int DIGIT2 = 4;

	const int COL1 = 0;
	const int COL2 = 1;
	for (int d = 0; d < NUM_DIGITS; ++d)
		if ((d != DIGIT1) && (d != DIGIT2))
		{
			board(ROW, COL1).clear_candidate(d);
			board(ROW, COL2).clear_candidate(d);
		}

	std::cout << "BEFORE:\n" << board.to_string() << std::endl;

	RuleCandidateTuples rule;
	rule.execute(board);

	std::cout << "AFTER:\n" << board.to_string() << std::endl;

	Cell::cell_candidates_t tuple1;
	tuple1.set(DIGIT1);
	tuple1.set(DIGIT2);

	Cell::cell_candidates_t tuple2;
	tuple2.set();
	tuple2.reset(DIGIT1);
	tuple2.reset(DIGIT2);

	Cell::cell_candidates_t tuple3;
	tuple3.set();

	for (int rx = 0; rx < BOARD_SIZE; ++rx)
	{
		for (int cx = 0; cx < BOARD_SIZE; ++cx)
		{
			const int gx = (cx / 3) + (3 * (rx / 3));

			Cell::cell_candidates_t expected_tuple = tuple3;
			if ((rx == ROW) && ((cx == COL1) || (cx == COL2)))
				expected_tuple = tuple1;
			else if ((rx == ROW) || (gx == GRP))
				expected_tuple = tuple2;

//			std::cout << "\n R=" << rx << " C=" << cx << " G=" << gx
//				<< " E=" << expected_tuple << std::endl;
				
			const auto actual_tuple = board(rx, cx).get_candidates();
			EXPECT_EQ(actual_tuple, expected_tuple);
		}
	}
}

TEST(RuleCandidatesTuplesTest, test02)
{
	Board board;

	const int DIGIT = 2;
	const int ROW = 0;	// 1st row
	const int GRP = 0;	// 1st group
	const int DIGIT1 = 2;
	const int DIGIT2 = 4;
	const int DIGIT3 = 6;

	const int COL1 = 1;
	const int COL2 = 4;
	const int COL3 = 7;
	for (int d = 0; d < NUM_DIGITS; ++d)
		if ((d != DIGIT1) && (d != DIGIT2) && (d != DIGIT3))
		{
			board(ROW, COL1).clear_candidate(d);
			board(ROW, COL2).clear_candidate(d);
			board(ROW, COL3).clear_candidate(d);
		}

	std::cout << "BEFORE:\n" << board.to_string() << std::endl;

	RuleCandidateTuples rule;
	rule.execute(board);

	std::cout << "AFTER:\n" << board.to_string() << std::endl;

	Cell::cell_candidates_t tuple1;
	tuple1.set(DIGIT1);
	tuple1.set(DIGIT2);
	tuple1.set(DIGIT3);

	Cell::cell_candidates_t tuple2;
	tuple2.set();
	tuple2.reset(DIGIT1);
	tuple2.reset(DIGIT2);
	tuple2.reset(DIGIT3);

	Cell::cell_candidates_t tuple3;
	tuple3.set();

	for (int rx = 0; rx < BOARD_SIZE; ++rx)
	{
		for (int cx = 0; cx < BOARD_SIZE; ++cx)
		{
			const int gx = (cx / 3) + (3 * (rx / 3));

			Cell::cell_candidates_t expected_tuple = tuple3;
			if ((rx == ROW) && ((cx == COL1) || (cx == COL2) || (cx == COL3)))
				expected_tuple = tuple1;
			else if ((rx == ROW) /*|| (gx == GRP)*/ )
				expected_tuple = tuple2;

//			std::cout << "\n R=" << rx << " C=" << cx << " G=" << gx
//						<< " E=" << expected_tuple << std::endl;

			const auto actual_tuple = board(rx, cx).get_candidates();
			EXPECT_EQ(actual_tuple, expected_tuple);
		}
	}
}



