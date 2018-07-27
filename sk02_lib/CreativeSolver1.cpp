#include "stdafx.h"
#include "Board.h"
#include "common.h"
#include "CreativeSolver1.h"
#include "SimpleSolver.h"


CreativeSolver1::CreativeSolver1()
{
}


CreativeSolver1::~CreativeSolver1()
{
}

bool CreativeSolver1::solve(Board & board)
{
	SimpleSolver simple_solver;

	bool is_solved = simple_solver.solve(board);

	if (!is_solved)
		is_solved = solve_by_guessing(board, simple_solver);

	return is_solved;
}

bool CreativeSolver1::solve_by_guessing(
	Board & board, 
	SimpleSolver & simple_solver) const
{
	std::cout << "UBEDEBUG GUESSING"
		<< " - starting from:\n" << board.to_string() 
		<< std::endl;

	bool is_solved = board.is_solved();

	for (int rx = 0; (!is_solved) && (rx < BOARD_SIZE); ++rx)
	{
		for (int cx = 0; (!is_solved) && (cx < BOARD_SIZE); ++cx)
		{
			is_solved = is_solved || 
						solve_by_guessing_single_cell(board, rx, cx, simple_solver);
		}
	}

	return is_solved;
}

bool CreativeSolver1::solve_by_guessing_single_cell(
	Board & board,
	const int rx,
	const int cx,
	SimpleSolver & simple_solver) const
{
	bool is_solved = false;

	const Cell & cell(board(rx, cx));
	auto candidates = cell.get_candidates();

	for (int d = 0; (!is_solved) && (d < NUM_DIGITS); ++d)
	{
		if (candidates.test(d))
		{
			Board temp_board(board);

			is_solved = solve_by_guessing_single_attempt(
				temp_board, rx, cx, d, simple_solver);

			if (is_solved)
				board = temp_board;
		}
	}

	return is_solved;
}

bool CreativeSolver1::solve_by_guessing_single_attempt(
	Board & temp_board,
	const int rx,
	const int cx,
	const int digit,
	SimpleSolver & simple_solver) const
{
	bool is_solved = false;

	try
	{
		std::cout << "UBEDEBUG Try solving setting"
			<< " rx=" << rx << " cx=" << cx 
			<< " to " << 1+digit 
			<< std::endl;

		temp_board.clear_cell_candidate(cell_coords_t(rx, cx), digit);
		is_solved = simple_solver.solve(temp_board);
	}
	catch (const std::exception & exh)
	{
		std::cout << "Creative Solver1: Exception: " << exh.what() << std::endl;
		is_solved = false;
	}

	return is_solved;
}



