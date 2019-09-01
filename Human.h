#pragma once
class CHuman
{
public:
	int m_nX;
	int m_nY;
	int m_nSpeed;
	bool m_bOpen;
	bool m_bMoveCheck;
	CRect rectHuman;
	Image *humanImg;

public:
	CHuman(void);
	~CHuman(void);

	void SettingPngFile();
};

