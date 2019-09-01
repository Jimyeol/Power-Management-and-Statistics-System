#pragma once
#include "afxwin.h"
#include "TotalGraph.h"

// CDlgLightStats ��ȭ �����Դϴ�.

class CDlgLightStats : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLightStats)

public:
	CDlgLightStats(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgLightStats();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_LIGHT_STATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ���� ���� Ȯ�� 
	UINT m_nLightCount;
	// ���� ���� Ȯ�� ��Ʈ�ѷ�
	CEdit m_ctLineCount;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit1();
	// ������ �� ��뷮 ǥ�� 
	int m_nLightSumVolt;

	CTotalGraph* m_pViewGraph;
	afx_msg void OnDestroy();
	// ���ۼ�Ʈ ������ �����ִ°� 
	CStatic m_stPercent;
	int m_nPercent;
	void InitStatic(int nSum);
	CString m_strPercent;
	// ��ü �� ��뷮 ���Ʈ���� 
	int m_nAllSum;
	// ���� ������Ʈ���� ������ 
	int m_nAllCount;
	// ��ǻ�� ����
	int m_nComputerCount;
	// ��ǻ�� �� ��뷮
	int m_nComputerSum;
	afx_msg void OnPaint();
	// ������ ��밹��
	int m_nAirconCount;
	int m_nAirconSum;
	int m_nPrintersCount;
	int m_nPrintersSum;
	int m_nEtcCount;
	int m_nEtcSum;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
