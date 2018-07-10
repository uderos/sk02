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

	EXPECT_FALSE(c.is_solved());
	EXPECT_TRUE(c.has_candidate(0));
	c.set(4);
	EXPECT_TRUE(c.is_solved());
	EXPECT_FALSE(c.has_candidate(0));
}
