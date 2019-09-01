// DlgHuman.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgHuman.h"
#include "afxdialogex.h"


// CDlgHuman 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgHuman, CDialog)

CDlgHuman::CDlgHuman(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHuman::IDD, pParent)
{
	m_nLayer = 0;
	m_nCur = 0;
}

CDlgHuman::~CDlgHuman()
{
}

void CDlgHuman::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_HUMAN_LAYER, m_ctLayerHuman);
}


BEGIN_MESSAGE_MAP(CDlgHuman, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_HUMAN_LAYER, &CDlgHuman::OnCbnSelchangeComboHumanLayer)
	ON_CBN_SELENDOK(IDC_COMBO_HUMAN_LAYER, &CDlgHuman::OnCbnSelendokComboHumanLayer)
	ON_CBN_SETFOCUS(IDC_COMBO_HUMAN_LAYER, &CDlgHuman::OnCbnSetfocusComboHumanLayer)
END_MESSAGE_MAP()


// 세팅 레이어 


void CDlgHuman::SettingLayer(int Y)
{

}

int CDlgHuman::GetCursor()
{
	return m_nCur;
}

BOOL CDlgHuman::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	/*int Y = 20;
	for( int i = 0; i < Y; i++ )
	{
		CString str;
		str.Format("%d층", i+1);
		m_ctLayerHuman.AddString(str);
	}*/
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgHuman::OnCbnSelchangeComboHumanLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void CDlgHuman::OnCbnSelendokComboHumanLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nCur = m_ctLayerHuman.GetCurSel();
	
}


void CDlgHuman::OnCbnSetfocusComboHumanLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	for( int i = 0; i < m_nLayer; i++ )
	{
		CString str;
		str.Format("%d층", i+1);
		m_ctLayerHuman.AddString(str);
	}
}
