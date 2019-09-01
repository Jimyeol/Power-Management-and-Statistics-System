// DlgStats.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgStats.h"
#include "afxdialogex.h"


// CDlgStats 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgStats, CDialog)

CDlgStats::CDlgStats(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStats::IDD, pParent)
{

}

CDlgStats::~CDlgStats()
{
}

void CDlgStats::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_STATS, m_tapControl);
}


BEGIN_MESSAGE_MAP(CDlgStats, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_STATS, &CDlgStats::OnTcnSelchangeTabStats)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgStats 메시지 처리기입니다.


BOOL CDlgStats::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CreateTapDlg();
	InitControl();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


// 컨트롤 추가
void CDlgStats::InitControl(void)
{
	m_tapControl.InsertItem(0, "전체");
	m_tapControl.InsertItem(1, "각층");
}


// 탭 다이얼로그 생성
void CDlgStats::CreateTapDlg(void)
{
	CRect rCtrl;

	m_tapControl.GetWindowRect(&rCtrl);
	ScreenToClient(&rCtrl);

	rCtrl.top += 20;
	rCtrl.left += 5;
	rCtrl.right -= 5;
	rCtrl.bottom -= 5;

	m_dlgLightStats.Create(CDlgLightStats::IDD, this);
	m_dlgLightStats.MoveWindow(rCtrl);
	m_dlgLightStats.ShowWindow(SW_SHOW);

	m_dlgAirconStats.Create(CDlgAirconeStats::IDD, this);
	m_dlgAirconStats.MoveWindow(rCtrl);
}


void CDlgStats::OnTcnSelchangeTabStats(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		int nSelectItem = 0;
	nSelectItem = m_tapControl.GetCurSel();

	switch( nSelectItem )
	{
	case 0:
		m_dlgLightStats.ShowWindow(SW_SHOW);
		m_dlgAirconStats.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_dlgLightStats.ShowWindow(SW_HIDE);
		m_dlgAirconStats.ShowWindow(SW_SHOW);
		break;
	}

	*pResult = 0;
}




BOOL CDlgStats::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return false;
	//return CDialog::OnEraseBkgnd(pDC);
}


BOOL CDlgStats::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message == WM_KEYDOWN)
	{
	
		if(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return true;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
