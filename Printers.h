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
	int m_nScale; //���� ����

	Image *printerImg;
	int m_nEnergy;	//������ ��뷮
	int m_nLimitEnergy;

	bool m_bTurnOn;

	void SettingPngFile();
};

