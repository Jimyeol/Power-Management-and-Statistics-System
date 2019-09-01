#include "StdAfx.h"
#include "Aircon.h"


CAircon::CAircon(void)
{
	m_nX		= -20;
	m_nY		= -20;
	m_bOpen		= false;
	m_nEnergy	= 30;
	m_nLimitEnergy = 0;
	rectAircon = CRect(-20, -20, -20, -20);
	m_bTurnOn = true;

	m_nScale = 120;
	airconImg = Gdiplus::Bitmap::FromFile(L"Aircon_off.png");
}


CAircon::~CAircon(void)
{
}


void CAircon::SettingPngFile()
{
	if( m_bTurnOn )
		airconImg = Gdiplus::Bitmap::FromFile(L"Aircon_on.png");
	else
		airconImg = Gdiplus::Bitmap::FromFile(L"Aircon_off.png");
	
}