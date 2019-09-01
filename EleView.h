
// EleView.h : CEleView 클래스의 인터페이스
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
	//인포메이션창
	bool m_bInfo;
	CRect rectInfoForm;
	CString infoName; //사용 기기
	CString infoStrFloor;	//몇층몆번째
	CString infoStrVolt;	//최대몇볼트
	CString infoCurrentVolt; //현재 볼트
	CString infoPercent; //몇퍼센트 사용중인지

};
class CEleView : public CView
{
protected: // serialization에서만 만들어집니다.
	CEleView();
	DECLARE_DYNCREATE(CEleView)

// 특성입니다.
public:
	CEleDoc* GetDocument() const;

// 작업입니다.
public:
	CDlgInputBld dlgBld;
	UINT m_nBldX;
	UINT m_nBldY;

	CPoint prevPoint;
	CPoint currentPoint;

	int m_nDrawBldCheck;
	bool m_bDrawBldCheck;

	CTile **m_ppTile;	//건물의 타일


	CDlgStats dlgStats;

	Information info;


	//비트맵 알파 
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


	int TileLimitedCount; //각 타일의 최대한몇개만들수있는지 평가 변수



	int m_nTileSize;
	CRect HelpBtnRect;
	CRect backBtnRect;
	bool bHelpBtn;
	bool settimercheck;



//오브젝트
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

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CEleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

	// 계속해서 상태를 업데이트 한다. 
	void UpdateStats(void);
	afx_msg void OnComputer();
	afx_msg void OnAllComputer();
	afx_msg void OnPrinter();
	afx_msg void OnEletronic();
private:
	// 오브젝트 크기 설정해주기 
	int SetObjectHeight(int top, int bottom, int object);
public:
	afx_msg void OnAllAircon();
	afx_msg void OnAllEtc();
	afx_msg void OnAllPrinters();
	afx_msg void OnControlLight();
	afx_msg void OnControlHuman();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnZZz();
	// 렉트끼리 충돌
	bool RectColl(CRect rect1, CRect rect2);
	afx_msg void OnAlldelHuman();
	afx_msg void OnAddHuman();
};

#ifndef _DEBUG  // EleView.cpp의 디버그 버전
inline CEleDoc* CEleView::GetDocument() const
   { return reinterpret_cast<CEleDoc*>(m_pDocument); }
#endif

