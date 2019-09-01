
// EleView.h : CEleView Ŭ������ �������̽�
//

#pragma once

#include "DlgInputBld.h"

#include "Light.h"
#include "Computer.h"
#include "Aircon.h"
#include "Printers.h"
#include "Eletronic.h"
#include "DlgEtcInput.h"
#include "Human.h"

#include "DlgStats.h"
#include "Tile.h"
#include "DlgLightVolt.h"
#include "Customdc.h"
#include "DlgEditLight.h"
#include "DlgTurnOn.h"
#include "DlgHuman.h"



#define LIGHTSIZEX 100
#define COUNT 7

enum
{
	VOLTEDIT = 0,
	EDIT,
	DEL,
	VIEW,
};

struct Information
{
	//�������̼�â
	bool m_bInfo;
	CRect rectInfoForm;
	CString infoName; //��� ���
	CString infoStrFloor;	//�����p��°
	CString infoStrVolt;	//�ִ�Ʈ
	CString infoCurrentVolt; //���� ��Ʈ
	CString infoPercent; //���ۼ�Ʈ ���������

};
class CEleView : public CView
{
protected: // serialization������ ��������ϴ�.
	CEleView();
	DECLARE_DYNCREATE(CEleView)

// Ư���Դϴ�.
public:
	CEleDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	CDlgInputBld dlgBld;
	UINT m_nBldX;
	UINT m_nBldY;

	CPoint prevPoint;
	CPoint currentPoint;

	int m_nDrawBldCheck;
	bool m_bDrawBldCheck;

	CTile **m_ppTile;	//�ǹ��� Ÿ��


	CDlgStats dlgStats;

	Information info;


	//��Ʈ�� ���� 
	CBitmap alpha;
	CDlgEditLight dlgLightEdit;
	CDlgTurnOn dlgComputerEdit;
	CDlgHuman dlgHuman;

	int m_nScreenEndSizeX;
	int m_nScreenStartSizeX;
	int m_nScreenSizeY;

	int m_nObjectCount[MAXOBJECT];
	int m_nObjectSum[MAXOBJECT];
	int m_nObjectALLCount;
	int m_nObjectALLSum;


	int TileLimitedCount; //�� Ÿ���� �ִ��Ѹ������ִ��� �� ����



	int m_nTileSize;
	CRect HelpBtnRect;
	CRect backBtnRect;
	bool bHelpBtn;
	bool settimercheck;



//������Ʈ
public:
	int						m_nSelectMode;
	int						m_nSelectObject;


	CLight**				light;
	CComputer**				computer;
	CAircon**				aircon;
	CPrinters**				printers;
	CEletronic**			eletronic;
	CDlgEtcInput			dlgInputName;
	CHuman*					human;
	CString					strECTName;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CEleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnAddLight();
	afx_msg void OnAddAircon();
	afx_msg void OnView();
	afx_msg void OnStats();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditLight();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBldCreate();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDeletemode();

	// ����ؼ� ���¸� ������Ʈ �Ѵ�. 
	void UpdateStats(void);
	afx_msg void OnComputer();
	afx_msg void OnAllComputer();
	afx_msg void OnPrinter();
	afx_msg void OnEletronic();
private:
	// ������Ʈ ũ�� �������ֱ� 
	int SetObjectHeight(int top, int bottom, int object);
public:
	afx_msg void OnAllAircon();
	afx_msg void OnAllEtc();
	afx_msg void OnAllPrinters();
	afx_msg void OnControlLight();
	afx_msg void OnControlHuman();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnZZz();
	// ��Ʈ���� �浹
	bool RectColl(CRect rect1, CRect rect2);
	afx_msg void OnAlldelHuman();
	afx_msg void OnAddHuman();
};

#ifndef _DEBUG  // EleView.cpp�� ����� ����
inline CEleDoc* CEleView::GetDocument() const
   { return reinterpret_cast<CEleDoc*>(m_pDocument); }
#endif

