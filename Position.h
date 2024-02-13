#pragma once

#include <stdio.h>
#include "BoardSomething.h"

class position {
public:
	int x; int y;
	void Normalize(void) {
		if (x < 0) { x = BOARDSIZE - 1; }
		else if (x >= BOARDSIZE) { x = 0; }
		if (y < 0) { y = BOARDSIZE - 1; }
		else if (y >= BOARDSIZE) { y = 0; }
	};
	void add(position ad) {
		x += ad.x;
		y += ad.y;
	};

	void addArrow(Arrow me)
	{
		position position{ 0,0 };
		switch (me)
		{
		case Right:
			position.x = 1;
			position.y = 0;
			break;

		case Left:
			position.x = -1;
			position.y = 0;
			break;

		case Down:
			position.x = 0;
			position.y = 1;
			break;

		case Up:
			position.x = 0;
			position.y = -1;
			break;

		case UpperRight:
			position.x = 1;
			position.y = -1;
			break;

		case LowerRight:
			position.x = 1;
			position.y = 1;
			break;

		case UpperLeft:
			position.x = -1;
			position.y = -1;
			break;

		case LowerLeft:
			position.x = -1;
			position.y = 1;
			break;
		default:
			position.x = 0;
			position.y = 0;
			break;
		}
		this->add(position);
	}
};
