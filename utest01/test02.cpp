#include "pch.h"
#include "lib_include.h"

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
		const CellRefSet & row_set = b.get_set(eCellSetType::CS_ROW, rx);

		for (int cx = 0; cx < BOARD_SIZE; ++cx)
		{
			const cell_coords_t cell_coords = row_set.get_cell(cx);
			EXPECT_EQ(cell_coords.rx, rx);
			EXPECT_EQ(cell_coords.cx, cx);
		}
	}

	// test columns
	for (int cx = 0; cx < BOARD_SIZE; ++cx)
	{
		const CellRefSet & column_set = b.get_set(eCellSetType::CS_COLUMN, cx);
		for (int rx = 0; rx < BOARD_SIZE; ++rx)
		{
			const cell_coords_t cell_coords = column_set.get_cell(rx);
			EXPECT_EQ(cell_coords.rx, rx);
			EXPECT_EQ(cell_coords.cx, cx);
		}
	}

	// test groups
	const int step = BOARD_SIZE / GROUP_SIZE;
	for (int gx = 0; gx < BOARD_SIZE; ++gx)
	{
		const CellRefSet & group_set = b.get_set(eCellSetType::CS_GROUP, gx);

		int cell_idx = 0;
		for (int rj = 0; rj < step; ++rj)
		{
			for (int cj = 0; cj < step; ++cj)
			{
				const int rx = (3 * (gx / 3)) + rj;
				const int cx = (3 * (gx % 3)) + cj;
				// std::cout << "gx=" << gx << " rx=" << rx << " cx=" << cx << std::endl;

				const cell_coords_t cell_coords = group_set.get_cell(cell_idx++);
				EXPECT_EQ(cell_coords.rx, rx);
				EXPECT_EQ(cell_coords.cx, cx);

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
			b.set_cell_digit(cell_coords_t(rx, cx), 1);
		}
	}

	EXPECT_TRUE(b.is_solved());
}
