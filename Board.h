#pragma once
#include "Point2D.h"
#include "Tile.h"
#include "Board.h"
#include "Frame.h"
#include <curses.h>

class CBoard
{
public:
	CBoard();
	CBoard(int _x, int _y, int _width, int _height);
	~CBoard();

	void OnKeyUp();
	void OnKeyDown();
	void OnKeyRight();
	void OnKeyLeft();
	void OnKeySpace(long _gameStep);

	void Render() const;
	void Update(long _gameStep);

	void ToggleNext();

	CPoint2D Position;
	int Width;
	int Height;

	CFrame* pFrame;
	std::vector<CTile*> m_vTiles;
	CTile* m_pCurrentTile;
	CTile* m_pNextTile;

private:
	void InitTiles();
	void CreateTile();
	void FixCurrentTile();
	void CheckFullRows();

	std::vector<__int64> m_vOccupiedFields;

	int m_iNextFallStep;
	int m_iNextDropStep;
	int m_iFallSpeed;
	int m_iDropSpeed;
	__int64 m_iFullRowNumber;
	int m_iNextTileX;
	int m_iNextTileY;

	bool m_bDrop;
	bool m_bShowNext;
};

