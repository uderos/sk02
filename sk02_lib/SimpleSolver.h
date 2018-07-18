#pragma once
#include "ISolver.h"

class IRule; // forward declaration;

class SimpleSolver : public ISolver
{
public:
	SimpleSolver();
	virtual ~SimpleSolver();

	virtual bool solve(Board & board);

private:
	std::vector<std::unique_ptr<IRule>> rules_;

};

