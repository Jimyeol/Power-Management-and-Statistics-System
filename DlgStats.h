#pragma once
#include "afxcmn.h"

#include "DlgLightStats.h"
#include "DlgAirconeStats.h"

// CDlgStats ��ȭ �����Դϴ�.

class CDlgStats : public CDialog
{
	DECLARE_DYNAMIC(CDlgStats)

public:
	CDlgStats(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgStats();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_STATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// �� ���� ��Ʈ�ѷ� 
	CTabCtrl m_tapControl;
	virtual BOOL OnInitDialog();
	// ��Ʈ�� �߰�
	void InitControl(void);

	CDlgLightStats m_dlgLightStats;
	CDlgAirconeStats m_dlgAirconStats;
	// �� ���̾�α� ����
	void CreateTapDlg(void);
	afx_msg void OnTcnSelchangeTabStats(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
