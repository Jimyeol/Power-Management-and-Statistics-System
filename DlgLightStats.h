#pragma once
#include "afxwin.h"
#include "TotalGraph.h"

// CDlgLightStats 대화 상자입니다.

class CDlgLightStats : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLightStats)

public:
	CDlgLightStats(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgLightStats();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_LIGHT_STATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 전구 갯수 확인 
	UINT m_nLightCount;
	// 전구 갯수 확인 컨트롤러
	CEdit m_ctLineCount;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit1();
	// 형광등 총 사용량 표시 
	int m_nLightSumVolt;

	CTotalGraph* m_pViewGraph;
	afx_msg void OnDestroy();
	// 몇퍼센트 썻는지 보여주는것 
	CStatic m_stPercent;
	int m_nPercent;
	void InitStatic(int nSum);
	CString m_strPercent;
	// 전체 총 사용량 몇와트인지 
	int m_nAllSum;
	// 현재 오브젝트수가 몇인지 
	int m_nAllCount;
	// 컴퓨터 갯수
	int m_nComputerCount;
	// 컴퓨터 총 사용량
	int m_nComputerSum;
	afx_msg void OnPaint();
	// 에어컨 사용갯수
	int m_nAirconCount;
	int m_nAirconSum;
	int m_nPrintersCount;
	int m_nPrintersSum;
	int m_nEtcCount;
	int m_nEtcSum;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
