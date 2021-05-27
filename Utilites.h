#pragma once

struct Point
{
	int x = 0, y = 0;

	bool operator == (const Point& other) const;
	bool operator != (const Point& other) const;
};