// DlgAirconeStats.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgAirconeStats.h"
#include "afxdialogex.h"


// CDlgAirconeStats ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgAirconeStats, CDialogEx)

CDlgAirconeStats::CDlgAirconeStats(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAirconeStats::IDD, pParent)
	, m_nLayerSum(0)
	, m_nObjectCount(0)
	, m_nComputerCounter(0)
	, m_nComputerSum(0)
	, m_nLightCount(0)
	, m_nLightSum(0)
	, m_nAirconCount(0)
	, m_nAirconSum(0)
	, m_nPrintersCount(0)
	, m_nPrintersSum(0)
	, m_nEtcCount(0)
	, m_nEtcSum(0)
{
	m_nCurrentLayer = -1;
}

CDlgAirconeStats::~CDlgAirconeStats()
{
}

void CDlgAirconeStats::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LAYER, m_ctLayer);
	DDX_Control(pDX, IDC_EDIT_LAYERVOLT, m_ctLayerSum);
	DDX_Text(pDX, IDC_EDIT_LAYERVOLT, m_nLayerSum);
	DDX_Text(pDX, IDC_EDIT_LAYER_SUM, m_nObjectCount);
	DDX_Text(pDX, IDC_EDIT_LAYER_COMPUTER_COUNT, m_nComputerCounter);
	DDX_Text(pDX, IDC_EDIT_LAYER_COMPUER_SUM, m_nComputerSum);
	DDX_Text(pDX, IDC_EDIT_LAYER_LIGHT_COUNT, m_nLightCount);
	DDX_Text(pDX, IDC_EDIT_LAYER_LIGHTSUM, m_nLightSum);
	DDX_Text(pDX, IDC_EDIT_LAYER_AIRCON_COUNT, m_nAirconCount);
	DDX_Text(pDX, IDC_EDIT_LAYER_AIRCON_SUM, m_nAirconSum);
	DDX_Text(pDX, IDC_EDIT_LAYER_PRINTERS_COUNT, m_nPrintersCount);
	DDX_Text(pDX, IDC_EDIT_LAYER_PRINTERS_SUM, m_nPrintersSum);
	DDX_Text(pDX, IDC_EDIT_LAYER_ETC_COUNT, m_nEtcCount);
	DDX_Text(pDX, IDC_EDIT_LAYER_ETC_SUM, m_nEtcSum);
}


BEGIN_MESSAGE_MAP(CDlgAirconeStats, CDialogEx)
	ON_CBN_SETFOCUS(IDC_COMBO_LAYER, &CDlgAirconeStats::OnCbnSetfocusComboLayer)
	ON_CBN_SELENDOK(IDC_COMBO_LAYER, &CDlgAirconeStats::OnCbnSelendokComboLayer)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgAirconeStats �޽��� ó�����Դϴ�.


BOOL CDlgAirconeStats::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

//	m_ctLayer.AddString("%d", 23);
	
	//(IDC_COMBO_LAYER, "1��");
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}



void CDlgAirconeStats::OnCbnSetfocusComboLayer()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
}


void CDlgAirconeStats::OnCbnSelendokComboLayer()
{
	m_nCurrentLayer = m_ctLayer.GetCurSel();
	if( m_nCurrentLayer == -1)
		return;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(false);

	//CEleView::Invalidate(false);
}


// �� ���� ���̾� �� �޾ƿ���
void CDlgAirconeStats::SettingLayer(int sum, int count, int *pObjectSum, int *pObjectCount)
{
	m_nLayerSum = sum;
	m_nObjectCount = count;

	m_nComputerCounter = pObjectCount[COMPUTER];
	m_nComputerSum = pObjectSum[COMPUTER];
	m_nLightCount = pObjectCount[LIGHT];
	m_nLightSum = pObjectSum[LIGHT];;
	m_nAirconCount = pObjectCount[AIRCON];
	m_nAirconSum = pObjectSum[AIRCON];;
	m_nPrintersCount = pObjectCount[PRINTERS];
	m_nPrintersSum = pObjectSum[PRINTERS];;
	m_nEtcCount = pObjectCount[ELETRONIC];
	m_nEtcSum = pObjectSum[ELETRONIC];;

	UpdateData(false);
}



void CDlgAirconeStats::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

	CBitmap bitmap;
	bitmap.LoadBitmapA(IDB_BITMAP_TEAM);
	BITMAP bmpinfo;
	bitmap.GetBitmap(&bmpinfo);

	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	dcmem.SelectObject(&bitmap);

	dc.BitBlt(50, 400, bmpinfo.bmWidth, bmpinfo.bmHeight,
		&dcmem, 0, 0, SRCCOPY);
}


BOOL CDlgAirconeStats::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return false;
	//return CDialogEx::OnEraseBkgnd(pDC);
}
