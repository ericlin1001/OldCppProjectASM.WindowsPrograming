// TestPanel.cpp : implementation file
//

#include "stdafx.h"
#include "singleDocTest1.h"
#include "TestPanel.h"
#include "afxdialogex.h"


// CTestPanel dialog

IMPLEMENT_DYNAMIC(CTestPanel, CDialogEx)

CTestPanel::CTestPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestPanel::IDD, pParent)
{

}

CTestPanel::~CTestPanel()
{
}

void CTestPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestPanel, CDialogEx)
END_MESSAGE_MAP()


// CTestPanel message handlers
