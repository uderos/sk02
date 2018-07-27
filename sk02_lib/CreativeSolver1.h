#pragma once
#include "ISolver.h"

class Board;			// forward declaration
class SimpleSolver;		// forward declaration

class CreativeSolver1 :
	public ISolver
{
public:
	CreativeSolver1();
	virtual ~CreativeSolver1();

	virtual bool solve(Board & board);

private:

	struct cell_data_t
	{
		cell_coords_t coords;
		int num_candidates;

		cell_data_t(const int rx, const int cx, const int num_candidates_in) :
			coords(rx, cx), num_candidates(num_candidates_in) {};
	};

	using cell_list_t = std::vector<cell_data_t>;

	bool solve_by_guessing(Board & board, SimpleSolver & simple_solver) const;
	bool solve_by_guessing_single_cell(
		Board & board, 
		const int rx,
		const int cx,
		SimpleSolver & simple_solver) const;
	bool solve_by_guessing_single_attempt(
		Board & temp_board,
		const int rx,
		const int cx,
		const int digit,
		SimpleSolver & simple_solver) const;

	cell_list_t get_cell_list(const Board & board) const;



};


