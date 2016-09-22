#include "stdafx.h"
#include "Tile.h"
#include "MatUtil.h"
#include "Debug.h"
#include <iostream>

CTile::CTile()
{
	m_pCurrentVariation = NULL;
	m_iCurrentVariationIndex = -1;
}

CTile::~CTile()
{
	for (CTileVariation* p : m_vVariations)
	{
		delete p;
	}
	m_vVariations.clear();
}

void CTile::AddVariation(const std::vector<CPoint2D>& _vPointList)
{
	CTileVariation* pVariation = new CTileVariation();
	for(CPoint2D p : _vPointList)
	{
		pVariation->AddPoint(p.X, p.Y);
	}
	m_vVariations.push_back(pVariation);
	if (m_pCurrentVariation == NULL)
	{
		m_pCurrentVariation = pVariation;
		m_iCurrentVariationIndex = 0;
	}
}

bool CTile::CheckValidTilePosition(const CTileVariation & _variation, const CPoint2D & _position, std::vector<__int64>& _occupiedFields)
{
	for (CPoint2D* p : _variation.Points)
	{
		CPoint2D checkPosition(_position.X + p->X, _position.Y + p->Y);
		if (!CheckIsWithinBoardBounds(checkPosition))
			return false;
		if ((_occupiedFields.at(checkPosition.Y) & (1 << checkPosition.X)) == (1 << checkPosition.X))
		{
			return false;
		}
	}

	return true;
}

bool CTile::CheckIsWithinBoardBounds(const CPoint2D& _p)
{
	//CDebug::Output("Pos %d / %d\n", _p.X, _p.Y);
	//CDebug::SetDebugOutput("Pos %d / %d\n", _p.X, _p.Y);
	return _p.X >= 0
		&& _p.X < BaseDefinitions::FieldWidth
		&& _p.Y >= 0
		&& _p.Y < BaseDefinitions::FieldHeight;
}

CTile::EMoveBlocker CTile::Move(int _x, int _y, std::vector<__int64>& _occupiedFields)
{
	CPoint2D newPosition(Position.X + _x, Position.Y + _y);
	if (m_pCurrentVariation != NULL)
	{
		if (CheckValidTilePosition(*m_pCurrentVariation, newPosition, _occupiedFields))
		{
			Position.Set(newPosition);
			return EMoveBlocker::NOT_BLOCKED;
		}
		else if (_x == 0 && _y > 0) // downwards
		{
			return EMoveBlocker::BLOCKED_DOWNWARD;
		}
		return EMoveBlocker::BLOCKED;
	}
	return EMoveBlocker::NO_VARIATION_AVAILABLE;
}

void CTile::MoveTo(int _x, int _y)
{
	Position.X = _x;
	Position.Y = _y;
}

void CTile::NextVariation(std::vector<__int64>& _occupiedFields)
{
	int m_iNextVariation = m_iCurrentVariationIndex + 1;
	if (m_iNextVariation > GetVariationCount() - 1)
	{
		m_iNextVariation = 0;
	}
	if (m_pCurrentVariation != NULL && CheckValidTilePosition(*(m_vVariations.at(m_iNextVariation)), Position, _occupiedFields))
	{
		m_iCurrentVariationIndex = m_iNextVariation;
		m_pCurrentVariation = m_vVariations.at(m_iCurrentVariationIndex);
	}
}

void CTile::PreviousVariation(std::vector<__int64>& _occupiedFields)
{
	int m_iNextVariation = m_iCurrentVariationIndex - 1;
	if (m_iNextVariation < 0)
	{
		m_iNextVariation = GetVariationCount() - 1;
	}
	if (m_pCurrentVariation != NULL && CheckValidTilePosition(*(m_vVariations.at(m_iNextVariation)), Position, _occupiedFields))
	{
		m_iCurrentVariationIndex = m_iNextVariation;
		m_pCurrentVariation = m_vVariations.at(m_iCurrentVariationIndex);
	}
}

void CTile::Render(bool _isPreview)
{
	if (_isPreview)
	{
		if (m_vVariations.size() > 0)
		{
			m_vVariations.at(0)->RenderPreview();
		}
	}
	else if (m_pCurrentVariation != NULL)
	{
		m_pCurrentVariation->Render(Position);
	}
}

void CTile::Reset()
{
	if (m_vVariations.size() > 0)
	{
		m_iCurrentVariationIndex = 0;
	}
	m_pCurrentVariation = m_vVariations.at(0);
	MoveTo(BaseDefinitions::FieldWidth / 2 - (m_pCurrentVariation->MaxX + 1) / 2, 0);
}

void CTile::Update(long _gameStep)
{
}
