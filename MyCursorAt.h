#pragma once
#include "position.h"

class MyCursorAt
{
public:
	static void CursorAt(position pos) {
		int xpos = pos.y * 2 + 3;
		int ypos = pos.x + 3;
		printf("%c[%d;%dH", ESC, ypos, xpos);
	}

};