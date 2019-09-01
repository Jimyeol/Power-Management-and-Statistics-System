#pragma once

#include "Customdc.h"
// CTotalGraph ���Դϴ�.

typedef struct GRAPHPOINT
{
	int nSumCount;
	int pointX;
}GraphPoint;

class CTotalGraph : public CView
{
	DECLARE_DYNCREATE(CTotalGraph)

public:
	CTotalGraph();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CTotalGraph();

public:
	virtual void OnDraw(CDC* dc);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	GraphPoint GraphPnt[GRAPHCOUNT];
public:

	int GraphCount;	//�׷��� ī��Ʈ

	CString strPercent;

	CRect **rectGradation;

public:
	// �׷��� �� �����ʱ�ȭ ��������
	void InitGraph(int nSum);
};


