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
		CellRefSet & cell_set(board.get_set(idx));

		update_single_set(board, cell_set);
	}
}

void RuleUpdateCandidates::execute(Board & board, CellRefSet & cell_set) const
{
	update_single_set(board, cell_set);
}

void RuleUpdateCandidates::update_single_set(Board & board, CellRefSet & cell_set) const
{
	for (int i = 0; i < CellRefSet::NUM_CELLS; ++i)
	{
		const Cell & source_cell = cell_set.get_cell(i);

		if (source_cell.is_solved())
		{
			for (int j = 0; j < CellRefSet::NUM_CELLS; ++j)
			{
				if (j != i)
				{
					Cell & target_cell = cell_set.get_cell(j);

					if (!target_cell.is_solved())
					{
						const bool cell_updated = target_cell.clear_candidate(source_cell.get_digit());
						if (cell_updated)
							board.cell_updated_notify(target_cell);

					}
				}
			}
		}
	}
}


