#pragma once
#include "afxwin.h"


// CDlgAirconeStats ��ȭ �����Դϴ�.

class CDlgAirconeStats : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAirconeStats)

public:
	CDlgAirconeStats(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgAirconeStats();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_AIRCON_STATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// �� ������ ��� �޺��ڽ� ���̾� ǥ�� 
	CComboBox m_ctLayer;
	virtual BOOL OnInitDialog();
	// �� ���� �� ���� ��뷮 
	CEdit m_ctLayerSum;
	// �� �� ���̾� ���»�뷮 �Ѱ�
	int m_nLayerSum;

	int m_nCurrentLayer; //���� �������ִ� ��
	afx_msg void OnCbnSetfocusComboLayer();
	afx_msg void OnCbnSelendokComboLayer();


	// �� ���� ���̾� �� �޾ƿ���
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
