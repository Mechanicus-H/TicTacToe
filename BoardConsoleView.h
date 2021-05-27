#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#include "Utilites.h"

class Board;

enum ConsoleColor : uint8_t {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

class BoardConsoleView
{
private:
	std::vector<std::string> m_ViewStrings;
	Board* m_pBoard = nullptr;
	static HANDLE m_hConsole;

	size_t m_viewSize = 0;


	void clear();
	char getOutputSymb(Point pos) const;
	static void PrintSymbol(char ch, ConsoleColor backColor = Black, ConsoleColor textColor = White);
public:
	BoardConsoleView(Board* pGameBoard);

	void Init();

	void RecalcView();
	void Show() const;
	void ClearView();
	void ShowMessage(const std::string& message);
};

