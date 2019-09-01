// DlgEtcInput.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgEtcInput.h"
#include "afxdialogex.h"


// CDlgEtcInput 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgEtcInput, CDialog)

CDlgEtcInput::CDlgEtcInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEtcInput::IDD, pParent)
	, m_nObjectName(_T(""))
{

}

CDlgEtcInput::~CDlgEtcInput()
{
}

void CDlgEtcInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OBJECT_NAME, m_nObjectName);
	DDV_MaxChars(pDX, m_nObjectName, 10);
}


BEGIN_MESSAGE_MAP(CDlgEtcInput, CDialog)
END_MESSAGE_MAP()


// CDlgEtcInput 메시지 처리기입니다.
