// DlgInputBld.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgInputBld.h"
#include "afxdialogex.h"


// CDlgInputBld 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgInputBld, CDialog)

CDlgInputBld::CDlgInputBld(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInputBld::IDD, pParent)
	, m_nBld_X(0)
	, m_nBld_Y(0)
{

}

CDlgInputBld::~CDlgInputBld()
{
}

void CDlgInputBld::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, m_nBld_X);
	DDV_MinMaxUInt(pDX, m_nBld_X, 1, 15);
	DDX_Text(pDX, IDC_EDIT_Y, m_nBld_Y);
	DDV_MinMaxUInt(pDX, m_nBld_Y, 1, 9);
}


BEGIN_MESSAGE_MAP(CDlgInputBld, CDialog)
END_MESSAGE_MAP()


// CDlgInputBld 메시지 처리기입니다.
