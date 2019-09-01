#pragma once
class CPrinters
{
public:
	CPrinters(void);
	~CPrinters(void);

public:
	int m_nX;
	int m_nY;
	int m_bOpen;
	CRect rectPrinter;
	int m_nScale; //전기 세기

	Image *printerImg;
	int m_nEnergy;	//에너지 사용량
	int m_nLimitEnergy;

	bool m_bTurnOn;

	void SettingPngFile();
};

