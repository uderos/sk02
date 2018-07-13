#pragma once

class Board;			// forward declaration
class CellRefSet;		// forward declaration

class IRule
{
public:
	IRule() = default;
	virtual ~IRule() = default;

	virtual bool execute(Board & board) const = 0;
	virtual bool execute(CellRefSet & cell_set) const = 0;
};
