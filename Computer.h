#pragma once
class CComputer
{

public:
	int m_nX;
	int m_nY;
	int m_bOpen;
	CRect rectComputer;
	int m_nScale; //���� ����

	Image *computerImg;
	int m_nEnergy;	//������ ��뷮
	int m_nLimitEnergy;

	bool m_bTurnOn;


public:
	CComputer(void);
	~CComputer(void);

	void SettingPngFile();
};

