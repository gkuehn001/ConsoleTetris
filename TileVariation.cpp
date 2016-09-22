#include "stdafx.h"
#include "TileVariation.h"
#include "MatUtil.h"
#include "BaseDefinitions.h"
#include <curses.h>

CTileVariation::CTileVariation()
{
	MaxX = 0;
	MaxY = 0;
}


CTileVariation::~CTileVariation()
{
	for (CPoint2D* p : Points)
	{
		delete p;
	}
}

void CTileVariation::AddPoint(int _x, int _y)
{
	Points.push_back(new CPoint2D(_x,_y));
	if (_x > MaxX)
		MaxX = _x;
	if (_y > MaxY)
		MaxY = _y;
}



void CTileVariation::Render(const CPoint2D& _position)
{
	for (CPoint2D* p : Points)
	{

		mvaddch(BaseDefinitions::FieldPositionY + p->Y + _position.Y, BaseDefinitions::FieldPositionX + (p->X + _position.X) * BaseDefinitions::ScaleX, (char)219);
		mvaddch(BaseDefinitions::FieldPositionY + p->Y + _position.Y, BaseDefinitions::FieldPositionX + (p->X + _position.X) * BaseDefinitions::ScaleX + 1, (char)219);
	}
}

void CTileVariation::RenderPreview()
{
	for (CPoint2D* p : Points)
	{
		mvaddch(BaseDefinitions::PreviewTileY + p->Y, BaseDefinitions::PreviewTileX + p->X * BaseDefinitions::ScaleX, (char)219);
		mvaddch(BaseDefinitions::PreviewTileY + p->Y, BaseDefinitions::PreviewTileX + p->X * BaseDefinitions::ScaleX + 1, (char)219);
	}
}
