#include "AIPlayer.h"

#include <map>

using namespace std;

AIPlayer::AIPlayer(const Board* pBoard) : m_pBoard(pBoard)
{
	_ASSERT(m_pBoard);
}
//-------------------------------------
Point AIPlayer::GetBestMove() const
{
	/*
	* old algorithm don't work fine
	map<int, Point, greater<int>> moves;
	moves[-1] = { -1,-1 };

	for (auto move : m_pBoard->GetLegalMoves())
	{
		int score = GetStepScore(move);
		moves[score] = move;
	}

	return moves.begin()->second;
	*/
	Board boardCopy{ *m_pBoard }; // let's use reference to copy, because const method
	auto optimized = MinMaxOptimize(boardCopy, Board::AI_MARKER, 0, LOSS, WIN); // 
	return optimized.second;
}
//-------------------------------------
int AIPlayer::IsOnDiag(const Point& p) const
{
	if (p.x == 1 && p.y == 1)
		return 3;
	if (p.x == p.y)
		return 1;
	if ((p.x == 2 && p.y == 0) || (p.x == 0 && p.y == 2))
		return 2;
	return 0;
}
//-------------------------------------
int AIPlayer::GetStepScore(const Point& p) const
{
	int result = 0;
	result += GetScoreExt(m_pBoard->GetLine(p.x));
	result += GetScoreExt(m_pBoard->GetCol(p.y));
	
	int isOnDiags = IsOnDiag(p);
	if (isOnDiags == 3)
	{
		result += GetScoreExt(m_pBoard->GetDiag(1));
		result += GetScoreExt(m_pBoard->GetDiag(-1));
	}
	else if (isOnDiags == 1)
		result += GetScoreExt(m_pBoard->GetDiag(1));
	else if (isOnDiags == 2)
		result += GetScoreExt(m_pBoard->GetDiag(-1));

	return result;
}
//-------------------------------------
int AIPlayer::GetScoreExt(const Board::ColLineType& markers)
{
	int ai_count = 0, human_count = 0, empty_count = 0;
	const int sz = markers.size();
	for (auto ch : markers)
	{
		switch (ch)
		{
		case Board::AI_MARKER: ++ai_count; break;
		case Board::PLAYER_MARKER: ++human_count; break;
		case Board::EMPTY_MARKER: ++empty_count; break;
		}
	}

	if (empty_count == 0)
		return -100;
	else if (empty_count == 1 && ai_count == sz - 1)
		return 100;
	else if (empty_count == 1 && human_count == (sz - 1))
		return 50;
	else if (ai_count == 1 && empty_count == (sz - 1))
		return 5;
	else if (human_count == 1 && empty_count == (sz - 1))
		return 2;
	else if (empty_count == sz)
		return 1;
	else 
		return 0;
}
//-------------------------------------
std::pair<int, Point> AIPlayer::MinMaxOptimize(Board& board, char marker, 
	int depth, int alpha, int beta)
{
	Point bestMove{ -1, -1 };
	int bestScore = (marker == Board::AI_MARKER) ? LOSS : WIN;

	if (board.IsGameOver())
	{
		switch (board.GetWinner())
		{
		case AI: return make_pair(WIN, bestMove);
		case Human: return make_pair(LOSS, bestMove);
		case DeadHeat: return make_pair(DEAD_HEAT, bestMove);
		}
	}

	for (auto& move : board.GetLegalMoves())
	{
		board.MarkCell(move, marker);
		if (marker == Board::AI_MARKER)
		{
			int score = MinMaxOptimize(board, Board::PLAYER_MARKER, depth + 1,
				alpha, beta).first;
			if (bestScore < score)
			{
				bestScore = score - depth * 10;
				bestMove = move;
				alpha = max(alpha, bestScore);
				board.MarkCell(move, Board::EMPTY_MARKER);
				if (beta <= alpha)
					break;
			}
		}
		else
		{
			int score = MinMaxOptimize(board, Board::AI_MARKER, depth + 1,
				alpha, beta).first;
			if (bestScore > score)
			{
				bestScore = score + depth * 10;
				bestMove = move;

				beta = min(beta, bestScore);
				board.MarkCell(move, Board::EMPTY_MARKER);
				if (beta <= alpha)
					break;
			}
		}

		board.MarkCell(move, Board::EMPTY_MARKER);
	}
	board.SkipWinner();

	return make_pair(bestScore, bestMove);
}
















