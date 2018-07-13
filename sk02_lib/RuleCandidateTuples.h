#pragma once
#include "IRule.h"
class RuleCandidateTuples :
	public IRule
{
public:
	RuleCandidateTuples();
	virtual ~RuleCandidateTuples();

	virtual bool execute(Board & board) const override;
	virtual bool execute(CellRefSet & cell_set) const override;

private:

	bool update_single_set(CellRefSet & cell_set) const;

	bool is_tuple_found(const CellRefSet & cell_set, const Cell& target_cell) const;
	void clear_tuple(CellRefSet & cell_set, Cell& target_cell) const;


};

