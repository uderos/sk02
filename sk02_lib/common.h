#pragma once

static const int NUM_DIGITS = 9; // 1->9 (UI), 0->9 (internals)
static const int BOARD_SIZE = 9;
// static const int BOARD_NUM_NGROUPS = BOARD_SIZE;
static const int GROUP_SIZE = 3;
static const int BOARD_NUM_GROUPS = 9;


enum eCellSetType
{
	CS_ROW,
	CS_COLUMN,
	CS_GROUP,
	NUM_CELL_SET_TYPES
};

struct cell_coords_t
{
	int rx;
	int cx;
	cell_coords_t(const int rx_in, const int cx_in) : rx(rx_in), cx(cx_in) {};
};



