#pragma once


// CDlgInputBld ��ȭ �����Դϴ�.

class CDlgInputBld : public CDialog
{
	DECLARE_DYNAMIC(CDlgInputBld)

public:
	CDlgInputBld(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgInputBld();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_INPUT_BLD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ������ x���� �Է�
	UINT m_nBld_X;
	// ������ Y���� �Է�
	UINT m_nBld_Y;
};
