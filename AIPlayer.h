#pragma once
#include "Utilites.h"
#include "Board.h"

#include <memory>

class Board;

class AIPlayer
{
private:

	static constexpr int
		LOSS = -1000, WIN = 1000, DEAD_HEAT = 0;

	const Board* m_pBoard;

	int IsOnDiag(const Point& p) const; // 3 if on both diags, 1 - main, 2 - minor

	int GetStepScore(const Point& p) const;

	static int GetScoreExt(const Board::ColLineType& markers);

	// algorithm from wiki and git
	static std::pair<int, Point> MinMaxOptimize(Board& board, char marker,
		int depth, int alpha, int beta);

public:
	explicit AIPlayer(const Board* pBoard);

	Point GetBestMove() const;

};

