#include "BoardConsoleView.h"
#include "Board.h"

using namespace std;

HANDLE BoardConsoleView::m_hConsole = nullptr;

void BoardConsoleView::clear()
{
	for (auto& s : m_ViewStrings)
		s.clear();
}
//-------------------------------------
BoardConsoleView::BoardConsoleView(Board* pBoard)
	: m_pBoard(pBoard)
{
	_ASSERT(m_pBoard);
	Init();
}
//-------------------------------------
void BoardConsoleView::Init()
{
	m_viewSize = m_pBoard->SZ + 2;
	m_ViewStrings.clear();

	m_ViewStrings.resize(m_viewSize);
	if(!m_hConsole)
		m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_ASSERT(m_hConsole);
}
//-------------------------------------
void BoardConsoleView::RecalcView()
{
	clear();

	string buff;

	for (int i = 0; i < m_viewSize; ++i)
	{
		for (int j = 0; j < m_viewSize; ++j)
			buff.push_back(getOutputSymb({ i, j }));
		m_ViewStrings[i] = move(buff);
	}
}
//-------------------------------------
char BoardConsoleView::getOutputSymb(Point pos) const
{
	char out = '\0';
	const size_t
		top = 0,
		bottom = m_viewSize - 1,
		right = m_viewSize - 1,
		left = 0;


	if(pos.x == top || pos.x == bottom)
	{
		if (left == pos.y)
			out = (top == pos.x) ? 201 : 200; // ╔ : ╚
		else if (right == pos.y)
			out = (top == pos.x) ? 187 : 188; // ╗ : ╝
		else
			out = 205; // ═
	}
	else
	{
		if (pos.y == left || pos.y == right)
			out = 186; // ║
		else
			out = (*m_pBoard)[pos.x - 1][pos.y - 1];
	}

	return out;
}
//-------------------------------------
void BoardConsoleView::Show() const
{
	const auto selectedCell = m_pBoard->getSelectedCell();
	size_t i = 0, j = 0;
	for (auto& s : m_ViewStrings)
	{
		j = 0;
		for (auto ch : s)
		{
			Point boardPoint{ i - 1, j - 1 };
			if (boardPoint == selectedCell)
				PrintSymbol(ch, Red);
			else
				PrintSymbol(ch);
			++j;
		}
		++i;
		PrintSymbol('\n');
	}
}
//-------------------------------------
void BoardConsoleView::PrintSymbol(char ch, ConsoleColor backColor, 
	ConsoleColor textColor)
{
	SetConsoleTextAttribute(m_hConsole, (WORD)((backColor << 4) | textColor));
	cout << ch;
}
//-------------------------------------
void BoardConsoleView::ClearView()
{
	system("cls");
}
//-------------------------------------
void BoardConsoleView::ShowMessage(const string& message)
{
	cout << message;
}