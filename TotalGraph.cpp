// TotalGraph.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Ele.h"
#include "TotalGraph.h"


// CTotalGraph

IMPLEMENT_DYNCREATE(CTotalGraph, CView)

CTotalGraph::CTotalGraph()
{
	strPercent.Format(""); 

	for( int i = 0; i < GRAPHCOUNT; i++)
	{
		GraphPnt[i].nSumCount = GRAPHSIZE.bottom;
		GraphPnt[i].pointX = 0;
	}

	GraphCount = 0;

	//rectGradation = /*GRAPHSIZE.*/;
}

CTotalGraph::~CTotalGraph()
{
}

BEGIN_MESSAGE_MAP(CTotalGraph, CView)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTotalGraph 그리기입니다.

void CTotalGraph::OnDraw(CDC* dc)
{
	CDocument* pDoc = GetDocument();

	CCustomDC pDC(dc);
	// TODO: 여기에 그리기 코드를 추가합니다.

	//그래프 눈금 그려주는 알고리즘
	for(int i = 0; i < (int)GRAPHSIZE.right/GRAPHCOUNT; i++)
	{
		pDC->MoveTo(i+(i*13), 0);
		pDC->LineTo(i+(i*13), 100);
	}
	for(int i = 0; i < (int)(100/GRAPHCOUNT); i++)
	{
		pDC->MoveTo(GRAPHSIZE.left, i+(i*(GRAPHCOUNT-1)));
		pDC->LineTo(GRAPHSIZE.right, i+(i*(GRAPHCOUNT-1)));
	}

	
	pDC->TextOutA(5, 5, strPercent);

	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));   
	CPen* pOldPen = pDC->SelectObject(&pen); 

	for( int i = 0; i < GraphCount; i++)
	{
		pDC->MoveTo(GraphPnt[i].pointX, GraphPnt[i].nSumCount);
		pDC->LineTo(GraphPnt[i+1].pointX, GraphPnt[i+1].nSumCount);
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	
	
	
}


// CTotalGraph 진단입니다.

#ifdef _DEBUG
void CTotalGraph::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CTotalGraph::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTotalGraph 메시지 처리기입니다.


void CTotalGraph::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnTimer(nIDEvent);
}


// 그래프 등 변수초기화 꼐속해줌
void CTotalGraph::InitGraph(int nSum)
{
	if( nSum < 0 )
		return;

	 

	if( GraphCount == GRAPHCOUNT-1)
	{
		int sum = 0;
		for( int i = 0; i < GRAPHCOUNT-1; i++) 
		{
			GraphPnt[i].nSumCount = GraphPnt[i+1].nSumCount;
			//sum += (GraphPnt[i].pointX + (int)GRAPHUNIT);
		}
		GraphPnt[GraphCount].nSumCount = nSum;
	}
	else
	{
	GraphCount++;
	GraphPnt[GraphCount].nSumCount = nSum;
	GraphPnt[GraphCount].pointX += (GraphPnt[GraphCount-1].pointX + (int)GRAPHSIZE.right/GRAPHCOUNT);
	}

	//

	//strPercent.Format("총 사용량 : %d %", nSum);
	//GraphPnt[GraphCount].pointX += (GraphPnt[GraphCount-1].pointX + (int)GRAPHUNIT);

	Invalidate(false);
}
