#pragma once
#define BOARDSIZE (int)24
#define  ESC    0x1B
#define BS 0x08
#define SPACE 0x20
#define CR 0x0d

enum Cell
{
	Dead,
	Living,
};

enum Arrow
{
	Up,
	UpperRight,
	Right,
	LowerRight,
	Down,
	LowerLeft,
	Left,
	UpperLeft,

	Max
};