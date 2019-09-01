#pragma once
#include "afxcmn.h"

#include "DlgLightStats.h"
#include "DlgAirconeStats.h"

// CDlgStats 대화 상자입니다.

class CDlgStats : public CDialog
{
	DECLARE_DYNAMIC(CDlgStats)

public:
	CDlgStats(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgStats();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_STATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 각 탭의 컨트롤러 
	CTabCtrl m_tapControl;
	virtual BOOL OnInitDialog();
	// 컨트롤 추가
	void InitControl(void);

	CDlgLightStats m_dlgLightStats;
	CDlgAirconeStats m_dlgAirconStats;
	// 탭 다이얼로그 생성
	void CreateTapDlg(void);
	afx_msg void OnTcnSelchangeTabStats(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
