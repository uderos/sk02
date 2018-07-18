#pragma once

class Board;			// forward declaration
class CellRefSet;		// forward declaration

class IRule
{
public:
	IRule() = default;
	virtual ~IRule() = default;

	virtual void execute(Board & board) const = 0;
	virtual void execute(Board & board, const CellRefSet & cell_set) const = 0;
};
