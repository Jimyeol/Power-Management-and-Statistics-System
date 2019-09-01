#pragma once
#include "afxwin.h"


// CDlgTurnOn 대화 상자입니다.

class CDlgTurnOn : public CDialog
{
	DECLARE_DYNAMIC(CDlgTurnOn)

public:
	CDlgTurnOn(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgTurnOn();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 턴온인지 오프인지 
	CButton m_ctCheckTurn;

public:
	void SetPosition(bool bTurnOn);
	// 체크변수
	BOOL m_bTurnOn;
};
