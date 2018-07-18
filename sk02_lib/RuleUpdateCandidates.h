#pragma once
#include "IRule.h"
class RuleUpdateCandidates : public IRule
{
public:
	RuleUpdateCandidates();
	virtual ~RuleUpdateCandidates();

	virtual void execute(Board & board) const override;
	virtual void execute(Board & board, const CellRefSet & cell_set) const override;

private:

	void update_single_set(Board & board, const CellRefSet & cell_set) const;

};

