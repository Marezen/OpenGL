
// 18.01.2016.h : main header file for the 18.01.2016 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy18012016App:
// See 18.01.2016.cpp for the implementation of this class
//

class CMy18012016App : public CWinApp
{
public:
	CMy18012016App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy18012016App theApp;
