// DlgEditLight.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgEditLight.h"
#include "afxdialogex.h"


// CDlgEditLight 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgEditLight, CDialog)

CDlgEditLight::CDlgEditLight(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditLight::IDD, pParent)
{
	m_nSliderPos = 0;
	m_nGetPos = 0;
}

CDlgEditLight::~CDlgEditLight()
{
}

void CDlgEditLight::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_ctrlSlider);
}


BEGIN_MESSAGE_MAP(CDlgEditLight, CDialog)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CDlgEditLight::OnNMReleasedcaptureSlider1)
END_MESSAGE_MAP()


// CDlgEditLight 메시지 처리기입니다.


BOOL CDlgEditLight::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_ctrlSlider.SetRange(0, 100);
	m_ctrlSlider.SetPos(100 - m_nGetPos);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgEditLight::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int n = 100 - m_ctrlSlider.GetPos();
	m_nSliderPos = n;
	*pResult = 0;
}


void CDlgEditLight::SetPosition(int nPos)
{
	if( nPos > 100 && nPos < 0 )
		return;

	m_nGetPos = nPos;
	
}

INT_PTR CDlgEditLight::DoModal()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialog::DoModal();
}


void CDlgEditLight::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	UpdateData(false);
	CDialog::OnOK();
}
