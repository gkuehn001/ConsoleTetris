#pragma once
#include "Point2D.h"

class CFrame
{
public:
	CFrame();
	CFrame(int _x, int _y, int _width, int _height);
	~CFrame();

	void Render();

	CPoint2D Position;

	int Width;
	int Height;
};

