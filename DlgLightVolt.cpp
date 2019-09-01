// DlgLightVolt.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgLightVolt.h"
#include "afxdialogex.h"


// CDlgLightVolt 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgLightVolt, CDialogEx)

CDlgLightVolt::CDlgLightVolt(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLightVolt::IDD, pParent)
	, m_nVolt(0)
{

}

CDlgLightVolt::~CDlgLightVolt()
{
}

void CDlgLightVolt::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VOLT, m_nVolt);
	DDV_MinMaxUInt(pDX, m_nVolt, 1, 1000);
}


BEGIN_MESSAGE_MAP(CDlgLightVolt, CDialogEx)
END_MESSAGE_MAP()


// CDlgLightVolt 메시지 처리기입니다.
