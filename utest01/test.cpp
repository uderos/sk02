#include "pch.h"
#include "sk02_lib.h"

TEST(CellClassTest, Constructor)
{
	Cell c;
	EXPECT_FALSE(c.is_solved());
	EXPECT_TRUE(c.has_candidate(0));
	EXPECT_TRUE(c.has_candidate(9));
}

TEST(CellClassTest, Set)
{
	Cell c;
	EXPECT_FALSE(c.is_solved());
	EXPECT_TRUE(c.has_candidate(0));
	c.set(4);
	EXPECT_TRUE(c.is_solved());
	EXPECT_FALSE(c.has_candidate(0));
}

TEST(CellClassTest, ClearCandidates)
{
	Cell c;

	for (int i = 0; i < 10; ++i)
		EXPECT_TRUE(c.has_candidate(i));

	for (int i = 0; i < 8; ++i)
	{
		c.clear_candidate(i);
		EXPECT_FALSE(c.is_solved());
		EXPECT_FALSE(c.has_candidate(i));
		EXPECT_TRUE(c.has_candidate(i + 1));
	}

	c.clear_candidate(8);
	EXPECT_TRUE(c.is_solved());
	EXPECT_EQ(c.get(), 9);
}

TEST(CellClassTest, ErrorChecks01)
{
	Cell c;

	EXPECT_THROW(c.get(), std::runtime_error);

	EXPECT_THROW(c.has_candidate(-1), std::runtime_error);
	EXPECT_THROW(c.has_candidate(10), std::runtime_error);

	EXPECT_THROW(c.set(-1), std::runtime_error);
	EXPECT_THROW(c.set(10), std::runtime_error);
}
