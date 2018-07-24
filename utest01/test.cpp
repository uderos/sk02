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
	c.set_digit(4);
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
	EXPECT_EQ(c.get_digit(), 8);
}

TEST(CellClassTest, ErrorChecks01)
{
	Cell c;

	EXPECT_THROW(c.get_digit(), std::runtime_error);

	EXPECT_THROW(c.has_candidate(-1), std::runtime_error);
	EXPECT_THROW(c.has_candidate(NUM_DIGITS), std::runtime_error);

	EXPECT_THROW(c.set_digit(-1), std::runtime_error);
	EXPECT_THROW(c.set_digit(10), std::runtime_error);
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

	c.set_digit(0);
	exps = "    [1]    ";
	gens = c.to_string();
	EXPECT_EQ(exps.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens, exps);

	c.set_digit(5);
	exps = "    [6]    ";
	gens = c.to_string();
	EXPECT_EQ(exps.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens.size(), EXP_CELL_STR_LEN);
	EXPECT_EQ(gens, exps);
}

TEST(CellRefSetTest, Constructor)
{
	const int ROW = 1;
	const int COLUMN = 2;
	CellRefSet row_set(eCellSetType::CS_ROW, 0);

	row_set.add_cell(ROW, COLUMN);

	const cell_coords_t cell_coords{ row_set.get_cell(0) };

	EXPECT_EQ(cell_coords.rx, ROW);
	EXPECT_EQ(cell_coords.cx, COLUMN);
	EXPECT_THROW(row_set.get_cell(1), std::runtime_error);
}
