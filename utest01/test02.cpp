#include "pch.h"
#include "sk02_lib.h"

TEST(BoardTest, Constructor)
{
	Board b;
	EXPECT_FALSE(b.is_solved());
}

static void f_test_board_sets(Board & b)
{
	// test rows
	for (int rx = 0; rx < BOARD_SIZE; ++rx)
	{
		CellRefSet & row = b.get_set(eCellSetType::CS_ROW, rx);
		for (int cx = 0; cx < BOARD_SIZE; ++cx)
		{
			Cell * cell_ptr = (&row.get_cell(cx));
			EXPECT_EQ(cell_ptr, &b(rx, cx));
		}
	}

	// test columns
	for (int cx = 0; cx < BOARD_SIZE; ++cx)
	{
		CellRefSet & column = b.get_set(eCellSetType::CS_COLUMN, cx);
		for (int rx = 0; rx < BOARD_SIZE; ++rx)
		{
			Cell * cell_ptr = (&column.get_cell(rx));
			EXPECT_EQ(cell_ptr, &b(rx, cx));
		}
	}

	// test groups
	const int step = BOARD_SIZE / GROUP_SIZE;
	for (int gx = 0; gx < BOARD_SIZE; ++gx)
	{
		CellRefSet & group = b.get_set(eCellSetType::CS_GROUP, gx);

		int cell_idx = 0;
		for (int rj = 0; rj < step; ++rj)
		{
			for (int cj = 0; cj < step; ++cj)
			{
				Cell * group_cell_ptr = (&group.get_cell(cell_idx++));

				const int rx = (3 * (gx / 3)) + rj;
				const int cx = (3 * (gx % 3)) + cj;
				// std::cout << "gx=" << gx << " rx=" << rx << " cx=" << cx << std::endl;

				Cell * board_cell_ptr = &b(rx, cx);
				EXPECT_EQ(group_cell_ptr, board_cell_ptr);
			}
		}
	}
}

TEST(BoardTest, TestSetGeneration)
{
	Board b;

	f_test_board_sets(b);
}

TEST(BoardTest, TestCopy)
{
	Board * b1_ptr = new Board;
	f_test_board_sets(*b1_ptr);

	Board * b2_ptr = new Board(*b1_ptr);
	delete b1_ptr;
	b1_ptr = nullptr;
	f_test_board_sets(*b2_ptr);
}

TEST(BoardTest, IsSolved)
{
	Board b;
	EXPECT_FALSE(b.is_solved());

	for (int rx = 0; rx < BOARD_SIZE; ++rx)
	{
		for (int cx = 0; cx < BOARD_SIZE; ++cx)
		{
			EXPECT_FALSE(b.is_solved());
			b(rx, cx).set_digit(1);
		}
	}

	EXPECT_TRUE(b.is_solved());
}
