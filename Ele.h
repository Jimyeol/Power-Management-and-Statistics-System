
// Ele.h : Ele ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CEleApp:
// �� Ŭ������ ������ ���ؼ��� Ele.cpp�� �����Ͻʽÿ�.
//

class CEleApp : public CWinApp
{
public:
	CEleApp();




// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP();

public:
	ULONG_PTR m_gdiplusToken;
	virtual int ExitInstance();
};

extern CEleApp theApp;
