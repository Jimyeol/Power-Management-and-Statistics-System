#pragma once
#include "afxwin.h"


// CDlgTurnOn ��ȭ �����Դϴ�.

class CDlgTurnOn : public CDialog
{
	DECLARE_DYNAMIC(CDlgTurnOn)

public:
	CDlgTurnOn(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgTurnOn();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// �Ͽ����� �������� 
	CButton m_ctCheckTurn;

public:
	void SetPosition(bool bTurnOn);
	// üũ����
	BOOL m_bTurnOn;
};
