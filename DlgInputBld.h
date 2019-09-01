#pragma once


// CDlgInputBld 대화 상자입니다.

class CDlgInputBld : public CDialog
{
	DECLARE_DYNAMIC(CDlgInputBld)

public:
	CDlgInputBld(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgInputBld();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_INPUT_BLD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 빌딩의 x값을 입력
	UINT m_nBld_X;
	// 빌딩의 Y값을 입력
	UINT m_nBld_Y;
};
