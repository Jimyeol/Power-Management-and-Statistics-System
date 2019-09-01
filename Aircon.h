#pragma once
class CAircon
{
	public:
	int m_nX;
	int m_nY;
	int m_bOpen;
	CRect rectAircon;
	int m_nScale; //전기 세기

	Image *airconImg;
	int m_nEnergy;	//에너지 사용량
	int m_nLimitEnergy;

	bool m_bTurnOn;


public:
	CAircon(void);
	~CAircon(void);

	void SettingPngFile();
};


