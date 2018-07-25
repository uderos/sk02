#include "stdafx.h"
#include "Application.h"
#include "Board.h"
#include "BoardGenerator.h"
#include "SimpleSolver.h"


Application::Application()
{
}


void Application::Run(const std::string & input_file_name)
{
	try
	{
		run_exec(input_file_name);
	}
	catch (const std::exception & exh)
	{
		std::cout << "FATAL EXCEPTION: " << exh.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "UNRECOGNIZED FATAL EXCEPTION" << std::endl;
	}
}


Application::~Application()
{
}

void Application::run_exec(const std::string & input_file_name)
{
	BoardGenerator board_generator;

	auto board_ptr = board_generator.generate(input_file_name);

	if (!board_ptr)
	{
		std::ostringstream oss;
		oss << "Unable to load board from file: " << input_file_name;
		throw std::runtime_error(oss.str());
	}

	std::cout << "BEFORE:\n" << board_ptr->to_string() << std::endl;

	SimpleSolver solver;
	const bool is_solved = solver.solve(*board_ptr);

	std::cout << "AFTER:\n" << board_ptr->to_string() << std::endl;

	if (is_solved)
		std::cout << "== Board Solved ==" << std::endl;
	else
		std::cout << "## Board NOT Solved ##" << std::endl;

}

