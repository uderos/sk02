#include "stdafx.h"
#include "Board.h"
#include "CellRefSet.h"
#include "SimpleSolver.h"
#include "RuleCandidateTuples.h"
#include "RuleUpdateCandidates.h"

SimpleSolver::SimpleSolver()
{
	rules_.emplace_back(std::make_unique<RuleUpdateCandidates>());
	rules_.emplace_back(std::make_unique<RuleCandidateTuples>());
}

SimpleSolver::~SimpleSolver()
{
}

bool SimpleSolver::solve(Board & board)
{
	const CellRefSet * dirty_set_ptr = board.get_next_dirty_set();

	while ((!board.is_solved()) && dirty_set_ptr)
	{
		for (auto & rule : rules_)
			rule->execute(board);

		dirty_set_ptr = board.get_next_dirty_set();
	}

	return board.is_solved();
}

