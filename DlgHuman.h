#pragma once
#include "afxwin.h"


// CDlgHuman 대화 상자입니다.

class CDlgHuman : public CDialog
{
	DECLARE_DYNAMIC(CDlgHuman)

public:
	CDlgHuman(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgHuman();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIG_HUMAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctLayerHuman;
	void SettingLayer(int Y);
	int GetCursor();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboHumanLayer();
	afx_msg void OnCbnSelendokComboHumanLayer();
	afx_msg void OnCbnSetfocusComboHumanLayer();

public:
	int m_nLayer;
	int m_nCur;
};
