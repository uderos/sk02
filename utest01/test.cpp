#include "pch.h"
#include "sk02_lib.h"

static constexpr std::size_t EXP_CELL_STR_LEN = 11;

TEST(CellClassTest, Constructor)
{
	Cell c;
	EXPECT_FALSE(c.is_solved());
	EXPECT_TRUE(c.has_candidate(0));
	EXPECT_TRUE(c.has_candidate(NUM_DIGITS - 1));
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

	for (int i = 0; i < NUM_DIGITS; ++i)
		EXPECT_TRUE(c.has_candidate(i));

	for (int i = 0; i < NUM_DIGITS - 2; ++i)
	{
		//std::cout << "i=" << i << std::endl;
		c.clear_candidate(i);
		EXPECT_FALSE(c.is_solved());
		EXPECT_FALSE(c.has_candidate(i));
		EXPECT_TRUE(c.has_candidate(i + 1));
	}

	c.clear_candidate(7);
	EXPECT_TRUE(c.is_solved());
	EXPECT_EQ(c.get(), 8);
}

TEST(CellClassTest, ErrorChecks01)
{
	Cell c;

	EXPECT_THROW(c.get(), std::runtime_error);

	EXPECT_THROW(c.has_candidate(-1), std::runtime_error);
	EXPECT_THROW(c.has_candidate(NUM_DIGITS), std::runtime_error);

	EXPECT_THROW(c.set(-1), std::runtime_error);
	EXPECT_THROW(c.set(10), std::runtime_error);
}

TEST(CellClassTest, ToString01)
{
	Cell c;

	std::string exps, gens;

	exps = "(987654321)";
	gens = c.to_string();
	EXPECT_EQ(exps.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens, exps);

	c.clear_candidate(0);
	exps = "(98765432) ";
	gens = c.to_string();
	EXPECT_EQ(exps.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens, exps);

	c.clear_candidate(8);
	c.clear_candidate(7);
	exps = " (765432)  ";
	gens = c.to_string();
	EXPECT_EQ(exps.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens, exps);

	c.clear_candidate(1);
	c.clear_candidate(2);
	c.clear_candidate(3);
	c.clear_candidate(4);
	exps = "   (76)    ";
	gens = c.to_string();
	EXPECT_EQ(exps.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens, exps);

}

TEST(CellClassTest, ToString02)
{
	Cell c;

	std::string exps, gens;

	exps = "(987654321)";
	gens = c.to_string();
	EXPECT_EQ(exps.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens, exps);

	c.set(0);
	exps = "    [1]    ";
	gens = c.to_string();
	EXPECT_EQ(exps.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens, exps);

	c.set(5);
	exps = "    [6]    ";
	gens = c.to_string();
	EXPECT_EQ(exps.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens, exps);
}

TEST(CellRefSetTest, Constructor)
{
	Cell c;
	CellRefSet row(eCellSetType::CS_ROW, 0);

	row.add_cell(c);
	Cell & cell_ref = row.get_cell(0);
	EXPECT_EQ(&c, &cell_ref);
	EXPECT_THROW(row.get_cell(1), std::runtime_error);
}
