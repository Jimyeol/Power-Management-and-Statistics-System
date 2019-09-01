#include "StdAfx.h"
#include "Computer.h"


CComputer::CComputer(void)
{
	m_nX		= -20;
	m_nY		= -20;
	m_bOpen		= false;
	m_nEnergy	= 30;
	m_nLimitEnergy = 0;
	rectComputer = CRect(-20, -20, -20, -20);
	m_bTurnOn = true;

	m_nScale = 120;
	computerImg = Gdiplus::Bitmap::FromFile(L"computer_off.png");
}


CComputer::~CComputer(void)
{
}

void CComputer::SettingPngFile()
{
	if( m_bTurnOn )
		computerImg = Gdiplus::Bitmap::FromFile(L"computer_on.png");
	else
		computerImg = Gdiplus::Bitmap::FromFile(L"computer_off.png");
	
}