#pragma once
class CComputer
{

public:
	int m_nX;
	int m_nY;
	int m_bOpen;
	CRect rectComputer;
	int m_nScale; //전기 세기

	Image *computerImg;
	int m_nEnergy;	//에너지 사용량
	int m_nLimitEnergy;

	bool m_bTurnOn;


public:
	CComputer(void);
	~CComputer(void);

	void SettingPngFile();
};

