
// UnRegularWin.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUnRegularWinApp:
// �йش����ʵ�֣������ UnRegularWin.cpp
//

class CUnRegularWinApp : public CWinAppEx
{
public:
	CUnRegularWinApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUnRegularWinApp theApp;