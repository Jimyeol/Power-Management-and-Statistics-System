// DlgStats.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgStats.h"
#include "afxdialogex.h"


// CDlgStats ��ȭ �����Դϴ�.

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


// CDlgStats �޽��� ó�����Դϴ�.


BOOL CDlgStats::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	CreateTapDlg();
	InitControl();


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


// ��Ʈ�� �߰�
void CDlgStats::InitControl(void)
{
	m_tapControl.InsertItem(0, "��ü");
	m_tapControl.InsertItem(1, "����");
}


// �� ���̾�α� ����
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return false;
	//return CDialog::OnEraseBkgnd(pDC);
}


BOOL CDlgStats::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->message == WM_KEYDOWN)
	{
	
		if(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return true;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
