// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>

#include "Game.h"

using namespace std;

int main()
{
	//	for (int i = 1; i < 256; ++i)
	//	{
	//		cout << "Char: " << char(i) << " - " << i << endl << endl;
	//	}
	char isContinue = 'y';

	while (isContinue == 'y')
	{

		Game game;
		char ch = '\0';
		game.GameStep(ch);

		while (!game.IsGameOver())
		{
			ch = '\0';
			ch = _getch();
			game.GameStep(ch);
		}
		game.ShowResults();
		cout << "Play again(y/n)? ";
		cin >> isContinue;
	}
}
