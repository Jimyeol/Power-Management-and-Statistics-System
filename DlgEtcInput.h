#pragma once


// CDlgEtcInput ��ȭ �����Դϴ�.

class CDlgEtcInput : public CDialog
{
	DECLARE_DYNAMIC(CDlgEtcInput)

public:
	CDlgEtcInput(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgEtcInput();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_ETC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_nObjectName;
};
