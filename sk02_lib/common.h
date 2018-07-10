#pragma once

static const int NUM_DIGITS = 10; // 0, 1, ..., 9
static const int BOARD_SIZE = 9;
static const int BOARD_NUM_NGROUPS = BOARD_SIZE;

enum eCellSetType
{
	CS_ROW,
	CS_COLUMN,
	CS_GROUP,
	NUM_CELL_SET_TYPES
};

