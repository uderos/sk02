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

	std::cout << b.to_string() << std::endl;

	EXPECT_TRUE(b(0, 0).is_solved());
	EXPECT_EQ(b(0, 0).get(), 1);
}
