#include "BOARD.h"
#include "BoardSomething.h"
#include "position.h"
#include"MyCursorAt.h"
#include <iostream>
#include <conio.h>

enum COLORS {
	BLACK, RED, GREEN, BROWN,
	BLUE, MAGENTA, CYAN, LIGHTGRAY,
	DARKGRAY, LIGHTRED, LIGHTGREEN, YELLOW,
	LIGHTBLUE, LIGHTMAGENTA, LIGHTCYAN, WHITE
};

int colorList[] = { BLACK,MAGENTA,LIGHTMAGENTA,BROWN,YELLOW };
/* 表示色設定 */
void textattr(int c)
{
	int fc = (c & 0x7) + 30;
	int bc = (c >> 4 & 0x7) + 40;
	cprintf("\x1b[0m");
	if (c & 0x8) cprintf("\x1b[1m");
	if (c & 0x80) cprintf("\x1b[5m");
	cprintf("\x1b[%d;%dm", fc, bc);
}

using namespace std;

void Board::initialize() {
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			boardCells[i][j] = Dead;
			futureBoard[i][j] = 0;
		}
	}
}
Cell Board::GetCell(position pos) {
	return boardCells[pos.x][pos.y];
}
void Board::PutCell(position pos, Cell myStone)
{
	SetCell(pos, myStone);
	int myFuture = futureBoard[pos.x][pos.y];
	MyCursorAt::CursorAt(pos);

	printf("%c[>5h", ESC);   /* カーソル消去 */

	if (myStone == Living) {
		textattr(colorList[myFuture] | colorList[myFuture] << 4);
		cout << LivingDigit;
	}
	else {
		textattr(colorList[myFuture] | BLACK << 4);
		cout << DeadDigit;
	}
	textattr(WHITE | BLACK << 4);

	printf("%c[>5h", ESC);   /* カーソル消去 */
}
void Board::Print()
{
	system("cls");

	printf("%c[%d;%dH", ESC, 0, 0);
	cout << "\n" << "ライフゲーム　上下左右がループします";
	cout << "\n";
	for (int i = 0; i < BoardMax[0]; i++)
	{
		cout << "　";

		for (int j = 0; j < BoardMax[1]; j++)
		{
			PutCell({ i,j }, Dead);
		}
		cout << "\n";
	}

	cout << "スペースで配置/削除　エンターで開始　バックスペースで全消し\n動作中、何かキーを押すと一時停止してセルを配置できます\nescを押すと終了します";
}
void Board::Copy(Board _board) {
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			boardCells[i][j] = _board.boardCells[i][j];
		}
	}
}
void Board::SetCell(position pos, Cell myStone) {
	boardCells[pos.x][pos.y] = myStone;
}
void Board::NewAgeBoard() {
	Board newboard;
	newboard.Copy(*this);
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int m = 0; m < BOARDSIZE; m++)
		{
			newboard.SetCell({ i,m }, NewAge({ i,m }));
		}
	}
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int m = 0; m < BOARDSIZE; m++)
		{
			if (ageIng({ i,m }, newboard.GetCell({ i,m })))
				PutCell({ i,m }, newboard.GetCell({ i,m }));
		}
	}
}
Cell Board::NewAge(position pos) {
	int count = 0;
	for (int i = 0; i < Arrow::Max; i++)
	{
		position checkPos = pos;
		checkPos.addArrow(Arrow(i));
		checkPos.Normalize();
		if (boardCells[checkPos.x][checkPos.y] == Living) {
			count++;
		}
	}
	if (count == 3) return Living;
	if (boardCells[pos.x][pos.y] == Living && count == 2) return Living;
	else return Dead;
}
bool Board::ageIng(position pos, Cell myStone) {
	int oldAge = futureBoard[pos.x][pos.y];

	if (myStone == Living)
		futureBoard[pos.x][pos.y]++;
	if (GetCell(pos) == Dead && myStone == Dead)
		futureBoard[pos.x][pos.y]--;

	if (futureBoard[pos.x][pos.y] < 0)
		futureBoard[pos.x][pos.y] = 0;

	if (futureBoard[pos.x][pos.y] >= sizeof(colorList) / sizeof(colorList[0]))
		futureBoard[pos.x][pos.y] = sizeof(colorList) / sizeof(colorList[0]) - 1;

	return (oldAge != futureBoard[pos.x][pos.y] || GetCell(pos) != myStone);
}
void Board::PlayersPut(position pos) {
	if (GetCell(pos) == Living) {
		futureBoard[pos.x][pos.y] = 0;
		PutCell(pos, Dead);
	}
	else {
		futureBoard[pos.x][pos.y] = 1;
		PutCell(pos, Living);
	}
}