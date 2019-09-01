#pragma once

class CLight
{
public:
	int m_nX;
	int m_nY;
	int m_bOpen;
	CRect ellLight;
	int m_nScale; //전기 세기

	Image *lightImg;



	int m_nEnergy;	//에너지 사용량
	int m_nLimitEnergy;
public:
	CLight(void);
	~CLight(void);

	void SettingPngFile();
};

