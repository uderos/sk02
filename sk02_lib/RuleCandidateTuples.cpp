#include "stdafx.h"
#include "Board.h"
#include "RuleCandidateTuples.h"


RuleCandidateTuples::RuleCandidateTuples()
{
}


RuleCandidateTuples::~RuleCandidateTuples()
{
}

void RuleCandidateTuples::execute(Board & board) const 
{
	for (int idx = 0; idx < Board::NUM_CELL_SETS; ++idx)
	{
		const CellRefSet & cell_set(board.get_set(idx));

		update_single_set(board, cell_set);
	}
}

void RuleCandidateTuples::execute(Board & board, const CellRefSet & cell_set) const
{
	update_single_set(board, cell_set);
}


void RuleCandidateTuples::update_single_set(Board & board, const CellRefSet & cell_set) const
{
	for (int i = 0; i < CellRefSet::NUM_CELLS; ++i)
	{
		const Cell & target_cell = board(cell_set.get_cell(i));

		const bool has_tuple = is_tuple_found(board, cell_set, target_cell);

		if (has_tuple)
		{
//			std::cout << "Tuple found for cell " << i << std::endl;
			clear_tuple(board, cell_set, target_cell);
		}
	}
}

bool RuleCandidateTuples::is_tuple_found(
	const Board & board,
	const CellRefSet & cell_set,
	const Cell& target_cell) const
{
	const auto target_tuple = target_cell.get_candidates();
	int counter = 0;

	for (int i = 0; i < CellRefSet::NUM_CELLS; ++i)
	{
		const Cell & current_cell(board(cell_set.get_cell(i)));

		if ((!current_cell.is_solved()) &&
			(current_cell.get_candidates() == target_tuple))
			++counter;
	}

	const bool tuple_found = (counter > 1) &&
							 (counter < NUM_DIGITS - 1) &&
							 (counter == target_tuple.count());

	return tuple_found;
}

void RuleCandidateTuples::clear_tuple(
	Board & board,
	const CellRefSet & cell_set,
	const Cell& target_cell) const
{
	const auto target_tuple = target_cell.get_candidates();

	for (int i = 0; i < CellRefSet::NUM_CELLS; ++i)
	{
		const auto cell_coords = cell_set.get_cell(i);
		const Cell & cell(board(cell_coords));

		if (!cell.is_solved())
		{
			if (cell.get_candidates() != target_tuple)
			{
				board.clear_cell_candidate(cell_coords, target_tuple);
			}
		}
	}
}

