#pragma once


// CDlgEtcInput 대화 상자입니다.

class CDlgEtcInput : public CDialog
{
	DECLARE_DYNAMIC(CDlgEtcInput)

public:
	CDlgEtcInput(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgEtcInput();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_ETC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_nObjectName;
};
