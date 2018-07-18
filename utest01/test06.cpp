#include "pch.h"
#include "sk02_lib.h"
#include "../sk02_lib/SimpleSolver.h"


static std::unique_ptr<Board> f_create_board_00()
{
	const std::vector<std::string> text{
		".........",
		"1........",
		".........",
		".........",
		".........",
		".........",
		".........",
		".......9.",
		"........."
	};

	BoardGenerator bg;
	return bg.generate(text);
}

TEST(SimpleSolverTest, test01)
{
	auto board_ptr = f_create_board_00();

	SimpleSolver solver;
	
	const bool result = solver.solve(*board_ptr);

	EXPECT_TRUE(result);
}

