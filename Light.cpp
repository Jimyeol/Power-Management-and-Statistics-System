#include "StdAfx.h"
#include "Light.h"


CLight::CLight(void)
{
	m_nX		= -20;
	m_nY		= -20;
	m_bOpen		= false;
	m_nEnergy	= 30;
	m_nLimitEnergy = 0;
	ellLight = CRect(-20, -20, -20, -20);

	m_nScale = 120;
	lightImg = Gdiplus::Bitmap::FromFile(L"Light.png");

}


CLight::~CLight(void)
{
	if( lightImg != NULL)
		delete lightImg;
}


void CLight::SettingPngFile()
{
	lightImg = Gdiplus::Bitmap::FromFile(L"Light.png");
	
}