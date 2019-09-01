// DlgHuman.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgHuman.h"
#include "afxdialogex.h"


// CDlgHuman ��ȭ �����Դϴ�.

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


// ���� ���̾� 


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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	/*int Y = 20;
	for( int i = 0; i < Y; i++ )
	{
		CString str;
		str.Format("%d��", i+1);
		m_ctLayerHuman.AddString(str);
	}*/
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CDlgHuman::OnCbnSelchangeComboHumanLayer()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}


void CDlgHuman::OnCbnSelendokComboHumanLayer()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_nCur = m_ctLayerHuman.GetCurSel();
	
}


void CDlgHuman::OnCbnSetfocusComboHumanLayer()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	for( int i = 0; i < m_nLayer; i++ )
	{
		CString str;
		str.Format("%d��", i+1);
		m_ctLayerHuman.AddString(str);
	}
}
