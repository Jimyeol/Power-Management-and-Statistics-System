#pragma once
class CTile
{
public:
	UINT m_nTileX;
	UINT m_nTileY;

	CRect m_rectTile;
	CRect m_rectViewTile;
public:
	CTile();
	~CTile(void);
	void InitTile(UINT nTileX, UINT nTileY, CRect rectTile, CRect viewTile);
};

