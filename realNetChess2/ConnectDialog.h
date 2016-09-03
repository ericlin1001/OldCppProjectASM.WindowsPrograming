#if !defined(AFX_CONNECTDIALOG_H__BE3DE74B_63CB_4C55_AC74_D750CA766DCB__INCLUDED_)
#define AFX_CONNECTDIALOG_H__BE3DE74B_63CB_4C55_AC74_D750CA766DCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnectDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConnectDialog dialog

class CConnectDialog : public CDialog
{
// Construction
public:
	CConnectDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConnectDialog)
	enum { IDD = IDD_CONNECT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectDialog)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConnectDialog)
	afx_msg void OnConnect();
	afx_msg void OnChooseConnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CConnectDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTDIALOG_H__BE3DE74B_63CB_4C55_AC74_D750CA766DCB__INCLUDED_)
