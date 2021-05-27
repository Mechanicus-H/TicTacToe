#include "Game.h"

using namespace std;

Game::Game() : m_gameBoard(), m_consoleOutput(&m_gameBoard)
{
	m_consoleOutput.Init();
}
//-------------------------------------
bool Game::ProcessKey(const char key)
{
	ePlayerMove direction = None;
	switch (key)
	{
	case 'w': case 'W':; direction = Up; break;
	case 's': case 'S': direction = Down;; break;
	case 'a': case 'A': direction = Left; break;
	case 'd': case 'D': direction = Right; break;
	case ' ': return m_gameBoard.PlayerChoiced();
	}

	m_gameBoard.MoveCursor(direction);

	return false;
}
//-------------------------------------
void Game::GameStep(const char key)
{
	if (ProcessKey(key) && !m_gameBoard.IsGameOver())
		m_gameBoard.AIMove();
	m_consoleOutput.ClearView();
	m_consoleOutput.ShowMessage("Controls: w,a,s,d, <space> - X\n");
	m_consoleOutput.RecalcView();
	m_consoleOutput.Show();
}
//-------------------------------------
bool Game::IsGameOver() const
{
	return m_gameBoard.IsGameOver();
}
//-------------------------------------
void Game::ShowResults()
{
	string message;
	switch (m_gameBoard.GetWinner())
	{
	case DeadHeat: message = "No winner, Dead heat!\n"; break;
	case Human: message = "You win, Congrats!!\n"; break;
	case AI: message = "AI wins, Looser =)\n"; break;
	}
	m_consoleOutput.ShowMessage(message);
}