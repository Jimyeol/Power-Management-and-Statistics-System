#pragma once
#include "afxcmn.h"


// CDlgEditLight 대화 상자입니다.

class CDlgEditLight : public CDialog
{
	DECLARE_DYNAMIC(CDlgEditLight)

public:
	CDlgEditLight(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgEditLight();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 형광등 슬라이더 컨트롤러 
	CSliderCtrl m_ctrlSlider;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	void SetPosition(int nPos);	//초기값 설정해주기

	int m_nSliderPos;
	int m_nGetPos;


	virtual INT_PTR DoModal();
	virtual void OnOK();
};
