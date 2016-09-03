
// singleDocTest1.h : main header file for the singleDocTest1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CsingleDocTest1App:
// See singleDocTest1.cpp for the implementation of this class
//

class CsingleDocTest1App : public CWinApp
{
public:
	CsingleDocTest1App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CsingleDocTest1App theApp;
