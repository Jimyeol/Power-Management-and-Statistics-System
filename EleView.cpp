
// EleView.cpp : CEleView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Ele.h"
#endif

#include "EleDoc.h"
#include "EleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CEleView

IMPLEMENT_DYNCREATE(CEleView, CView)

BEGIN_MESSAGE_MAP(CEleView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_ADD_LIGHT, &CEleView::OnAddLight)
	ON_COMMAND(ID_ADD_AIRCON, &CEleView::OnAddAircon)
	ON_COMMAND(ID_VIEW, &CEleView::OnView)
	ON_COMMAND(ID_STATS, &CEleView::OnStats)
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EDIT_LIGHT, &CEleView::OnEditLight)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_BLD_CREATE, &CEleView::OnBldCreate)
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DELETEMODE, &CEleView::OnDeletemode)
	ON_COMMAND(ID_COMPUTER, &CEleView::OnComputer)
	ON_COMMAND(ID_ALL_COMPUTER, &CEleView::OnAllComputer)
	ON_COMMAND(ID_PRINTER, &CEleView::OnPrinter)
	ON_COMMAND(ID_ELETRONIC, &CEleView::OnEletronic)
	ON_COMMAND(ID_ALL_AIRCON, &CEleView::OnAllAircon)
	ON_COMMAND(ID_ALL_ETC, &CEleView::OnAllEtc)
	ON_COMMAND(ID_ALL_PRINTERS, &CEleView::OnAllPrinters)
	ON_COMMAND(ID_CONTROL_LIGHT, &CEleView::OnControlLight)
	ON_COMMAND(ID_CONTROL_HUMAN, &CEleView::OnControlHuman)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_Z_ZZ, &CEleView::OnZZz)
	ON_COMMAND(ID_ALLDEL_HUMAN, &CEleView::OnAlldelHuman)
	ON_COMMAND(ID_ADD_HUMAN, &CEleView::OnAddHuman)
END_MESSAGE_MAP()

// CEleView 생성/소멸

CEleView::CEleView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

	light				= NULL;
	computer			= NULL;
	aircon				= NULL;
	printers			= NULL;
	eletronic			= NULL;
	human				= NULL;
	m_nObjectALLCount = 0;
	m_nObjectALLSum = 0;
	strECTName.Format("전기(기타)");
	m_nBldX = 0;
	m_nBldY = 0;

	m_nDrawBldCheck = 0; //아직그리지 않음.
	m_bDrawBldCheck = false; //아직안그림
	m_ppTile = NULL;

	m_nSelectMode = VIEW;	//뷰모드, 편집모드
	m_nSelectObject = 0;	//오브젝트 생성

	info.rectInfoForm = CRect(-20, -20, -20, -20);
	info.m_bInfo = false;//인포창이 안보임
	info.infoStrFloor = CString("");
	info.infoStrVolt = CString("");
	//SetTimer(2015, 1000, NULL);

	 m_nScreenEndSizeX = 0;
	 m_nScreenStartSizeX = 0;
	 m_nScreenSizeY = 0;

	 for( int i = 0; i < MAXOBJECT; i++)
	 {
		m_nObjectCount[i] = 0;
		m_nObjectSum[i] = 0;
	 }
	 TileLimitedCount = 0;

	 HelpBtnRect = CRect(-20, -20, -20, -20);
	 backBtnRect = CRect(-20, -20, -20, -20);
	 bHelpBtn = false;
	settimercheck = false;

	

}

CEleView::~CEleView()
{

	if(light != NULL)
	{
		for( UINT i = 0; i < m_nBldX; i++ )
		{
			delete [] light[i];
		}
		delete []light;
	}

	if(m_ppTile != NULL)
	{
		for( UINT i = 0; i < m_nBldX; i++ )
		{
			delete [] m_ppTile[i];
		}
		delete []m_ppTile;
	}

	if( computer != NULL)
	{
		for( UINT i = 0; i < m_nBldX; i++ )
		{
			delete [] computer[i];
		}
		delete []computer;
	}

	if( aircon != NULL)
	{
		for( UINT i = 0; i < m_nBldX; i++ )
		{
			delete [] aircon[i];
		}
		delete []aircon;
	}

	if( printers != NULL)
	{
		for( UINT i = 0; i < m_nBldX; i++ )
		{
			delete [] printers[i];
		}
		delete []printers;
	}

	if( eletronic != NULL)
	{
		for( UINT i = 0; i < m_nBldX; i++ )
		{
			delete [] eletronic[i];
		}
		delete []eletronic;
	}

	if( human != NULL)
		delete []human;



}

BOOL CEleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CEleView 그리기

void CEleView::OnDraw(CDC* dc)
{
	CEleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CCustomDC pDC(dc);	//더블버퍼링 문제 해결
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	//GDI PLUS+
	CDC dcmem;
	dcmem.CreateCompatibleDC(&pDC);

	Graphics graph(pDC->m_hDC);
	CBrush brush(RGB(230, 230, 230));
	CBrush *pOldBrush = pDC->SelectObject(&brush);
	if( m_bDrawBldCheck )
	{
		//헬프장 비트맵 출력
		
		if( !bHelpBtn )
		{
			CBitmap bitmap_Help;
			bitmap_Help.LoadBitmapA(IDB_BITMAP3);
			BITMAP bmpinfoHelp;
			bitmap_Help.GetBitmap(&bmpinfoHelp);
			dcmem.SelectObject(&bitmap_Help);
			pDC->BitBlt(0, 0, bmpinfoHelp.bmWidth, bmpinfoHelp.bmHeight,
				&dcmem, 0, 0, SRCCOPY);
			bitmap_Help.DeleteObject();

			CBitmap bitmap_HelpButton;
			bitmap_HelpButton.LoadBitmapA(IDB_BITMAP4);

			BITMAP bmpinfoHelpBtn;
			bitmap_HelpButton.GetBitmap(&bmpinfoHelpBtn);
			dcmem.SelectObject(&bitmap_HelpButton);
			pDC->BitBlt((bmpinfoHelp.bmWidth/2)/2, bmpinfoHelp.bmHeight - bmpinfoHelp.bmHeight/3, bmpinfoHelpBtn.bmWidth, bmpinfoHelpBtn.bmHeight,
				&dcmem, 0, 0, SRCCOPY);
			backBtnRect = CRect(-20, -20, -20, -20);
			HelpBtnRect = CRect((bmpinfoHelp.bmWidth/2)/2  , bmpinfoHelp.bmHeight - bmpinfoHelp.bmHeight/3, 
				((bmpinfoHelp.bmWidth/2)/2) + bmpinfoHelpBtn.bmWidth, (bmpinfoHelp.bmHeight - bmpinfoHelp.bmHeight/3) + bmpinfoHelpBtn.bmHeight);
			bitmap_HelpButton.DeleteObject();

			/*pDC->Rectangle(HelpBtnRect);*/
		}
		else
		{
			CBitmap bitmap_Help;
			bitmap_Help.LoadBitmapA(IDB_BITMAP6);
			BITMAP bmpinfoHelp;
			bitmap_Help.GetBitmap(&bmpinfoHelp);
			dcmem.SelectObject(&bitmap_Help);
			pDC->BitBlt(0, 0, bmpinfoHelp.bmWidth, bmpinfoHelp.bmHeight,
				&dcmem, 0, 0, SRCCOPY);
			

			HelpBtnRect = CRect(-20, -20, -20, -20);
			backBtnRect = CRect(0  , 0, bmpinfoHelp.bmWidth-20, bmpinfoHelp.bmHeight);
			bitmap_Help.DeleteObject();
		}

		
		

		for( UINT i = 0; i < m_nBldX; i++ )
		{
			for( UINT j = 0; j < m_nBldY; j++ )
			{
					pDC->Rectangle(m_ppTile[i][j].m_rectViewTile);
			}
		}
		pDC->SelectObject(pOldBrush);
	}
	else
	{

	

	CBitmap bitmap;
	bitmap.LoadBitmapA(IDB_BITMAP_INTRO);
	BITMAP bmpinfo;
	bitmap.GetBitmap(&bmpinfo);

	dcmem.SelectObject(&bitmap);

	pDC->BitBlt(260, 100, bmpinfo.bmWidth, bmpinfo.bmHeight,
		&dcmem, 0, 0, SRCCOPY);
	bitmap.DeleteObject();

	
	}

	//graph.DrawImage(lightImg, 10, 10, 30, 30);

	
	for( UINT i = 0; i < m_nBldX; i++ )
	{ 
		for( UINT j = 0; j < m_nBldY; j++ )
		{
			if( light[i][j].m_bOpen  )
			{
				SolidBrush brush(Color(light[i][j].m_nScale, 0, 0, 0));
				graph.FillRectangle(&brush, m_ppTile[i][j].m_rectTile.left, 
					m_ppTile[i][j].m_rectTile.top, 
					m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left, 
					m_ppTile[i][j].m_rectTile.bottom - m_ppTile[i][j].m_rectTile.top);
				light[i][j].SettingPngFile();	//꼐속 세팅해줘야함.
				graph.DrawImage(light[i][j].lightImg, light[i][j].m_nX - (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2, 
					light[i][j].m_nY, (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left),
					(m_ppTile[i][j].m_rectTile.bottom - m_ppTile[i][j].m_rectTile.top)/(MAXOBJECT) );
				
			}
			if( computer[i][j].m_bOpen  )
			{
				computer[i][j].SettingPngFile();	//꼐속 세팅해줘야함.
				graph.DrawImage(computer[i][j].computerImg, computer[i][j].m_nX- (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2 , 
					computer[i][j].m_nY, (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left), 
					(m_ppTile[i][j].m_rectTile.bottom - m_ppTile[i][j].m_rectTile.top)/(MAXOBJECT));
			}
			if( aircon[i][j].m_bOpen  )
			{
				aircon[i][j].SettingPngFile();	//꼐속 세팅해줘야함.
				graph.DrawImage(aircon[i][j].airconImg, aircon[i][j].m_nX - (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2 , 
					aircon[i][j].m_nY, (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left), 
					(m_ppTile[i][j].m_rectTile.bottom - m_ppTile[i][j].m_rectTile.top)/(MAXOBJECT));
			}
			if( eletronic[i][j].m_bOpen  )
			{
				eletronic[i][j].SettingPngFile();	//꼐속 세팅해줘야함.
				graph.DrawImage(eletronic[i][j].EleImg, eletronic[i][j].m_nX- (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2, 
					eletronic[i][j].m_nY, (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left),
					(m_ppTile[i][j].m_rectTile.bottom - m_ppTile[i][j].m_rectTile.top)/(MAXOBJECT));
			}
			if( printers[i][j].m_bOpen  )
			{
				printers[i][j].SettingPngFile();	//꼐속 세팅해줘야함.
				graph.DrawImage(printers[i][j].printerImg, printers[i][j].m_nX-(m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2, 
					printers[i][j].m_nY, (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left),
					(m_ppTile[i][j].m_rectTile.bottom - m_ppTile[i][j].m_rectTile.top)/(MAXOBJECT));
			}
/*
			if( light[i][j].m_bOpen)
				pDC->Rectangle(m_ppTile[i][j].m_rectTile);
			if( human[j].m_bOpen)
				pDC->Rectangle(human[j].rectHuman);*/
		}
	}
	for( UINT i = 0; i < m_nBldY; i++ )
	{
		if( human[i].m_bOpen  )
		{
			human[i].SettingPngFile();	//꼐속 세팅해줘야함.
			graph.DrawImage( human[i].humanImg, human[i].m_nX, human[i].m_nY, 15, 20);

		}
	}

	//인포메이션창 띄우기
	if( info.m_bInfo )
	{

		pDC->Rectangle(info.rectInfoForm);
		pDC->TextOutA(info.rectInfoForm.left+5, info.rectInfoForm.top+10, info.infoName);
		pDC->TextOutA(info.rectInfoForm.left+5, info.rectInfoForm.top+30, info.infoStrFloor);
		pDC->TextOutA(info.rectInfoForm.left+5, info.rectInfoForm.top+50, info.infoStrVolt);
		pDC->TextOutA(info.rectInfoForm.left+5, info.rectInfoForm.top+70, info.infoCurrentVolt);
		pDC->TextOutA(info.rectInfoForm.left+5, info.rectInfoForm.top+90, info.infoPercent);
	}

	
	
	//CDC MemDC;
	//MemDC.CreateCompatibleDC(pDC);
	//CBitmap bitmap, *oldbitmap;
	//bitmap.LoadBitmapA(IDB_BITMAP1);
	//oldbitmap = MemDC.SelectObject(&bitmap);

	//BITMAP bmpinfo;
	//bitmap.GetBitmap(&bmpinfo);
	//MemDC.SelectObject(&bitmap);

	//BLENDFUNCTION bf;
	////비트맵설정
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = 0;
	//bf.SourceConstantAlpha = 20;
	//pDC->AlphaBlend(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, 
	//	&MemDC,  0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, bf);

	//MemDC.SelectObject(oldbitmap);



	
	


}


// CEleView 진단

#ifdef _DEBUG
void CEleView::AssertValid() const
{
	CView::AssertValid();
}

void CEleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEleDoc* CEleView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEleDoc)));
	return (CEleDoc*)m_pDocument;
}
#endif //_DEBUG


// CEleView 메시지 처리기


void CEleView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

}


void CEleView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//건물 생성 
	
	prevPoint = point;
	currentPoint = point;

	//포인트가눌리면
	if( HelpBtnRect.PtInRect(point))
	{
		HelpBtnRect = CRect(-20, -20, -20, -20);
		bHelpBtn = true;
		Invalidate(false);
	}
	else if( backBtnRect.PtInRect(point))
	{
		backBtnRect = CRect(-20, -20, -20, -20);
		bHelpBtn = false;
		Invalidate(false);
	}
	//오브젝트가 눌렸다.
	if( m_nSelectMode == EDIT )	//만약 편집모드라면
	{
		switch(m_nSelectObject)
		{
		case LIGHT:
			for( UINT i = 0; i < m_nBldX; i++ )
			{
				for( UINT j = 0; j < m_nBldY; j++ )
				{
					if( m_ppTile[i][j].m_rectTile.PtInRect(point) &&
						!light[i][j].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
					{
						CDlgLightVolt dlgVolt;

						if( dlgVolt.DoModal() == IDOK)
						{
							light[i][j].m_nX = (m_ppTile[i][j].m_rectTile.left + 
								((m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2));
							light[i][j].m_nY = SetObjectHeight(m_ppTile[i][j].m_rectTile.top, m_ppTile[i][j].m_rectTile.bottom, LIGHT);
							light[i][j].m_bOpen = true;
							light[i][j].ellLight = CRect(light[i][j].m_nX - (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2,
								light[i][j].m_nY, 
								(light[i][j].m_nX - (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2)
								+(m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left), 
								light[i][j].m_nY+(m_ppTile[i][j].m_rectTile.bottom - m_ppTile[i][j].m_rectTile.top)/(MAXOBJECT));
							light[i][j].m_nEnergy = dlgVolt.m_nVolt;	//전력량 보급
							light[i][j].m_nLimitEnergy = dlgVolt.m_nVolt;
						}
						break;
					}
				}
			}
			break;
			//컴퓨터 생성
		case COMPUTER:
			for( UINT i = 0; i < m_nBldX; i++ )
			{
				for( UINT j = 0; j < m_nBldY; j++ )
				{
					if( m_ppTile[i][j].m_rectTile.PtInRect(point) &&
						!computer[i][j].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
					{
						CDlgLightVolt dlgVolt;
						if( dlgVolt.DoModal() == IDOK)
						{
							computer[i][j].m_nX = (m_ppTile[i][j].m_rectTile.left + 
								((m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2));
							computer[i][j].m_nY = SetObjectHeight(m_ppTile[i][j].m_rectTile.top, m_ppTile[i][j].m_rectTile.bottom, COMPUTER);
							computer[i][j].m_bOpen = true;

							computer[i][j].rectComputer = CRect(computer[i][j].m_nX - (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2,
								computer[i][j].m_nY, 
								(computer[i][j].m_nX - (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2)
								+(m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left), 
								computer[i][j].m_nY+(m_ppTile[i][j].m_rectTile.bottom - m_ppTile[i][j].m_rectTile.top)/(MAXOBJECT));

							computer[i][j].m_nEnergy = dlgVolt.m_nVolt;	//전력량 보급
							computer[i][j].m_nLimitEnergy = dlgVolt.m_nVolt;
						}

					}
				}
			}
			break;

		case AIRCON:
			for( UINT i = 0; i < m_nBldX; i++ )
			{
				for( UINT j = 0; j < m_nBldY; j++ )
				{
					if( m_ppTile[i][j].m_rectTile.PtInRect(point) &&
						!aircon[i][j].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
					{
						CDlgLightVolt dlgVolt;
						if( dlgVolt.DoModal() == IDOK)
						{
							aircon[i][j].m_nX = (m_ppTile[i][j].m_rectTile.left + 
								((m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2));
							aircon[i][j].m_nY = SetObjectHeight(m_ppTile[i][j].m_rectTile.top, m_ppTile[i][j].m_rectTile.bottom, AIRCON);
							aircon[i][j].m_bOpen = true;

							aircon[i][j].rectAircon = CRect(aircon[i][j].m_nX - (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2,
								aircon[i][j].m_nY, 
								(aircon[i][j].m_nX - (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2)
								+(m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left), 
								aircon[i][j].m_nY+(m_ppTile[i][j].m_rectTile.bottom - m_ppTile[i][j].m_rectTile.top)/(MAXOBJECT));

							aircon[i][j].m_nEnergy = dlgVolt.m_nVolt;	//전력량 보급
							aircon[i][j].m_nLimitEnergy = dlgVolt.m_nVolt;
						}

					}
				}
			}
			break;
		case ELETRONIC:
			for( UINT i = 0; i < m_nBldX; i++ )
			{
				for( UINT j = 0; j < m_nBldY; j++ )
				{
					if( m_ppTile[i][j].m_rectTile.PtInRect(point) &&
						!eletronic[i][j].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
					{
						CDlgLightVolt dlgVolt;
						if( dlgVolt.DoModal() == IDOK)
						{
							eletronic[i][j].m_nX = (m_ppTile[i][j].m_rectTile.left + 
								((m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2));
							eletronic[i][j].m_nY = SetObjectHeight(m_ppTile[i][j].m_rectTile.top, m_ppTile[i][j].m_rectTile.bottom, ELETRONIC);
							eletronic[i][j].m_bOpen = true;

							eletronic[i][j].rectEle = CRect(eletronic[i][j].m_nX - (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2,
								eletronic[i][j].m_nY, 
								(eletronic[i][j].m_nX - (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2)
								+(m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left), 
								eletronic[i][j].m_nY+(m_ppTile[i][j].m_rectTile.bottom - m_ppTile[i][j].m_rectTile.top)/(MAXOBJECT));

							eletronic[i][j].m_nEnergy = dlgVolt.m_nVolt;	//전력량 보급
							eletronic[i][j].m_nLimitEnergy = dlgVolt.m_nVolt;
							eletronic[i][j].strName = strECTName;
						}

					}
				}
			}
			break;
		case PRINTERS:
			for( UINT i = 0; i < m_nBldX; i++ )
			{
				for( UINT j = 0; j < m_nBldY; j++ )
				{
					if( m_ppTile[i][j].m_rectTile.PtInRect(point) &&
						!printers[i][j].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
					{
						CDlgLightVolt dlgVolt;
						if( dlgVolt.DoModal() == IDOK)
						{
							printers[i][j].m_nX = (m_ppTile[i][j].m_rectTile.left + 
								((m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2));
							printers[i][j].m_nY = SetObjectHeight(m_ppTile[i][j].m_rectTile.top, m_ppTile[i][j].m_rectTile.bottom, PRINTERS);
							printers[i][j].m_bOpen = true;

							printers[i][j].rectPrinter = CRect(printers[i][j].m_nX - (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2,
								printers[i][j].m_nY, 
								(printers[i][j].m_nX - (m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left)/2)
								+(m_ppTile[i][j].m_rectTile.right - m_ppTile[i][j].m_rectTile.left), 
								printers[i][j].m_nY+(m_ppTile[i][j].m_rectTile.bottom - m_ppTile[i][j].m_rectTile.top)/(MAXOBJECT));

							printers[i][j].m_nEnergy = dlgVolt.m_nVolt;	//전력량 보급
							printers[i][j].m_nLimitEnergy = dlgVolt.m_nVolt;
						}

					}
				}
			}
			break;
		}
	}
	else if( m_nSelectMode == DEL )
	{
		for( UINT i = 0; i < m_nBldX; i++ )
		{
			for( UINT j = 0; j < m_nBldY; j++ )
			{
				if( light[i][j].ellLight.PtInRect(point) &&
					light[i][j].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
				{
					CString str;
					str.Format("%d층 %d번째 형광등 삭제하였습니다", m_nBldY-j, i+1);
					light[i][j].m_bOpen = false;
					MessageBox(str, "삭제");

				}
				if( computer[i][j].rectComputer.PtInRect(point) &&
					computer[i][j].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
				{
					CString str;
					str.Format("%d층 %d번째 컴퓨터 삭제하였습니다", m_nBldY-j, i+1);
					computer[i][j].m_bOpen = false;
					MessageBox(str, "삭제");

				}
				if( aircon[i][j].rectAircon.PtInRect(point) &&
					aircon[i][j].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
				{
					CString str;
					str.Format("%d층 %d번째 에어컨 삭제하였습니다", m_nBldY-j, i+1);
					aircon[i][j].m_bOpen = false;
					MessageBox(str, "삭제");

				}
				if( eletronic[i][j].rectEle.PtInRect(point) &&
					eletronic[i][j].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
				{
					CString str;
					str.Format("%d층 %d번째 전기 삭제하였습니다", m_nBldY-j, i+1);
					eletronic[i][j].m_bOpen = false;
					MessageBox(str, "삭제");

				}
				if( printers[i][j].rectPrinter.PtInRect(point) &&
					printers[i][j].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
				{
					CString str;
					str.Format("%d층 %d번째 프린터 삭제하였습니다", m_nBldY-j, i+1);
					printers[i][j].m_bOpen = false;
					MessageBox(str, "삭제");

				}
			}
		}
	}
	Invalidate(false);


	//총계산해주는것
	UpdateStats();//상태업데이트

	
	CView::OnLButtonDown(nFlags, point);
}


void CEleView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	info.m_bInfo = false; //아무대나 눌리면 없에버려!

	

	CView::OnLButtonUp(nFlags, point);
}


void CEleView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if( !m_bDrawBldCheck )
	{
		currentPoint = point;
		m_nDrawBldCheck++;
		//Invalidate(true);
	}

	
	CView::OnMouseMove(nFlags, point);
}


void CEleView::OnAddLight()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}
	m_nSelectObject = LIGHT;
	m_nSelectMode = EDIT;


}


void CEleView::OnAddAircon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}
	m_nSelectObject = AIRCON;
	m_nSelectMode = EDIT;
}


void CEleView::OnView()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}

	m_nSelectMode = VOLTEDIT;
	MessageBox("오브젝트 더블클릭후 설정", "설정");
}


void CEleView::OnStats()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	if( dlgStats.DoModal() == IDOK)
	{
		//전력사용량
		CDlgLightStats dlgLightStats;
		SetDlgItemInt(IDC_EDIT1, 2);
		UpdateData(false);
		//dlgLightStats.m_ctLineCount.SetDlgItemInt(20, 2);
		//dlgLightStats.m_nLightCount = 2;

	}
}


void CEleView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if( nIDEvent == 1)
	{
		if( dlgStats.m_dlgAirconStats.m_nCurrentLayer != -1 )
		{
			int sum = 0;
			int count = 0;
			int object_sum[MAXOBJECT];
			int object_count[MAXOBJECT];
			for( int i = 0; i < MAXOBJECT; i++)
			{
				object_sum[i] = 0;
				object_count[i] = 0;
			}
			for( UINT i = 0; i < m_nBldX; i++ )
			{
				if( light[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
				{
					sum += light[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nEnergy - 
						(int)((float)PERCENT(light[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nScale)/100.f * 
						light[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nEnergy);
					count++;

					object_sum[LIGHT] += light[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nEnergy - 
						(int)((float)PERCENT(light[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nScale)/100.f * 
						light[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nEnergy);
					object_count[LIGHT]++;

				}
				if( computer[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
				{
					sum += computer[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nEnergy;
					count++;

					object_sum[COMPUTER] += computer[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nEnergy;
					object_count[COMPUTER] ++;
				}
				if( aircon[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
				{
					sum += aircon[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nEnergy;
					count++;

					object_sum[AIRCON] += aircon[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nEnergy;
					object_count[AIRCON] ++;
				}
				if( eletronic[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
				{
					sum += eletronic[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nEnergy;
					count++;

					object_sum[ELETRONIC] += eletronic[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nEnergy;
					object_count[ELETRONIC] ++;
				}
				if( printers[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
				{
					sum += printers[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nEnergy;
					count++;

					object_sum[PRINTERS] += printers[i][m_nBldY - dlgStats.m_dlgAirconStats.m_nCurrentLayer-1].m_nEnergy;
					object_count[PRINTERS] ++;
				}
			}
			dlgStats.m_dlgAirconStats.SettingLayer(sum, count, object_sum, object_count);
		}
	}

	//그래프 처리해주는 부분
	
	if( nIDEvent == 2)
	{
		int sum = 0;
		int volt = 0;
		int count = 0;
		for( UINT i = 0; i < m_nBldX; i++)
		{
			for( UINT j = 0; j < m_nBldY; j++ )
			{
				if( light[i][j].m_bOpen)
				{
					sum += light[i][j].m_nEnergy - (int)((float)PERCENT(light[i][j].m_nScale)/100.f * 
						light[i][j].m_nEnergy);
					volt += light[i][j].m_nLimitEnergy;
					//volt += light[i][j].

				}
				if( computer[i][j].m_bOpen )
				{
					sum += computer[i][j].m_nEnergy;
					volt += computer[i][j].m_nLimitEnergy;
					//volt += light[i][j].

				}
				if( aircon[i][j].m_bOpen )
				{
					sum += aircon[i][j].m_nEnergy;
					volt += aircon[i][j].m_nLimitEnergy;
					//volt += light[i][j].

				}
				if( printers[i][j].m_bOpen )
				{
					sum += printers[i][j].m_nEnergy;
					volt += printers[i][j].m_nLimitEnergy;
					//volt += light[i][j].

				}
				if( eletronic[i][j].m_bOpen )
				{
					sum += eletronic[i][j].m_nEnergy;
					volt += eletronic[i][j].m_nLimitEnergy;
					//volt += light[i][j].

				}
			}

		}
		count = (int)(((float)sum/(float)volt)*100.f);
		dlgStats.m_dlgLightStats.m_pViewGraph->InitGraph((int)100 - (int)count);
		dlgStats.m_dlgLightStats.InitStatic((int)count);

	}



	if( nIDEvent == 2016)
	{
		for( UINT i = 0; i < m_nBldX; i++)
		{
			for( UINT j = 0; j < m_nBldY; j++ )
			{
				if( human[j].m_bOpen && light[i][j].m_bOpen )
				{
					if( RectColl(human[j].rectHuman, m_ppTile[i][j].m_rectTile))
					{
						light[i][j].m_nScale = 0;
					}
					else
					{
						light[i][j].m_nScale = (light[i][j].m_nEnergy/light[i][j].m_nLimitEnergy) * 255;
					}
				}
			}
		}
		for( int i = 0; i < m_nBldY; i++)
		{
			human[i].rectHuman = CRect(human[i].m_nX, human[i].m_nY, human[i].m_nX + 15, human[i].m_nY + 20);
			if( human[i].m_bOpen )
			{
				if( human[i].m_nX < m_nScreenEndSizeX + m_nScreenStartSizeX  &&  !human[i].m_bMoveCheck)
				{
					if( human[i].m_nX+40 > m_nScreenEndSizeX + m_nScreenStartSizeX)
						human[i].m_bMoveCheck = true;
					human[i].m_nX += human[i].m_nSpeed;
				}
				else if (  human[i].m_nX > m_nScreenStartSizeX &&  human[i].m_bMoveCheck )
				{
					if( human[i].m_nX-20 < m_nScreenStartSizeX )
						human[i].m_bMoveCheck = false;

					human[i].m_nX -= human[i].m_nSpeed;
				}
			}
		}
		Invalidate(false);
	}
	CView::OnTimer(nIDEvent);
}


void CEleView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	for( UINT i = 0; i < m_nBldX; i++)
	{
		for( UINT j = 0; j < m_nBldY; j++ )
		{
			if( light[i][j].ellLight.PtInRect(point) &&
				light[i][j].m_bOpen /*여기다 오브젝트 더 추가*/)	//만약에 라이트안에 포인트가 들어간다면
			{
				info.m_bInfo = true;		//그리기 !
				info.infoName.Format("[형광등]");
				info.infoStrFloor.Format("%d층%d번째", m_nBldY-j, i+1);
				info.infoStrVolt.Format("최대 %d와트", light[i][j].m_nLimitEnergy);
				info.infoCurrentVolt.Format("현재 %d와트사용", (light[i][j].m_nEnergy - (int)((float)PERCENT(light[i][j].m_nScale)/100.f * 
						light[i][j].m_nEnergy)));
				info.infoPercent.Format("%d퍼센트 사용", (int)(((float)(light[i][j].m_nEnergy - (int)((float)PERCENT(light[i][j].m_nScale)/100.f * 
					light[i][j].m_nEnergy))/(float)light[i][j].m_nEnergy)*100.f));
				info.rectInfoForm = CRect(point.x, point.y, point.x+120, point.y+120);
				if( info.rectInfoForm.bottom > m_nScreenSizeY)
				{
					info.rectInfoForm = CRect(point.x-120, point.y-120, point.x, point.y);
				}
				else if( info.rectInfoForm.right > m_nScreenEndSizeX)
				{
					info.rectInfoForm = CRect(point.x-120, point.y, point.x, point.y+120);
				}
			}
			if( computer[i][j].rectComputer.PtInRect(point) &&
				computer[i][j].m_bOpen /*여기다 오브젝트 더 추가*/)	//만약에 라이트안에 포인트가 들어간다면
			{
				info.m_bInfo = true;		//그리기 !
				info.infoName.Format("[컴퓨터]");
				info.infoStrFloor.Format("%d층%d번째", m_nBldY-j, i+1);
				info.infoStrVolt.Format("최대 %d와트", computer[i][j].m_nLimitEnergy);
				info.infoCurrentVolt.Format("현재 %d와트사용", computer[i][j].m_nEnergy);
				info.infoPercent.Format("%d퍼센트 사용", (int)(((float) computer[i][j].m_nEnergy/(float)computer[i][j].m_nLimitEnergy)*100.f));
				info.rectInfoForm = CRect(point.x, point.y, point.x+120, point.y+120);
				if( info.rectInfoForm.bottom > m_nScreenSizeY)
				{
					info.rectInfoForm = CRect(point.x-120, point.y-120, point.x, point.y);
				}
				else if( info.rectInfoForm.right > m_nScreenEndSizeX)
				{
					info.rectInfoForm = CRect(point.x-120, point.y, point.x, point.y+120);
				}
			}
			if( aircon[i][j].rectAircon.PtInRect(point) &&
				aircon[i][j].m_bOpen /*여기다 오브젝트 더 추가*/)	//만약에 라이트안에 포인트가 들어간다면
			{
				info.m_bInfo = true;		//그리기 !
				info.infoName.Format("[에어컨]");
				info.infoStrFloor.Format("%d층%d번째", m_nBldY-j, i+1);
				info.infoStrVolt.Format("최대 %d와트", aircon[i][j].m_nLimitEnergy);
				info.infoCurrentVolt.Format("현재 %d와트사용", aircon[i][j].m_nEnergy);
				info.infoPercent.Format("%d퍼센트 사용", (int)(((float) aircon[i][j].m_nEnergy/(float)aircon[i][j].m_nLimitEnergy)*100.f));
				info.rectInfoForm = CRect(point.x, point.y, point.x+120, point.y+120);
				if( info.rectInfoForm.bottom > m_nScreenSizeY)
				{
					info.rectInfoForm = CRect(point.x-120, point.y-120, point.x, point.y);
				}
				else if( info.rectInfoForm.right > m_nScreenEndSizeX)
				{
					info.rectInfoForm = CRect(point.x-120, point.y, point.x, point.y+120);
				}
			}
			if( printers[i][j].rectPrinter.PtInRect(point) &&
				printers[i][j].m_bOpen /*여기다 오브젝트 더 추가*/)	//만약에 라이트안에 포인트가 들어간다면
			{
				info.m_bInfo = true;		//그리기 !
				info.infoName.Format("[프린터]");
				info.infoStrFloor.Format("%d층%d번째", m_nBldY-j, i+1);
				info.infoStrVolt.Format("최대 %d와트", printers[i][j].m_nLimitEnergy);
				info.infoCurrentVolt.Format("현재 %d와트사용", printers[i][j].m_nEnergy);
				info.infoPercent.Format("%d퍼센트 사용", (int)(((float) printers[i][j].m_nEnergy/(float)printers[i][j].m_nLimitEnergy)*100.f));
				info.rectInfoForm = CRect(point.x, point.y, point.x+120, point.y+120);
				if( info.rectInfoForm.bottom > m_nScreenSizeY)
				{
					info.rectInfoForm = CRect(point.x-120, point.y-120, point.x, point.y);
				}
				else if( info.rectInfoForm.right > m_nScreenEndSizeX)
				{
					info.rectInfoForm = CRect(point.x-120, point.y, point.x, point.y+120);
				}
			}
			if( eletronic[i][j].rectEle.PtInRect(point) &&
				eletronic[i][j].m_bOpen /*여기다 오브젝트 더 추가*/)	//만약에 라이트안에 포인트가 들어간다면
			{
				info.m_bInfo = true;		//그리기 !
				info.infoName.Format("[%s]", eletronic[i][j].strName);
				info.infoStrFloor.Format("%d층%d번째", m_nBldY-j, i+1);
				info.infoStrVolt.Format("최대 %d와트", eletronic[i][j].m_nLimitEnergy);
				info.infoCurrentVolt.Format("현재 %d와트사용", eletronic[i][j].m_nEnergy);
				info.infoPercent.Format("%d퍼센트 사용", (int)(((float) eletronic[i][j].m_nEnergy/(float)eletronic[i][j].m_nLimitEnergy)*100.f));
				info.rectInfoForm = CRect(point.x, point.y, point.x+120, point.y+120);
				if( info.rectInfoForm.bottom > m_nScreenSizeY)
				{
					info.rectInfoForm = CRect(point.x-120, point.y-120, point.x, point.y);
				}
				else if( info.rectInfoForm.right > m_nScreenEndSizeX)
				{
					info.rectInfoForm = CRect(point.x-120, point.y, point.x, point.y+120);
				}
			}
		}
	}
	Invalidate(false);
	CView::OnRButtonDown(nFlags, point);
}


void CEleView::OnEditLight()	//형광등 조절
{
	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	dlgLightEdit.SetPosition(127);
	if( dlgLightEdit.DoModal() == IDOK)
	{
		for( UINT i = 0; i < m_nBldX; i++ )
		{ 
			for( UINT j = 0; j < m_nBldY; j++ )
			{
				if( light[i][j].m_bOpen )
				{
					light[i][j].m_nScale = DEPERCENT(dlgLightEdit.m_nSliderPos);
				}
			}
		}
	}
	Invalidate(false);

	
	UpdateStats();
	
}


void CEleView::OnLButtonDblClk(UINT nFlags, CPoint point)	//더블클릭시 형광등 조절
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if( m_nSelectMode != VOLTEDIT)
		return;

	for( UINT i = 0; i < m_nBldX; i++ )
	{
		for( UINT j = 0; j < m_nBldY; j++ )
		{
			if( light[i][j].ellLight.PtInRect(point)) 	//만약에 라이트안에 포인트가 더블클릭들어간다면
			{
				if( light[i][j].m_bOpen /*여기다 오브젝트 더 추가*/)
				{
					dlgLightEdit.SetPosition(PERCENT(light[i][j].m_nScale));
					//초기값 설정해주기
					if( dlgLightEdit.DoModal() == IDOK)
					{
						light[i][j].m_nScale = DEPERCENT(dlgLightEdit.m_nSliderPos);
						UpdateStats();
						break;
					}
				}
			}

			if( computer[i][j].rectComputer.PtInRect(point)) 	//만약에 라이트안에 포인트가 더블클릭들어간다면
			{
				if( computer[i][j].m_bOpen /*여기다 오브젝트 더 추가*/)
				{
					dlgComputerEdit.SetPosition(computer[i][j].m_bTurnOn);
					//초기값 설정해주기
					if( dlgComputerEdit.DoModal() == IDOK)
					{
						computer[i][j].m_bTurnOn = dlgComputerEdit.m_bTurnOn;
						if( !dlgComputerEdit.m_bTurnOn )
							computer[i][j].m_nEnergy = 0;
						else
							computer[i][j].m_nEnergy = computer[i][j].m_nLimitEnergy;
						UpdateStats();
						break;
					}
				}
			}
			if( aircon[i][j].rectAircon.PtInRect(point)) 	//만약에 라이트안에 포인트가 더블클릭들어간다면
			{
				if( aircon[i][j].m_bOpen /*여기다 오브젝트 더 추가*/)
				{
					dlgComputerEdit.SetPosition(aircon[i][j].m_bTurnOn);
					//초기값 설정해주기
					if( dlgComputerEdit.DoModal() == IDOK)
					{
						aircon[i][j].m_bTurnOn = dlgComputerEdit.m_bTurnOn;
						if( !dlgComputerEdit.m_bTurnOn )
							aircon[i][j].m_nEnergy = 0;
						else
							aircon[i][j].m_nEnergy = aircon[i][j].m_nLimitEnergy;
						UpdateStats();
						break;
					}
				}
			}
			if( printers[i][j].rectPrinter.PtInRect(point)) 	//만약에 라이트안에 포인트가 더블클릭들어간다면
			{
				if( printers[i][j].m_bOpen /*여기다 오브젝트 더 추가*/)
				{
					dlgComputerEdit.SetPosition(printers[i][j].m_bTurnOn);
					//초기값 설정해주기
					if( dlgComputerEdit.DoModal() == IDOK)
					{
						printers[i][j].m_bTurnOn = dlgComputerEdit.m_bTurnOn;
						if( !dlgComputerEdit.m_bTurnOn )
							printers[i][j].m_nEnergy = 0;
						else
							printers[i][j].m_nEnergy = printers[i][j].m_nLimitEnergy;
						UpdateStats();
						break;
					}
				}
			}
			if( eletronic[i][j].rectEle.PtInRect(point)) 	//만약에 라이트안에 포인트가 더블클릭들어간다면
			{
				if( eletronic[i][j].m_bOpen /*여기다 오브젝트 더 추가*/)
				{
					dlgComputerEdit.SetPosition(eletronic[i][j].m_bTurnOn);
					//초기값 설정해주기
					if( dlgComputerEdit.DoModal() == IDOK)
					{
						eletronic[i][j].m_bTurnOn = dlgComputerEdit.m_bTurnOn;
						if( !dlgComputerEdit.m_bTurnOn )
							eletronic[i][j].m_nEnergy = 0;
						else
							eletronic[i][j].m_nEnergy = eletronic[i][j].m_nLimitEnergy;
						UpdateStats();
						break;
					}
				}
			}
		}
	}
	Invalidate(false);
	CView::OnLButtonDblClk(nFlags, point);
}


int CEleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	dlgStats.Create(IDD_DLG_STATS, this);
	dlgStats.ShowWindow(SW_SHOW);

	return 0;
}


void CEleView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	m_nScreenStartSizeX = cx/4;
	m_nScreenEndSizeX = cx - cx/4;
	m_nScreenSizeY = cy;

	dlgStats.SetWindowPos(NULL, -1, -1, cx/4, cy, SWP_NOMOVE | SWP_NOZORDER);
}


void CEleView::OnBldCreate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	if( m_bDrawBldCheck ) {
		MessageBox("이미 생성 되었습니다.", "생성 불가");
		return;
	}
	bool m_bCheck = false;
	if( dlgBld.DoModal() == IDOK)		//dlgBld의 다이얼로그가 OK가 눌리면
	{
		//각 방 마다 최대 몇까지 만들수있는지 설정해주는 알고리즘

		int TileSize = 0; 
		TileSize = m_nScreenStartSizeX;
		int TileIntervalX = (int)m_nScreenEndSizeX / dlgBld.m_nBld_X;
		TileSize += TileIntervalX;

		for(;;)
		{

			if( TileSize - LIGHTSIZEX < LIGHTSIZEX )
				break;

			TileSize = TileSize - LIGHTSIZEX;
			TileLimitedCount++;
		}
		//////////////////////여기까지


		m_nBldX = dlgBld.m_nBld_X*TileLimitedCount;		//x , y의 값을 받아옴
		m_nBldY = dlgBld.m_nBld_Y;
		
		//타일생성
		m_ppTile = new CTile*[m_nBldX];
		for( UINT i = 0; i < m_nBldX; i++)
			m_ppTile[i] = new CTile[m_nBldY];

		for( UINT i = 0; i < m_nBldX; i++ )
		{
			for( UINT j = 0; j < m_nBldY; j++ )
			{
				m_ppTile[i][j].InitTile(m_nBldX, m_nBldY, CRect(0, 0, 0, 0), CRect(0, 0, 0, 0));
			}
		}

		light = new CLight*[m_nBldX];
		for( UINT i = 0; i < m_nBldX; i++)
			light[i] = new CLight[m_nBldY];


		computer = new CComputer*[m_nBldX];
		for( UINT i = 0; i < m_nBldX; i++)
			computer[i] = new CComputer[m_nBldY];

		aircon = new CAircon*[m_nBldX];
		for( UINT i = 0; i < m_nBldX; i++)
			aircon[i] = new CAircon[m_nBldY];

		printers = new CPrinters*[m_nBldX];
		for( UINT i = 0; i < m_nBldX; i++)
			printers[i] = new CPrinters[m_nBldY];

		eletronic = new CEletronic*[m_nBldX];
		for( UINT i = 0; i < m_nBldX; i++)
			eletronic[i] = new CEletronic[m_nBldY];

		human = new CHuman[m_nBldY];

		m_bCheck = true;
	}

	if( !m_bDrawBldCheck && m_bCheck)
	{
		int prevy, nexty, intervaly;
		int prevx, nextx, intervalx;
		prevy = 0;
		nexty = 0;
		prevx = m_nScreenStartSizeX;
		nextx = m_nScreenStartSizeX;

		intervalx = (int) m_nScreenEndSizeX / m_nBldX;
		intervaly = (int) m_nScreenSizeY / m_nBldY;
		for( UINT i = 0; i < m_nBldX; i++ )
		{
			
			nextx+=intervalx;
			for( UINT j = 0; j < m_nBldY; j++ )
			{
				
				nexty+=intervaly;
				
				m_ppTile[i][j].m_rectTile = CRect(prevx, prevy, nextx, nexty);
				prevy = nexty;
			}
			prevy = 0;
			nexty = 0;
			prevx = nextx;
			
		}
		m_bDrawBldCheck = true;

		
		prevy = 0;
		nexty = 0;
		prevx = m_nScreenStartSizeX;
		nextx = m_nScreenStartSizeX;

		intervalx = (int) m_nScreenEndSizeX / (m_nBldX / TileLimitedCount);
		intervaly = (int) m_nScreenSizeY / m_nBldY;
		//뷰타일 지정
		for( UINT i = 0; i < m_nBldX / TileLimitedCount; i++ )
		{

			nextx+=intervalx;
			for( UINT j = 0; j < m_nBldY; j++ )
			{

				nexty+=intervaly;

				m_ppTile[i][j].m_rectViewTile = CRect(prevx, prevy, nextx, nexty);
				prevy = nexty;
			}
			prevy = 0;
			nexty = 0;
			prevx = nextx;

		}
	}


	//각 레이어 몇층인지 넣어주는것
	for( int i = 0; i < m_nBldY; i++ )
	{
		CString str;
		str.Format("%d층", i+1);
		dlgStats.m_dlgAirconStats.m_ctLayer.AddString(str);
	}
	//이거에러뜸
	//dlgHuman.SettingLayer(m_nBldY);


	//타이머설정
	SetTimer(1, 100, NULL);
	SetTimer(2, 1000, NULL);

	Invalidate(false);
}


void CEleView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	for( UINT i = 0; i < m_nBldX; i++)
	{
		for( UINT j = 0; j < m_nBldY; j++ )
		{
			if( light[i][j].ellLight.PtInRect(point) &&
				light[i][j].m_bOpen && info.m_bInfo /*여기다 오브젝트 더 추가*/)	//만약에 라이트안에 포인트가 들어간다면
			{
				info.m_bInfo = false;		//그리기 !
			}
			if( computer[i][j].rectComputer.PtInRect(point) &&
				computer[i][j].m_bOpen && info.m_bInfo /*여기다 오브젝트 더 추가*/)	//만약에 라이트안에 포인트가 들어간다면
			{
				info.m_bInfo = false;		//그리기 !
			}
			if( aircon[i][j].rectAircon.PtInRect(point) &&
				aircon[i][j].m_bOpen && info.m_bInfo /*여기다 오브젝트 더 추가*/)	//만약에 라이트안에 포인트가 들어간다면
			{
				info.m_bInfo = false;		//그리기 !
			}
			if( printers[i][j].rectPrinter.PtInRect(point) &&
				printers[i][j].m_bOpen && info.m_bInfo /*여기다 오브젝트 더 추가*/)	//만약에 라이트안에 포인트가 들어간다면
			{
				info.m_bInfo = false;		//그리기 !
			}
			if( eletronic[i][j].rectEle.PtInRect(point) &&
				eletronic[i][j].m_bOpen && info.m_bInfo /*여기다 오브젝트 더 추가*/)	//만약에 라이트안에 포인트가 들어간다면
			{
				info.m_bInfo = false;		//그리기 !
			}
		}
	}
	Invalidate(false);

	CView::OnRButtonUp(nFlags, point);
}


void CEleView::OnDeletemode()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}
	MessageBox("삭제모드가 되었습니다.", "삭제!");
	m_nSelectMode = DEL;

}


// 계속해서 상태를 업데이트 한다. 
void CEleView::UpdateStats(void)
{
	
	m_nObjectALLCount = 0;
	m_nObjectALLSum = 0;
	//총 형광등 계산해주는것
	m_nObjectCount[LIGHT] = 0;
	m_nObjectSum[LIGHT] = 0;
	for( UINT i = 0; i < m_nBldX; i++ )
	{
		for( UINT j = 0; j < m_nBldY; j++ )
		{
			if( light[i][j].m_bOpen)	//만약에 상자안에 포인트가 들어간다면
			{
				m_nObjectCount[LIGHT]++;
				m_nObjectSum[LIGHT] += light[i][j].m_nEnergy - (int)((float)PERCENT(light[i][j].m_nScale)/100.f * light[i][j].m_nEnergy);
			}
		}
	}

	//총 컴퓨터 계싼
	m_nObjectCount[COMPUTER] = 0;
	m_nObjectSum[COMPUTER] = 0;
	for( UINT i = 0; i < m_nBldX; i++ )
	{
		for( UINT j = 0; j < m_nBldY; j++ )
		{
			if( computer[i][j].m_bOpen )	//만약에 상자안에 포인트가 들어간다면
			{
				m_nObjectCount[COMPUTER]++;
				if( computer[i][j].m_bTurnOn)
					m_nObjectSum[COMPUTER] += computer[i][j].m_nEnergy;
			}
		}
	}

	//총 에어컨 계싼
	m_nObjectCount[AIRCON] = 0;
	m_nObjectSum[AIRCON] = 0;
	for( UINT i = 0; i < m_nBldX; i++ )
	{
		for( UINT j = 0; j < m_nBldY; j++ )
		{
			if( aircon[i][j].m_bOpen )	//만약에 상자안에 포인트가 들어간다면
			{
				m_nObjectCount[AIRCON]++;
				if( aircon[i][j].m_bTurnOn)
					m_nObjectSum[AIRCON] += aircon[i][j].m_nEnergy;
			}
		}
	}
	//총 프린터 계싼
	m_nObjectCount[PRINTERS] = 0;
	m_nObjectSum[PRINTERS] = 0;
	for( UINT i = 0; i < m_nBldX; i++ )
	{
		for( UINT j = 0; j < m_nBldY; j++ )
		{
			if( printers[i][j].m_bOpen )	//만약에 상자안에 포인트가 들어간다면
			{
				m_nObjectCount[PRINTERS]++;
				if( printers[i][j].m_bTurnOn)
					m_nObjectSum[PRINTERS] += printers[i][j].m_nEnergy;
			}
		}
	}
	//총 전기 계싼
	m_nObjectCount[ELETRONIC] = 0;
	m_nObjectSum[ELETRONIC] = 0;
	for( UINT i = 0; i < m_nBldX; i++ )
	{
		for( UINT j = 0; j < m_nBldY; j++ )
		{
			if( eletronic[i][j].m_bOpen )	//만약에 상자안에 포인트가 들어간다면
			{
				m_nObjectCount[ELETRONIC]++;
				if( eletronic[i][j].m_bTurnOn)
					m_nObjectSum[ELETRONIC] += eletronic[i][j].m_nEnergy;
			}
		}
	}
	
	for( int i = 0; i < MAXOBJECT; i++ )
	{
		m_nObjectALLCount += m_nObjectCount[i];
		m_nObjectALLSum += m_nObjectSum[i];
	}

	dlgStats.m_dlgLightStats.m_nAllCount = m_nObjectALLCount;
	dlgStats.m_dlgLightStats.m_nAllSum = m_nObjectALLSum;

	dlgStats.m_dlgLightStats.m_nLightCount = m_nObjectCount[LIGHT];
	dlgStats.m_dlgLightStats.m_nLightSumVolt = m_nObjectSum[LIGHT];

	dlgStats.m_dlgLightStats.m_nComputerCount = m_nObjectCount[COMPUTER];
	dlgStats.m_dlgLightStats.m_nComputerSum = m_nObjectSum[COMPUTER];

	dlgStats.m_dlgLightStats.m_nAirconCount = m_nObjectCount[AIRCON];
	dlgStats.m_dlgLightStats.m_nAirconSum = m_nObjectSum[AIRCON];

	dlgStats.m_dlgLightStats.m_nPrintersCount = m_nObjectCount[PRINTERS];
	dlgStats.m_dlgLightStats.m_nPrintersSum = m_nObjectSum[PRINTERS];

	dlgStats.m_dlgLightStats.m_nEtcCount = m_nObjectCount[ELETRONIC];
	dlgStats.m_dlgLightStats.m_nEtcSum = m_nObjectSum[ELETRONIC];

	dlgStats.m_dlgLightStats.UpdateData(false);
}




void CEleView::OnComputer()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}
	m_nSelectObject = COMPUTER;
	m_nSelectMode = EDIT;

}


void CEleView::OnAllComputer()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}
	//CDlgTurnOn.SetPosition(127);
	if( dlgComputerEdit.DoModal() == IDOK)
	{
		for( UINT i = 0; i < m_nBldX; i++ )
		{ 
			for( UINT j = 0; j < m_nBldY; j++ )
			{
				if( computer[i][j].m_bOpen)
				{
					computer[i][j].m_bTurnOn = dlgComputerEdit.m_bTurnOn;
					if( !computer[i][j].m_bTurnOn )
						computer[i][j].m_nEnergy = 0;
					else
						computer[i][j].m_nEnergy = computer[i][j].m_nLimitEnergy;
				}
			}
		}
	}
	UpdateStats();
	Invalidate(false);
}


void CEleView::OnPrinter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}
	m_nSelectObject =PRINTERS;
	m_nSelectMode = EDIT;
}


void CEleView::OnEletronic()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}
	m_nSelectObject = ELETRONIC;
	m_nSelectMode = EDIT;

	if( dlgInputName.DoModal() == IDOK)
	{
		strECTName = dlgInputName.m_nObjectName;
	}
	else
	{
		strECTName.Format("전기(기타)");
	}
}


// 오브젝트 크기 설정해주기 
int CEleView::SetObjectHeight(int top, int bottom, int object)
{
	int n = 0;
	/*if( object == LIGHT)
		return top;*/
	n = (bottom - top) / (MAXOBJECT-1);
	int Y = top + (n*object);
	return Y;
}


void CEleView::OnAllAircon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}
	//CDlgTurnOn.SetPosition(127);
	if( dlgComputerEdit.DoModal() == IDOK)
	{
		for( UINT i = 0; i < m_nBldX; i++ )
		{ 
			for( UINT j = 0; j < m_nBldY; j++ )
			{
				if( aircon[i][j].m_bOpen)
				{
					aircon[i][j].m_bTurnOn = dlgComputerEdit.m_bTurnOn;
					if( !aircon[i][j].m_bTurnOn )
						aircon[i][j].m_nEnergy = 0;
					else
						aircon[i][j].m_nEnergy = aircon[i][j].m_nLimitEnergy;
				}
			}
		}
	}
	UpdateStats();
	Invalidate(false);
}


void CEleView::OnAllEtc()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}
	//CDlgTurnOn.SetPosition(127);
	if( dlgComputerEdit.DoModal() == IDOK)
	{
		for( UINT i = 0; i < m_nBldX; i++ )
		{ 
			for( UINT j = 0; j < m_nBldY; j++ )
			{
				if( eletronic[i][j].m_bOpen)
				{
					eletronic[i][j].m_bTurnOn = dlgComputerEdit.m_bTurnOn;
					if( !eletronic[i][j].m_bTurnOn )
						eletronic[i][j].m_nEnergy = 0;
					else
						eletronic[i][j].m_nEnergy = eletronic[i][j].m_nLimitEnergy;
				}
			}
		}
	}
	UpdateStats();
	Invalidate(false);
}


void CEleView::OnAllPrinters()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}
	//CDlgTurnOn.SetPosition(127);
	if( dlgComputerEdit.DoModal() == IDOK)
	{
		for( UINT i = 0; i < m_nBldX; i++ )
		{ 
			for( UINT j = 0; j < m_nBldY; j++ )
			{
				if( printers[i][j].m_bOpen)
				{
					printers[i][j].m_bTurnOn = dlgComputerEdit.m_bTurnOn;
					if( !printers[i][j].m_bTurnOn )
						printers[i][j].m_nEnergy = 0;
					else
						printers[i][j].m_nEnergy = printers[i][j].m_nLimitEnergy;
				}
			}
		}
	}
	UpdateStats();
	Invalidate(false);
}


void CEleView::OnControlLight()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	

}


void CEleView::OnControlHuman()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}

	//int Y = 0;
	//dlgHuman.m_nLayer = m_nBldY;
	//if( dlgHuman.DoModal() == IDOK)
	//{
	//	Y = (m_nBldY - (dlgHuman.GetCursor()));
	//}

	//
	////dlgHuman.SettingLayer(20);
	//int prevY = 0;
	//prevY =  Y*((int) m_nScreenSizeY / m_nBldY);
	//Y--;
	//human[Y].m_bOpen = true;
	//human[Y].m_nX = 500;
	//human[Y].m_nY += prevY;
	//human[Y].rectHuman = CRect(0, 0, 20, 20);
	//human[Y].SettingPngFile();
	//Invalidate(false);
	//
	//수정해야할부분
	//SetTimer(2016, 100, NULL);
	//dlgHuman.SettingLayer(20);
}


BOOL CEleView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return true;
	//return CView::OnEraseBkgnd(pDC);
}


void CEleView::OnZZz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	dlgStats.ShowWindow(SW_SHOW);
}


// 렉트끼리 충돌
bool CEleView::RectColl(CRect rect1, CRect rect2)
{
	if(rect1.left < rect2.right && rect1.top < rect2.bottom &&
		rect1.right > rect2.left && rect1.bottom > rect2.top)
		return true;
	
	return false;
}


void CEleView::OnAlldelHuman()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for( UINT j = 0; j < m_nBldY; j++ )
	{
		if( human[j].m_bOpen )
		{
			human[j].m_nX = -20;
			human[j].m_nY = -20;
			human[j].m_nSpeed = 10;
			human[j].m_bOpen = false;
			human[j].m_bMoveCheck = false;
			human[j].rectHuman = CRect(-20, -20, -20, -20);
			settimercheck = false;
		}
		KillTimer(2016);
	}

	Invalidate(false);
}


void CEleView::OnAddHuman()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	if( !m_bDrawBldCheck )
	{
		MessageBox("빌딩을 먼저 생성하세요.", "빌딩 생성!");
		return;
	}
	int Y = 0;
	dlgHuman.m_nLayer = m_nBldY;
	if( dlgHuman.DoModal() == IDOK)
	{
		Y = (m_nBldY - (dlgHuman.GetCursor()));
	}

	
	//dlgHuman.SettingLayer(20);
	int prevY = 0;
	prevY =  Y*((int) m_nScreenSizeY / m_nBldY);
	Y--;
	human[Y].m_bOpen = true;
	human[Y].m_nX = 500;
	human[Y].m_nY += prevY;
	human[Y].rectHuman = CRect(0, 0, 20, 20);
	human[Y].SettingPngFile();
	Invalidate(false);

	if( !settimercheck )
		SetTimer(2016, 100, NULL);

	settimercheck = true;
}
