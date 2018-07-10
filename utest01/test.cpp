#include "pch.h"
#include "Cell.h"

TEST(TestCaseName, TestName)
{
	Cell c;
	EXPECT_FALSE(c.is_solved());
	EXPECT_TRUE(c.has_candidate(0));
	EXPECT_TRUE(c.has_candidate(9));
}
