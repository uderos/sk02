#include "stdafx.h"
#include "common.h"
#include "Board.h"
#include "RuleUpdateCandidates.h"


RuleUpdateCandidates::RuleUpdateCandidates()
{
}


RuleUpdateCandidates::~RuleUpdateCandidates()
{
}

void RuleUpdateCandidates::execute(Board & board) const
{
	for (int idx = 0; idx < Board::NUM_CELL_SETS; ++idx)
	{
		const CellRefSet & cell_set(board.get_set(idx));

		update_single_set(board, cell_set);
	}
}

void RuleUpdateCandidates::execute(Board & board, const CellRefSet & cell_set) const
{
	update_single_set(board, cell_set);
}

void RuleUpdateCandidates::update_single_set(Board & board, const CellRefSet & cell_set) const
{
	for (int i = 0; i < CellRefSet::NUM_CELLS; ++i)
	{
		const Cell & source_cell = board(cell_set.get_cell(i));

		if (source_cell.is_solved())
		{
			const int source_cell_digit = source_cell.get_digit();

			for (int j = 0; j < CellRefSet::NUM_CELLS; ++j)
			{
				if (j != i)
				{
					const auto target_cell_coords = cell_set.get_cell(j);

					if (!board(target_cell_coords).is_solved())
						board.clear_cell_candidate(target_cell_coords, source_cell_digit);
				}
			}
		}
	}
}


