
// test2Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Ctest2Dlg dialog
class Ctest2Dlg : public CDialogEx
{
// Construction
public:
	Ctest2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TEST2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CEdit m_adda;
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_addb;
	CEdit m_addsum;
	afx_msg void OnCbnSelchangeCombo1();
};
