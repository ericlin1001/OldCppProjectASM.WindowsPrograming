#pragma once


// CTestPanel dialog

class CTestPanel : public CDialogEx
{
	DECLARE_DYNAMIC(CTestPanel)

public:
	CTestPanel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTestPanel();

// Dialog Data
	enum { IDD = IDD_FORMVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
