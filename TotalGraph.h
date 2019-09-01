#pragma once

#include "Customdc.h"
// CTotalGraph 뷰입니다.

typedef struct GRAPHPOINT
{
	int nSumCount;
	int pointX;
}GraphPoint;

class CTotalGraph : public CView
{
	DECLARE_DYNCREATE(CTotalGraph)

public:
	CTotalGraph();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CTotalGraph();

public:
	virtual void OnDraw(CDC* dc);      // 이 뷰를 그리기 위해 재정의되었습니다.
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

	int GraphCount;	//그래프 카운트

	CString strPercent;

	CRect **rectGradation;

public:
	// 그래프 등 변수초기화 꼐속해줌
	void InitGraph(int nSum);
};


