#pragma once

#include <vector>
#include <curses.h>
#include "Point2D.h"

class CTileVariation
{
public:
	CTileVariation();
	~CTileVariation();

	void AddPoint(int _x, int _y);
	void Render(const CPoint2D& _position);
	void RenderPreview();

	std::vector<CPoint2D*> Points;
	int MaxX;
	int MaxY;
};

