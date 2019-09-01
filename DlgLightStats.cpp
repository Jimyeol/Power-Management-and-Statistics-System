// DlgLightStats.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Ele.h"
#include "DlgLightStats.h"
#include "afxdialogex.h"
#include "Customdc.h"


// CDlgLightStats ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgLightStats, CDialogEx)

CDlgLightStats::CDlgLightStats(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLightStats::IDD, pParent)
	, m_nLightCount(0)
	, m_nLightSumVolt(0)
	, m_strPercent(_T("���� ������Ʈ�� �����ϴ�"))
	, m_nAllSum(0)
	, m_nAllCount(0)
	, m_nComputerCount(0)
	, m_nComputerSum(0)
	, m_nAirconCount(0)
	, m_nAirconSum(0)
	, m_nPrintersCount(0)
	, m_nPrintersSum(0)
	, m_nEtcCount(0)
	, m_nEtcSum(0)
{
	m_nPercent = 0;
}

CDlgLightStats::~CDlgLightStats()
{
}

void CDlgLightStats::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nLightCount);
	DDX_Control(pDX, IDC_EDIT1, m_ctLineCount);
	DDX_Text(pDX, IDC_EDIT_LIGHTSUM, m_nLightSumVolt);
	DDX_Control(pDX, IDC_STATIC_PERCENT, m_stPercent);
	DDX_Text(pDX, IDC_STATIC_PERCENT, m_strPercent);
	DDX_Text(pDX, IDC_EDIT__ALL_SUM, m_nAllSum);
	DDX_Text(pDX, IDC_EDIT_ALL_COUNT, m_nAllCount);
	DDX_Text(pDX, IDC_EDIT_COMPUTER_COUNT, m_nComputerCount);
	DDX_Text(pDX, IDC_EDIT_COMPUER_SUM, m_nComputerSum);
	DDX_Text(pDX, IDC_EDIT_AIRCON_COUNT, m_nAirconCount);
	DDX_Text(pDX, IDC_EDIT_AIRCON_SUM, m_nAirconSum);
	DDX_Text(pDX, IDC_EDIT_PRINTERS_COUNT, m_nPrintersCount);
	DDX_Text(pDX, IDC_EDIT_PRINTERS_SUM, m_nPrintersSum);
	DDX_Text(pDX, IDC_EDIT_ETC_COUNT, m_nEtcCount);
	DDX_Text(pDX, IDC_EDIT_ETC_SUM, m_nEtcSum);
}


BEGIN_MESSAGE_MAP(CDlgLightStats, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CDlgLightStats::OnEnChangeEdit1)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgLightStats �޽��� ó�����Դϴ�.


BOOL CDlgLightStats::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_pViewGraph = new CTotalGraph();

	m_pViewGraph->Create(NULL, "", WS_CHILD | WS_BORDER | WS_VISIBLE, GRAPHSIZE, 
		this, 1024);
	//this->ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	m_pViewGraph->OnInitialUpdate();

	m_nLightCount = 0;

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CDlgLightStats::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(false);
}


void CDlgLightStats::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	delete m_pViewGraph;
}


void CDlgLightStats::InitStatic(int nSum)
{
	if( nSum < 0 )
		return;
	m_nPercent = nSum;
	m_strPercent.Format("��ü ���·��� \n %d �ۼ�Ʈ �����", m_nPercent);
	UpdateData(false);
}


void CDlgLightStats::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

	CBitmap bitmap;
	bitmap.LoadBitmapA(IDB_BITMAP2);
	BITMAP bmpinfo;
	bitmap.GetBitmap(&bmpinfo);

	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	dcmem.SelectObject(&bitmap);

	dc.BitBlt(10, 0, bmpinfo.bmWidth, bmpinfo.bmHeight,
		&dcmem, 0, 0, SRCCOPY);

	GetDlgItem(IDC_EDIT_ALL_COUNT)->Invalidate(false);

}


BOOL CDlgLightStats::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return false;
	//return CDialogEx::OnEraseBkgnd(pDC);
}
