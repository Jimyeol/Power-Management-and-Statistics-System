#include "StdAfx.h"
#include "Tile.h"


CTile::CTile(void)
{
}


CTile::~CTile(void)
{
}


void CTile::InitTile(UINT nTileX, UINT nTileY, CRect rectTile, CRect viewTile)
{
	m_nTileX = nTileX;
	m_nTileY = nTileY;
	m_rectTile = rectTile;
	m_rectViewTile = viewTile;
}

