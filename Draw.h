
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       


// CDrawApp:


class CDrawApp : public CWinAppEx
{
public:
	CDrawApp();



public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();


	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDrawApp theApp;
