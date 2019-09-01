#pragma once
class CEletronic
{
public:
	CEletronic(void);
	~CEletronic(void);

public:
	int m_nX;
	int m_nY;
	int m_bOpen;
	CRect rectEle;
	int m_nScale; //전기 세기

	Image *EleImg;
	int m_nEnergy;	//에너지 사용량
	int m_nLimitEnergy;
	CString strName;

	bool m_bTurnOn;

	void SettingPngFile();
};

