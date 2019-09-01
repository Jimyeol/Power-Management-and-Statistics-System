// DlgTurnOn.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgTurnOn.h"
#include "afxdialogex.h"


// CDlgTurnOn ��ȭ �����Դϴ�.

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


// CDlgTurnOn �޽��� ó�����Դϴ�.



void CDlgTurnOn::SetPosition(bool bTurnOn)
{
	m_bTurnOn = bTurnOn;
}
