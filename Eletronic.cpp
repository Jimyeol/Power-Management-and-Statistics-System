#include "StdAfx.h"
#include "Eletronic.h"


CEletronic::CEletronic(void)
{
	m_nX		= -20;
	m_nY		= -20;
	m_bOpen		= false;
	m_nEnergy	= 30;
	m_nLimitEnergy = 0;
	rectEle = CRect(-20, -20, -20, -20);
	m_bTurnOn = true;
	strName.Format("전기(기타)");
	m_nScale = 120;
	EleImg = Gdiplus::Bitmap::FromFile(L"ele_off.png");
}


CEletronic::~CEletronic(void)
{
}


void CEletronic::SettingPngFile()
{
	if( m_bTurnOn )
		EleImg = Gdiplus::Bitmap::FromFile(L"ele_on.png");
	else
		EleImg = Gdiplus::Bitmap::FromFile(L"ele_off.png");
	
}