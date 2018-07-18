#pragma once

class Board; // forward declaration

class ISolver
{
public:
	ISolver() = default;
	virtual ~ISolver() = default;

	virtual bool solve(Board & board) = 0;
};

