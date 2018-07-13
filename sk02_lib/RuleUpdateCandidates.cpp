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

bool RuleUpdateCandidates::execute(Board & board) const
{
	bool board_updated = false;
	for (int idx = 0; idx < Board::NUM_CELL_SETS; ++idx)
	{
		CellRefSet & cell_set(board.get_set(idx));

		board_updated = update_single_set(cell_set) || board_updated;
	}

	return board_updated;
}

bool RuleUpdateCandidates::execute(CellRefSet & cell_set) const
{
	const bool board_updated = update_single_set(cell_set);

	return board_updated;
}

bool RuleUpdateCandidates::update_single_set(CellRefSet & cell_set) const
{
	bool cell_updated = false;

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
						cell_updated = target_cell.clear_candidate(source_cell.get()) || cell_updated;
				}
			}
		}
	}

	return cell_updated;
}


