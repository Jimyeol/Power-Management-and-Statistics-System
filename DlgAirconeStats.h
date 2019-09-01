#pragma once
#include "afxwin.h"


// CDlgAirconeStats 대화 상자입니다.

class CDlgAirconeStats : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAirconeStats)

public:
	CDlgAirconeStats(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgAirconeStats();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_AIRCON_STATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 각 층마다 띄울 콤보박스 레이어 표시 
	CComboBox m_ctLayer;
	virtual BOOL OnInitDialog();
	// 각 층의 총 전력 사용량 
	CEdit m_ctLayerSum;
	// 각 층 레이어 전력사용량 총값
	int m_nLayerSum;

	int m_nCurrentLayer; //지금 눌려져있는 층
	afx_msg void OnCbnSetfocusComboLayer();
	afx_msg void OnCbnSelendokComboLayer();


	// 각 층의 레이어 값 받아오기
	void SettingLayer(int sum, int count, int *pObjectSum, int *pObjectCount);
	int m_nObjectCount;
	int m_nComputerCounter;
	int m_nComputerSum;
	int m_nLightCount;
	int m_nLightSum;
	int m_nAirconCount;
	int m_nAirconSum;
	int m_nPrintersCount;
	int m_nPrintersSum;
	int m_nEtcCount;
	int m_nEtcSum;
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
