#include "pch.h"
#include "sk02_lib.h"

TEST(BoardTest, Constructor)
{
	Board b;
	EXPECT_FALSE(b.is_solved());
}

TEST(BoardTest, TestSetGeneration)
{
	Board b;
	Cell * cell_ptr_array[BOARD_SIZE][BOARD_SIZE];

	for (int rx = 0; rx < BOARD_SIZE; ++rx)
		for (int cx = 0; cx < BOARD_SIZE; ++cx)
			cell_ptr_array[rx][cx] = (&b(rx, cx));

	// test rows
	int idx = 0;
	for (int rx = 0; rx < BOARD_SIZE; ++rx)
	{
		CellRefSet & row = b.get_set(idx++);
		for (int cx = 0; cx < BOARD_SIZE; ++cx)
		{
			Cell * cell_ptr = (&row.get_cell(cx));
			EXPECT_EQ(cell_ptr, cell_ptr_array[rx][cx]);
		}
	}

	// test columns
	for (int cx = 0; cx < BOARD_SIZE; ++cx)
	{
		CellRefSet & column = b.get_set(idx++);
		for (int rx = 0; rx < BOARD_SIZE; ++rx)
		{
			Cell * cell_ptr = (&column.get_cell(rx));
			EXPECT_EQ(cell_ptr, cell_ptr_array[rx][cx]);
		}
	}

	// test groups
	const int step = BOARD_SIZE / GROUP_SIZE;
	for (int gx = 0; gx < BOARD_SIZE; ++gx)
	{
		CellRefSet & group = b.get_set(idx++);

		int i = 0;
		for (int rj = 0; rj < step; ++rj)
		{
			for (int cj = 0; cj < step; ++cj)
			{
				Cell * group_cell_ptr = (&group.get_cell(i++));

				const int rx = (3*(gx / 3)) + rj;
				const int cx =  (3*(gx % 3)) + cj;
				// std::cout << "gx=" << gx << " rx=" << rx << " cx=" << cx << std::endl;

				Cell * board_cell_ptr = cell_ptr_array[rx][cx];
				EXPECT_EQ(group_cell_ptr, board_cell_ptr);
			}
		}
	}
}
