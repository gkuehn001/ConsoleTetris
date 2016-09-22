#pragma once
#include <sstream>

class CPoint2D
{
public:
	CPoint2D();
	CPoint2D(int _x, int _y);
	~CPoint2D();

	void Set(const CPoint2D& _newPoint);

	int X;
	int Y;
};

