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

	const cell_list_t cell_list = get_cell_list(board);

	for (const auto & cell_info : cell_list)
	{
		const bool is_solved = solve_by_guessing_single_cell(
			board, cell_info.coords.rx, cell_info.coords.cx, simple_solver);

		if (is_solved)
			return true;
	}

	return false;
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
		is_solved = simple_solver.solve(temp_board) && 
					temp_board.is_valid();
	}
	catch (const std::exception & exh)
	{
		std::cout << "Creative Solver1: Exception: " << exh.what() << std::endl;
		is_solved = false;
	}

	return is_solved;
}

CreativeSolver1::cell_list_t 
CreativeSolver1::get_cell_list(const Board & board) const
{
	cell_list_t cell_list;

	for (int rx = 0; rx < BOARD_SIZE; ++rx)
	{
		for (int cx = 0; cx < BOARD_SIZE; ++cx)
		{
			const Cell & cell(board(rx, cx));

			if (!cell.is_solved())
				cell_list.emplace_back(rx, cx, cell.get_candidates().count());
		}
	}

	auto sort_fn = [](const cell_data_t & a, const cell_data_t & b) -> bool {
		return (a.num_candidates < b.num_candidates);
	};
	std::sort(cell_list.begin(), cell_list.end(), sort_fn);

	//for (const auto & p : cell_list)
	//	std::cout << "CELL LIST:"
	//	<< " rx=" << p.coords.rx
	//	<< " cx=" << p.coords.cx
	//	<< " nc=" << p.num_candidates
	//	<< " " << board(p.coords.rx, p.coords.cx).get_candidates().to_string()
	//	<< std::endl;

	return cell_list;
}



