#pragma once
class CAircon
{
	public:
	int m_nX;
	int m_nY;
	int m_bOpen;
	CRect rectAircon;
	int m_nScale; //���� ����

	Image *airconImg;
	int m_nEnergy;	//������ ��뷮
	int m_nLimitEnergy;

	bool m_bTurnOn;


public:
	CAircon(void);
	~CAircon(void);

	void SettingPngFile();
};


