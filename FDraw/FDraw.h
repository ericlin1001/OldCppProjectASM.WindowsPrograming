// FDraw.h : main header file for the FDRAW application
//

#if !defined(AFX_FDRAW_H__67AA72BB_44DA_41C2_80E1_14156364218A__INCLUDED_)
#define AFX_FDRAW_H__67AA72BB_44DA_41C2_80E1_14156364218A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFDrawApp:
// See FDraw.cpp for the implementation of this class
//

class CFDrawApp : public CWinApp
{
public:
	CFDrawApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFDrawApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFDrawApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FDRAW_H__67AA72BB_44DA_41C2_80E1_14156364218A__INCLUDED_)
