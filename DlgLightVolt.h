#pragma once


// CDlgLightVolt ��ȭ �����Դϴ�.

class CDlgLightVolt : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLightVolt)

public:
	CDlgLightVolt(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgLightVolt();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ��Ʈ
	UINT m_nVolt;
};
