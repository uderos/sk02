#include "pch.h"
#include "sk02_lib.h"
#include "../sk02_lib/SimpleSolver.h"


static std::unique_ptr<Board> f_create_board_01()
{
	const std::vector<std::string> text{
		".4.96.7..",
		"......1.4",
		".87.43...",
		"6....13..",
		".79...84.",
		"..18....5",
		"...67.91.",
		"9.3......",
		"..4.89.5."
	};

	BoardGenerator bg;
	return bg.generate(text);
}

static std::unique_ptr<Board> f_create_board_02()
{
	const std::vector<std::string> text{
		"54.8..6.9",
		"....6....",
		"...9.7.28",
		".31....8.",
		".5.7.2.1.",
		".9....53.",
		"61.3.5...",
		"....2....",
		"9.7..1.45",
	};

	BoardGenerator bg;
	return bg.generate(text);
}

TEST(SimpleSolverTest, test01)
{
	auto board_ptr = f_create_board_01();

	std::cout << "BEFORE:\n" << board_ptr->to_string() << std::endl;

	SimpleSolver solver;
	
	const bool result = solver.solve(*board_ptr);

	std::cout << "AFTER:\n" << board_ptr->to_string() 
		<< " result=" << result
		<< std::endl;

	EXPECT_TRUE(result);
}

TEST(SimpleSolverTest, test02)
{
	auto board_ptr = f_create_board_02();

	std::cout << "BEFORE:\n" << board_ptr->to_string() << std::endl;

	SimpleSolver solver;

	const bool result = solver.solve(*board_ptr);

	std::cout << "AFTER:\n" << board_ptr->to_string()
		<< " result=" << result
		<< std::endl;

	EXPECT_TRUE(result);
}

