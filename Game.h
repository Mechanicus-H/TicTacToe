#pragma once
#include "Board.h"
#include "BoardConsoleView.h"

class Game
{
private:
	Board m_gameBoard;
	BoardConsoleView m_consoleOutput;

	bool ProcessKey(const char key); // true if board changed
public:
	Game();

	void GameStep(const char key);
	bool IsGameOver() const;
	void ShowResults();
};