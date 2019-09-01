#include "StdAfx.h"
#include "Human.h"


CHuman::CHuman(void)
{
	 m_nX = -20;
	 m_nY = -20;
	 m_nSpeed = 10;
	 m_bOpen = false;
	 m_bMoveCheck = false;
	 rectHuman = CRect(-20, -20, -20, -20);

	humanImg = Gdiplus::Bitmap::FromFile(L"human.png");
}


CHuman::~CHuman(void)
{
}


void CHuman::SettingPngFile()
{
	m_bOpen = true;
	humanImg = Gdiplus::Bitmap::FromFile(L"human.png");
	
}