#pragma once

class CLight
{
public:
	int m_nX;
	int m_nY;
	int m_bOpen;
	CRect ellLight;
	int m_nScale; //���� ����

	Image *lightImg;



	int m_nEnergy;	//������ ��뷮
	int m_nLimitEnergy;
public:
	CLight(void);
	~CLight(void);

	void SettingPngFile();
};

