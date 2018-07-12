#pragma once

class Board; // forward declaration

class IRule
{
public:
	IRule() = default;
	virtual ~IRule() = default;

	virtual bool execute(Board & board) const = 0;
};
