// DlgLightStats.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgLightStats.h"
#include "afxdialogex.h"
#include "Customdc.h"


// CDlgLightStats 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgLightStats, CDialogEx)

CDlgLightStats::CDlgLightStats(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLightStats::IDD, pParent)
	, m_nLightCount(0)
	, m_nLightSumVolt(0)
	, m_strPercent(_T("현재 오브젝트가 없습니다"))
	, m_nAllSum(0)
	, m_nAllCount(0)
	, m_nComputerCount(0)
	, m_nComputerSum(0)
	, m_nAirconCount(0)
	, m_nAirconSum(0)
	, m_nPrintersCount(0)
	, m_nPrintersSum(0)
	, m_nEtcCount(0)
	, m_nEtcSum(0)
{
	m_nPercent = 0;
}

CDlgLightStats::~CDlgLightStats()
{
}

void CDlgLightStats::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nLightCount);
	DDX_Control(pDX, IDC_EDIT1, m_ctLineCount);
	DDX_Text(pDX, IDC_EDIT_LIGHTSUM, m_nLightSumVolt);
	DDX_Control(pDX, IDC_STATIC_PERCENT, m_stPercent);
	DDX_Text(pDX, IDC_STATIC_PERCENT, m_strPercent);
	DDX_Text(pDX, IDC_EDIT__ALL_SUM, m_nAllSum);
	DDX_Text(pDX, IDC_EDIT_ALL_COUNT, m_nAllCount);
	DDX_Text(pDX, IDC_EDIT_COMPUTER_COUNT, m_nComputerCount);
	DDX_Text(pDX, IDC_EDIT_COMPUER_SUM, m_nComputerSum);
	DDX_Text(pDX, IDC_EDIT_AIRCON_COUNT, m_nAirconCount);
	DDX_Text(pDX, IDC_EDIT_AIRCON_SUM, m_nAirconSum);
	DDX_Text(pDX, IDC_EDIT_PRINTERS_COUNT, m_nPrintersCount);
	DDX_Text(pDX, IDC_EDIT_PRINTERS_SUM, m_nPrintersSum);
	DDX_Text(pDX, IDC_EDIT_ETC_COUNT, m_nEtcCount);
	DDX_Text(pDX, IDC_EDIT_ETC_SUM, m_nEtcSum);
}


BEGIN_MESSAGE_MAP(CDlgLightStats, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CDlgLightStats::OnEnChangeEdit1)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgLightStats 메시지 처리기입니다.


BOOL CDlgLightStats::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pViewGraph = new CTotalGraph();

	m_pViewGraph->Create(NULL, "", WS_CHILD | WS_BORDER | WS_VISIBLE, GRAPHSIZE, 
		this, 1024);
	//this->ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	m_pViewGraph->OnInitialUpdate();

	m_nLightCount = 0;

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgLightStats::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(false);
}


void CDlgLightStats::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	delete m_pViewGraph;
}


void CDlgLightStats::InitStatic(int nSum)
{
	if( nSum < 0 )
		return;
	m_nPercent = nSum;
	m_strPercent.Format("전체 전력량의 \n %d 퍼센트 사용중", m_nPercent);
	UpdateData(false);
}


void CDlgLightStats::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CBitmap bitmap;
	bitmap.LoadBitmapA(IDB_BITMAP2);
	BITMAP bmpinfo;
	bitmap.GetBitmap(&bmpinfo);

	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	dcmem.SelectObject(&bitmap);

	dc.BitBlt(10, 0, bmpinfo.bmWidth, bmpinfo.bmHeight,
		&dcmem, 0, 0, SRCCOPY);

	GetDlgItem(IDC_EDIT_ALL_COUNT)->Invalidate(false);

}


BOOL CDlgLightStats::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return false;
	//return CDialogEx::OnEraseBkgnd(pDC);
}
