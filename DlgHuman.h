#pragma once
#include "afxwin.h"


// CDlgHuman ��ȭ �����Դϴ�.

class CDlgHuman : public CDialog
{
	DECLARE_DYNAMIC(CDlgHuman)

public:
	CDlgHuman(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgHuman();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIG_HUMAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
