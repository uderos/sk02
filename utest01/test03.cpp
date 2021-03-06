#include "pch.h"
#include "lib_include.h"

TEST(BoardGeneratorTest, Constructor)
{
	BoardGenerator bg;
}

TEST(BoardGeneratorTest, FromString01)
{
	const std::vector<std::string> text{
		"1.3.5.7.9",
		".........",
		".2.4.6.8.",
		"123456789",
		".........",
		".........",
		".........",
		".........",
		"987654321"
	};

	BoardGenerator bg;
	auto board_ptr = bg.generate(text);

	ASSERT_NE(board_ptr, nullptr);

	Board & b(*board_ptr);

//	std::cout << b.to_string() << std::endl;

	for (int rx = 0; rx < 3; ++rx)
	{
		for (int cx = 0; cx < 3; ++cx)
		{
			if (text[rx][cx] == '.')
			{
				EXPECT_FALSE(b(rx, cx).is_solved());
			}
			else
			{
				EXPECT_TRUE(b(rx, cx).is_solved());
				const int expected_value = int(text[rx][cx] - '0') - 1;
				const int actual_value = b(rx, cx).get_digit();
				EXPECT_EQ(actual_value, expected_value);
			}
		}
	}
}

TEST(BoardTest, board_test_01)
{
	Board b;
	EXPECT_FALSE(b.is_solved());
	EXPECT_TRUE(b.is_valid());

	Cell::cell_candidates_t candidates;
	candidates.set();
	candidates.reset(0);
	b.clear_cell_candidate(cell_coords_t(0, 0), candidates);
	EXPECT_TRUE(b.is_valid());

	{
		Board b1(b);
		EXPECT_TRUE(b1.is_valid());
		b1.clear_cell_candidate(cell_coords_t(0, 8), candidates);
		EXPECT_FALSE(b1.is_valid());
	}

	{
		Board b1(b);
		EXPECT_TRUE(b1.is_valid());
		b1.clear_cell_candidate(cell_coords_t(8, 0), candidates);
		EXPECT_FALSE(b1.is_valid());
	}

	{
		Board b1(b);
		EXPECT_TRUE(b1.is_valid());
		b.clear_cell_candidate(cell_coords_t(1, 1), candidates);
		EXPECT_FALSE(b.is_valid());
	}


}

