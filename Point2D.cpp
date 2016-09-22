#include "stdafx.h"
#include "Point2D.h"
#include "Windows.h"

CPoint2D::CPoint2D()
{
	CPoint2D(0, 0);
}

CPoint2D::CPoint2D(int _x, int _y)
{
	X = _x;
	Y = _y;
}


CPoint2D::~CPoint2D()
{
}

void CPoint2D::Set(const CPoint2D & _newPoint)
{
	X = _newPoint.X;
	Y = _newPoint.Y;
}
