#include "pch.h"
#include "sk02_lib.h"

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
				EXPECT_EQ(b(rx, cx).get(), int(text[rx][cx] - '0'));
			}
		}
	}
}
