#include "Board.h"
#include "AIPlayer.h"

#include <algorithm>

using namespace std;

void Board::Clear()
{
	for (auto& ar : m_GameBoard)
	{
		ar.fill(EMPTY_MARKER);
	}
	m_selectedCell = { 0, 0 };
	m_winner = NoWinner;
}
//-----------------------------------------------
Board::Board()
{
	Clear();
}
//-----------------------------------------------
Board::Board(const Board& other) 
	: m_GameBoard(other.m_GameBoard), m_selectedCell(other.m_selectedCell),
	m_winner(other.m_winner)
{ }
//-----------------------------------------------
Board::~Board()
{ }
//-----------------------------------------------
Point Board::getSelectedCell() const
{
	return m_selectedCell;
}
//-----------------------------------------------
bool Board::setSelectedCell(Point p)
{
	if (m_selectedCell == p)
		return false;

	if (p.x >= SZ)
		p.x %= SZ;
	else if (p.x < 0)
		p.x = SZ - 1;

	if (p.y >= SZ)
		p.y %= SZ;
	else if (p.y < 0)
		p.y = SZ - 1;

	m_selectedCell = p;
	return true;
}
//-------------------------------------
bool Board::IsSelectedAvailable() const
{
	return m_GameBoard[m_selectedCell.x][m_selectedCell.y] == '\0';
}
//-------------------------------------
bool Board::MoveCursor(ePlayerMove dir)
{
	auto curPos = getSelectedCell();

	switch (dir)
	{
	case Left: curPos.y--; break;
	case Right: curPos.y++; break;
	case Up: curPos.x--; break;
	case Down: curPos.x++; break;
	default: return false;
	}
	return setSelectedCell(curPos);
}
//-------------------------------------
bool Board::PlayerChoiced()
{
	if (IsSelectedAvailable())
	{
		m_GameBoard[m_selectedCell.x][m_selectedCell.y] = PLAYER_MARKER;
		return true;
	}
	return false;
}
//-------------------------------------
bool Board::IsGameOver() const
{
	bool isGameContinue = false;

	for (int i = 0; i < SZ; ++i)
	{
		eWinner winner = NoWinner;
		for (int j = 0; j < 2; ++j)
		{
			if (j == 0)
				winner = CheckExt(GetCol(i));
			else
				winner = CheckExt(GetLine(i));
			
			if (winner == Human || winner == AI)
			{
				m_winner = winner;
				return true;
			}
			else if (winner == NoWinner)
				isGameContinue = true; // We have posible steps
		}
	}

	for (int i = -1; i <= 1; i += 2) // Check Diags
	{
		eWinner winner = CheckExt(GetDiag(i));
		if (winner == Human || winner == AI)
		{
			m_winner = winner;
			return true;
		}
		else if (winner == NoWinner)
			isGameContinue = true; // We have posible steps
	}

	if (!isGameContinue)
		m_winner = DeadHeat;
	return !isGameContinue;
}
//-------------------------------------
eWinner Board::GetWinner() const
{
	if (m_winner == NoWinner)
		IsGameOver(); // Check Again;
	return m_winner;
}
//-------------------------------------
Board::ColLineType Board::GetCol(int numb) const
{
	ColLineType ar;
	size_t count = 0;
	for (auto& line : m_GameBoard)
		ar[count++] = line[numb];
	return ar;
}
//-------------------------------------
Board::ColLineType Board::GetLine(int numb) const
{
	return m_GameBoard[numb];
}
//-------------------------------------
Board::ColLineType Board::GetDiag(int diag) const
{
	_ASSERT(diag == 1 || diag == -1);

	ColLineType ar;
	int i = 0;
	int j = (diag == 1) ? 0 : SZ - 1;
	for (auto& line : m_GameBoard)
	{
		ar[i++] = line[j];
		j += diag;
	}
	return ar;
}
//-------------------------------------
eWinner Board::CheckExt(const Board::ColLineType& ar)
{
	int ai = 0, player = 0, empty = 0; // counters
	for (char ch : ar)
	{
		if (ch == PLAYER_MARKER)
			++player;
		else if (ch == AI_MARKER)
			++ai;
		else
			++empty;
	}

	if (player == SZ)
		return eWinner::Human;
	else if (ai == SZ)
		return eWinner::AI;
	else if ((player == 0 && ai == 0) || empty > 0)
		return eWinner::NoWinner;
	else
		return eWinner::DeadHeat;
}
//-------------------------------------
void Board::AIMove()
{
	AIPlayer bender(this);
	auto step = bender.GetBestMove();
	if(IsPosibleMove(step))
		m_GameBoard[step.x][step.y] = AI_MARKER;
}
//-------------------------------------
vector<Point> Board::GetLegalMoves() const
{
	vector<Point> results;
	for (int i = 0; i < SZ; ++i)
	{
		for (int j = 0; j < SZ; ++j)
		{
			if (m_GameBoard[i][j] == EMPTY_MARKER)
				results.push_back({ i,j });
		}
	}
	return results;
}
//-------------------------------------
bool Board::IsPosibleMove(Point p) const
{
	if (
		(p.x < 0 || p.x >= SZ) ||
		(p.y < 0 || p.y >= SZ))
		return false;
	return m_GameBoard[p.x][p.y] == EMPTY_MARKER;
}
//-------------------------------------
char Board::GetOpponentMarker(char mark)
{
	switch (mark)
	{
	case PLAYER_MARKER: return AI_MARKER;
	case AI_MARKER: return PLAYER_MARKER;
	}
	return EMPTY_MARKER;
}
//-------------------------------------
void Board::MarkCell(const Point& p, char mark)
{
	m_GameBoard[p.x][p.y] = mark;
}
//-------------------------------------
void Board::SkipWinner()
{
	m_winner = NoWinner;
}