#include <iostream>
#include <conio.h>
#include"position.h"
#include"BOARD.h"
#include"BoardSomething.h"
#include"MyCursorAt.h"

using namespace std;
Board board;
void MiliSleep(int time);
bool PlayerInput();
int main()
{

	srand((unsigned int)time(NULL));
	board.initialize();
	board.Print();
	if (PlayerInput() == false) {

		system("cls"); return 0;
	}
	int age = 0;
	do
	{
		age++;
		printf("%c[%d;%dH", ESC, 0, 0);
		printf("%c[K", ESC);
		cout << age << "世代目";
		if (kbhit() != 0) {

			if (getch() == ESC)
				break;
			if (PlayerInput() == false) break;
		}
		board.NewAgeBoard();
		MiliSleep(100);
	} while (1);

	system("cls");
	return 0;
}
void MiliSleep(int milisecond) {
	time_t now = milisecond + clock();

	while (now > clock());
}
bool PlayerInput() {
	bool putFinish = false;
	position answer = { 0,0 };
	printf("%c[>5l", ESC);  /* カーソル表示 */
	MyCursorAt::CursorAt(answer);
	do {
		int c = getch();
		if (c == ESC) return false;
		if (c == 0xe0) {
			switch (getch())
			{
			case 0x48: answer.x--; break;
			case 0x50: answer.x++; break;
			case 0x4b: answer.y--; break;
			case 0x4d: answer.y++; break;
			}
		}
		if (c == 'w' || c == '8') answer.x--;
		if (c == 'a' || c == '4') answer.y--;
		if (c == 's' || c == '2') answer.x++;
		if (c == 'd' || c == '6') answer.y++;
		answer.Normalize();

		if (c == SPACE) {
			board.PlayersPut(answer);
		}
		if (c == BS) {
			board.initialize();	board.Print();
		}
		MyCursorAt::CursorAt(answer);
		if (c == CR) putFinish = true;
	} while (!putFinish);
	return true;
}