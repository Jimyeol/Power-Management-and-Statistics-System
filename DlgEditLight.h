#pragma once
#include "afxcmn.h"


// CDlgEditLight ��ȭ �����Դϴ�.

class CDlgEditLight : public CDialog
{
	DECLARE_DYNAMIC(CDlgEditLight)

public:
	CDlgEditLight(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgEditLight();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ������ �����̴� ��Ʈ�ѷ� 
	CSliderCtrl m_ctrlSlider;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	void SetPosition(int nPos);	//�ʱⰪ �������ֱ�

	int m_nSliderPos;
	int m_nGetPos;


	virtual INT_PTR DoModal();
	virtual void OnOK();
};
