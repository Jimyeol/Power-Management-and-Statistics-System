// DlgTurnOn.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgTurnOn.h"
#include "afxdialogex.h"


// CDlgTurnOn 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgTurnOn, CDialog)

CDlgTurnOn::CDlgTurnOn(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTurnOn::IDD, pParent)
	, m_bTurnOn(FALSE)
{

}

CDlgTurnOn::~CDlgTurnOn()
{
}

void CDlgTurnOn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_TURN, m_ctCheckTurn);
	DDX_Check(pDX, IDC_CHECK_TURN, m_bTurnOn);
}


BEGIN_MESSAGE_MAP(CDlgTurnOn, CDialog)
END_MESSAGE_MAP()


// CDlgTurnOn 메시지 처리기입니다.



void CDlgTurnOn::SetPosition(bool bTurnOn)
{
	m_bTurnOn = bTurnOn;
}
