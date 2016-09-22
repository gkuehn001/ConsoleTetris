#pragma once
#include <vector>
#include "TileVariation.h"
#include "BaseDefinitions.h"
#include <curses.h>

class CTile
{
public:
	enum EMoveBlocker : int
	{
		NOT_BLOCKED,
		NO_VARIATION_AVAILABLE,
		BLOCKED,
		BLOCKED_DOWNWARD
	};

	CTile();
	~CTile();

	void AddVariation(const std::vector<CPoint2D>& _vPointList);
	bool CheckIsWithinBoardBounds(const CPoint2D& _p);
	bool CheckValidTilePosition(const CTileVariation& _variation, const CPoint2D& _position, std::vector<__int64>& _occupiedFields);
	inline int GetVariationCount() { return static_cast<int>(m_vVariations.size()); }
	EMoveBlocker Move(int _x, int _y, std::vector<__int64>& _occupiedFields);
	void MoveTo(int _x, int _y);
	void NextVariation(std::vector<__int64>& _occupiedFields);
	void PreviousVariation(std::vector<__int64>& _occupiedFields);
	void Render(bool _isPreview);
	void Reset();
	void Update(long _gameStep);

	std::vector<CTileVariation*> m_vVariations;
	CTileVariation* m_pCurrentVariation;
	int m_iCurrentVariationIndex;

	CPoint2D Position;
};

