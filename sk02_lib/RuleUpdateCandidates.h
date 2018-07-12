#pragma once
#include "IRule.h"
class RuleUpdateCandidates : public IRule
{
public:
	RuleUpdateCandidates();
	virtual ~RuleUpdateCandidates();

	virtual bool execute(Board & board) const override;

private:

	bool update_single_set(CellRefSet & cell_set) const;

};

