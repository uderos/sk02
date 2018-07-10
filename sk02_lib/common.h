#pragma once

static const int NUM_DIGITS = 10; // 0, 1, ..., 9
static const int BOARD_SIZE = 9;
static const int BOARD_NUM_NGROUPS = BOARD_SIZE;

enum class eCellSetType
{
	ROW,
	COLUMN,
	GROUP
};

