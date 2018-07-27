#include "pch.h"
#include "lib_include.h"


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


TEST(CreativeSolver1Test, test01)
{
	auto board_ptr = f_create_board_01();

	std::cout << "BEFORE:\n" << board_ptr->to_string() << std::endl;

	CreativeSolver1 solver;

	const bool result = solver.solve(*board_ptr);

	std::cout << "AFTER:\n" << board_ptr->to_string()
		<< " result=" << result
		<< std::endl;

	EXPECT_TRUE(result);
}

