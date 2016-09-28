#include "stdafx.h"
#include "Board.h"
#include "BaseDefinitions.h"
#include <time.h>

CBoard::CBoard()
{
	CBoard(3, 3, 5, 5);
}

CBoard::CBoard(int _x, int _y, int _width, int _height)
{
	Position.X = _x;
	Position.Y = _y;
	Width = _width;
	Height = _height;
	pFrame = new CFrame(_x, _y, _width, _height);
	m_pCurrentTile = NULL;
	InitTiles();
	for (int i = 0; i < _height; i++)
	{
		m_vOccupiedFields.push_back(0);
	}
	m_iFallSpeed = 100;
	m_iDropSpeed = 1;
	m_iNextFallStep = m_iFallSpeed;
	m_iNextDropStep = m_iDropSpeed;
	srand(time(NULL));
	m_bDrop = false;
	for (long long i = 0LL; i < (long long)BaseDefinitions::FieldWidth; i++)
	{
		m_iFullRowNumber |= (1LL << i);
	}

	m_iNextTileX = 0; // _x - 15;
	m_iNextTileY = 0; // (_y + _height) / 2 - 15;
	m_bShowNext = true;
}


CBoard::~CBoard()
{
	delete pFrame;
	for (CTile* t : m_vTiles)
	{
		delete t;
	}
}

void CBoard::OnKeyUp()
{
	if (m_pCurrentTile != NULL && !m_bDrop)
	{
		m_pCurrentTile->PreviousVariation(m_vOccupiedFields);
	}
}

void CBoard::OnKeyDown()
{
	if (m_pCurrentTile != NULL && !m_bDrop)
	{
		m_pCurrentTile->NextVariation(m_vOccupiedFields);
	}
}

void CBoard::OnKeyRight()
{
	if (m_pCurrentTile != NULL && !m_bDrop)
	{
		m_pCurrentTile->Move(1, 0, m_vOccupiedFields);
	}
}

void CBoard::OnKeyLeft()
{
	if (m_pCurrentTile != NULL && !m_bDrop)
	{
		m_pCurrentTile->Move(-1, 0, m_vOccupiedFields);
	}
}

void CBoard::OnKeySpace(long _gameStep)
{
	m_iNextFallStep = _gameStep + m_iDropSpeed;
	m_bDrop = true;
}

void CBoard::Render() const
{
	pFrame->Render();

	char c1 = (char)32;
	char c2 = (char)46;

	for (long long y = 0LL; y < BaseDefinitions::FieldHeight; y++)
	{
		for (long long x = 0LL; x < BaseDefinitions::FieldWidth; x++)
		{
			if (m_vOccupiedFields.at(y) > 0 && (m_vOccupiedFields.at(y) & (1LL << x)) == (1LL << x))
			{
				c1 = (char)178;
				c2 = c1;
			}
			else
			{
				c1 = (char)32;
				c2 = (char)46;
			}

			mvaddch(BaseDefinitions::FieldPositionY + y, BaseDefinitions::FieldPositionX + (x * BaseDefinitions::ScaleX), c1);
			mvaddch(BaseDefinitions::FieldPositionY + y, BaseDefinitions::FieldPositionX + (x * BaseDefinitions::ScaleX) + 1, c2);
		}
	}
	if (m_pCurrentTile != NULL)
	{
		m_pCurrentTile->Render(false);
	}


	for (int y = BaseDefinitions::PreviewTileY; y < BaseDefinitions::PreviewTileY + 4; y++)
	{
		for (int x = BaseDefinitions::PreviewTileX; x < BaseDefinitions::PreviewTileX + 3 * BaseDefinitions::ScaleX; x++)
		{
			mvaddch(y, x, ' ');
		}
	}

	if (m_bShowNext)
	{
		if (m_pNextTile != NULL)
		{
			m_pNextTile->Render(true);
		}
	}
}

void CBoard::Update(long _gameStep)
{
	if (m_pCurrentTile != NULL)
	{
		if (_gameStep > m_iNextFallStep)
		{
			if (m_pCurrentTile->Move(0, 1, m_vOccupiedFields) == CTile::BLOCKED_DOWNWARD)
			{
				FixCurrentTile();
				CheckFullRows();
				CreateTile();
				m_iNextFallStep = _gameStep + m_iFallSpeed;
			}
			else
			{
				m_iNextFallStep += (m_bDrop ? m_iDropSpeed : m_iFallSpeed);
			}
		}
	}
}

void CBoard::InitTiles()
{
	std::vector<CPoint2D> tileDef;
	CTile* t;

	/*Debug Tile
	t = new CTile();

	tileDef.clear();
	tileDef.push_back(CPoint2D(0, 0));
	t->AddVariation(tileDef);

	m_vTiles.push_back(t);
	*/

	//------------------------------
	
	/* L */
	t = new CTile();

	tileDef.clear();
	tileDef.push_back(CPoint2D(0, 0));
	tileDef.push_back(CPoint2D(1, 0));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(1, 2));
	t->AddVariation(tileDef);

	tileDef.clear();
	tileDef.push_back(CPoint2D(2, 0));
	tileDef.push_back(CPoint2D(0, 1));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(2, 1));
	t->AddVariation(tileDef);

	tileDef.clear();
	tileDef.push_back(CPoint2D(1, 0));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(1, 2));
	tileDef.push_back(CPoint2D(2, 2));
	t->AddVariation(tileDef);

	tileDef.clear();
	tileDef.push_back(CPoint2D(0, 2));
	tileDef.push_back(CPoint2D(0, 1));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(2, 1));
	t->AddVariation(tileDef);

	m_vTiles.push_back(t);

	/* L Reverse */
	t = new CTile();

	tileDef.clear();
	tileDef.push_back(CPoint2D(2, 2));
	tileDef.push_back(CPoint2D(0, 1));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(2, 1));
	t->AddVariation(tileDef);

	tileDef.clear();
	tileDef.push_back(CPoint2D(1, 0));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(1, 2));
	tileDef.push_back(CPoint2D(0, 2));
	t->AddVariation(tileDef);

	tileDef.clear();
	tileDef.push_back(CPoint2D(0, 0));
	tileDef.push_back(CPoint2D(0, 1));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(2, 1));
	t->AddVariation(tileDef);

	tileDef.clear();
	tileDef.push_back(CPoint2D(2, 0));
	tileDef.push_back(CPoint2D(1, 0));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(1, 2));
	t->AddVariation(tileDef);

	m_vTiles.push_back(t);

	/* T */
	t = new CTile();

	tileDef.clear();
	tileDef.push_back(CPoint2D(1, 2));
	tileDef.push_back(CPoint2D(0, 1));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(2, 1));
	t->AddVariation(tileDef);

	tileDef.clear();
	tileDef.push_back(CPoint2D(1, 0));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(1, 2));
	tileDef.push_back(CPoint2D(0, 1));
	t->AddVariation(tileDef);

	tileDef.clear();
	tileDef.push_back(CPoint2D(1, 0));
	tileDef.push_back(CPoint2D(0, 1));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(2, 1));
	t->AddVariation(tileDef);

	tileDef.clear();
	tileDef.push_back(CPoint2D(2, 1));
	tileDef.push_back(CPoint2D(1, 0));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(1, 2));
	t->AddVariation(tileDef);

	m_vTiles.push_back(t);

	/* S */
	t = new CTile();

	tileDef.clear();
	tileDef.push_back(CPoint2D(1, 2));
	tileDef.push_back(CPoint2D(0, 1));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(2, 2));
	t->AddVariation(tileDef);


	tileDef.clear();
	tileDef.push_back(CPoint2D(1, 0));
	tileDef.push_back(CPoint2D(0, 1));
	tileDef.push_back(CPoint2D(0, 2));
	tileDef.push_back(CPoint2D(1, 1));
	t->AddVariation(tileDef);

	m_vTiles.push_back(t);

	/* S Reverse */
	t = new CTile();

	tileDef.clear();
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(0, 2));
	tileDef.push_back(CPoint2D(1, 2));
	tileDef.push_back(CPoint2D(2, 1));
	t->AddVariation(tileDef);

	tileDef.clear();
	tileDef.push_back(CPoint2D(0, 0));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(1, 2));
	tileDef.push_back(CPoint2D(0, 1));
	t->AddVariation(tileDef);

	m_vTiles.push_back(t);


	/*Square*/
	t = new CTile();

	tileDef.clear();
	tileDef.push_back(CPoint2D(0, 1));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(0, 2));
	tileDef.push_back(CPoint2D(1, 2));
	t->AddVariation(tileDef);

	m_vTiles.push_back(t);

	/*Long*/
	t = new CTile();

	tileDef.clear();
	tileDef.push_back(CPoint2D(1, 0));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(1, 2));
	tileDef.push_back(CPoint2D(1, 3));
	t->AddVariation(tileDef);

	tileDef.clear();
	tileDef.push_back(CPoint2D(0, 1));
	tileDef.push_back(CPoint2D(1, 1));
	tileDef.push_back(CPoint2D(2, 1));
	tileDef.push_back(CPoint2D(3, 1));
	t->AddVariation(tileDef);

	m_vTiles.push_back(t);

	if (m_pCurrentTile == NULL)
	{
		CreateTile();
	}
}

void CBoard::CreateTile()
{
	if (m_pNextTile == NULL)
	{
		m_pNextTile = m_vTiles.at(rand() % m_vTiles.size());
		m_pNextTile->Reset();
		m_pNextTile->MoveTo(m_iNextTileX, m_iNextTileY);
	}

	m_pCurrentTile = m_pNextTile;
	m_pNextTile = m_vTiles.at(rand() % m_vTiles.size());
	m_pCurrentTile->Reset();
	m_bDrop = false;
}

void CBoard::FixCurrentTile()
{
	if (m_pCurrentTile != NULL)
	{
		for (CPoint2D* p : m_pCurrentTile->m_pCurrentVariation->Points)
		{
			CPoint2D fixPoint(p->X + m_pCurrentTile->Position.X, p->Y + m_pCurrentTile->Position.Y);
			__int64& iRow = m_vOccupiedFields.at(fixPoint.Y);
			iRow = (_int64)(1 << fixPoint.X) | iRow;
		}
	}
}

void CBoard::CheckFullRows()
{
	for (int i = 0; i < (int)m_vOccupiedFields.size(); i++)
	{
		if (m_vOccupiedFields.at(i) == m_iFullRowNumber)
		{
			for (int j = i; j > 0; j--)
			{
				__int64& row = m_vOccupiedFields.at(j);
				if (j == 0)
				{
					row = 0;
				}
				else
				{
					row = m_vOccupiedFields.at(j - 1);
				}
			}
		}
	}

}

void CBoard::ToggleNext()
{
	m_bShowNext = !m_bShowNext;
}
