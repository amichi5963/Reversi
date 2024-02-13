#pragma once
#include "BoardSomething.h"
#include"position.h"


#pragma warning(disable:4996)
#pragma warning(disable:26495)
class Board
{
private:
	char LivingDigit[3]{ "Å°" };
	char DeadDigit[3]{ "Å†" };

	const int BoardMax[2]{ BOARDSIZE,BOARDSIZE };
	Cell boardCells[BOARDSIZE][BOARDSIZE];
	int futureBoard[BOARDSIZE][BOARDSIZE];

public:
	void initialize();
	Cell GetCell(position pos);
	void PutCell(position pos, Cell myStone);
	void Print();
	void Copy(Board _board);
	void SetCell(position pos,Cell cell);
	void NewAgeBoard();
	Cell NewAge(position pos);
	bool ageIng(position pos, Cell myStone);
	void PlayersPut(position pos);
};