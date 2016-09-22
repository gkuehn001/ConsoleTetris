#include "stdafx.h"
#include "Frame.h"
#include "BaseDefinitions.h"
#include <curses.h>

CFrame::CFrame()
{
}

CFrame::CFrame(int _x, int _y, int _width, int _height)
{
	Position.X = _x;
	Position.Y = _y;
	Width = _width;
	Height = _height;
}


CFrame::~CFrame()
{
}

void CFrame::Render()
{
	for (int row = Position.Y; row <= Position.Y + Height; row++)
	{
		int col = Position.X - 2;
		if (col >= 0 && row <= 24)
		{
			mvaddch(row, col, '<');
		}
		col = Position.X - 1;
		if (col >= 0 && row <= 24)
		{
			mvaddch(row, col, '!');
		}
		col = Position.X + Width * BaseDefinitions::ScaleX;
		if (col < 80 && row <= 24)
		{
			mvaddch(row, col, '!');
		}
		col = Position.X + Width * BaseDefinitions::ScaleX + 1;
		if (col < 80 && row <= 24)
		{
			mvaddch(row, col, '>');
		}
	}
	for (int col = Position.X; col < Position.X + Width * BaseDefinitions::ScaleX; col++)
	{
		int row = Position.Y + Height;
		if (col > 0 && col < 80 && row <= 24)
		{
			mvaddch(row, col, '=');
		}
	}
	for (int co = 0; co < Width; co++)
	{
		int row = Position.Y + Height + 1;
		int col = Position.X + co * BaseDefinitions::ScaleX;
		if (col > 0 && col < 80 && row <= 24)
		{
			mvaddch(row, col, '\\');
		}
		col++;
		if (col > 0 && col < 80 && row <= 24)
		{
			mvaddch(row, col, '/');
		}
	}
}
