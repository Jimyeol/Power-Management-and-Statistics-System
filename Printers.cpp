#include "StdAfx.h"
#include "Printers.h"


CPrinters::CPrinters(void)
{
	m_nX		= -20;
	m_nY		= -20;
	m_bOpen		= false;
	m_nEnergy	= 30;
	m_nLimitEnergy = 0;
	rectPrinter = CRect(-20, -20, -20, -20);
	m_bTurnOn = true;

	m_nScale = 120;
	printerImg = Gdiplus::Bitmap::FromFile(L"printer_off.png");
}


CPrinters::~CPrinters(void)
{
}

void CPrinters::SettingPngFile()
{
	if( m_bTurnOn )
		printerImg = Gdiplus::Bitmap::FromFile(L"printer_on.png");
	else
		printerImg = Gdiplus::Bitmap::FromFile(L"printer_off.png");
	
}