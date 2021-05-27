#pragma once
#include <array>
#include <vector>

#include "Utilites.h"

enum ePlayerMove {
	None = 0, Left, Right, Up, Down
};

enum eWinner {
	NoWinner = 0, // Continue the game
	DeadHeat, Human, AI
};

class Board
{
public:
	static constexpr int SZ = 3;
	static constexpr char PLAYER_MARKER = 'X';
	static constexpr char AI_MARKER = 'O';
	static constexpr char EMPTY_MARKER = '\0';

	using ColLineType = std::array<char, SZ>;
	using RawBoardType = std::array<ColLineType, SZ>;

private:
	RawBoardType m_GameBoard;
	Point m_selectedCell;
	mutable eWinner m_winner = NoWinner;

	void Clear();
	static eWinner CheckExt(const ColLineType& ar);

public:
	ColLineType GetCol(int numb) const;
	ColLineType GetLine(int numb) const;
	ColLineType GetDiag(int diag) const; // 1 - main, -1 - minor

	Board();
	Board(const Board& other);
	~Board();

	const ColLineType& operator[](size_t index) const
	{	return m_GameBoard[index];	}
	ColLineType& operator[](size_t index)
	{	return m_GameBoard[index];	}

	Point getSelectedCell() const;
	bool setSelectedCell(Point p);

	bool IsSelectedAvailable() const;

	bool MoveCursor(ePlayerMove direction);
	bool PlayerChoiced();

	bool IsGameOver() const;
	eWinner GetWinner() const;

	void AIMove();
	auto& getRawBoard() const { return m_GameBoard; }
	std::vector<Point> GetLegalMoves() const;
	bool IsPosibleMove(Point p) const;

	static char GetOpponentMarker(char mark);

	void MarkCell(const Point& p, char mark);
	void SkipWinner();
};