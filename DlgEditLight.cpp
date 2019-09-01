// DlgEditLight.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgEditLight.h"
#include "afxdialogex.h"


// CDlgEditLight ��ȭ �����Դϴ�.

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


// CDlgEditLight �޽��� ó�����Դϴ�.


BOOL CDlgEditLight::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ctrlSlider.SetRange(0, 100);
	m_ctrlSlider.SetPos(100 - m_nGetPos);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CDlgEditLight::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CDialog::DoModal();
}


void CDlgEditLight::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	UpdateData(false);
	CDialog::OnOK();
}
