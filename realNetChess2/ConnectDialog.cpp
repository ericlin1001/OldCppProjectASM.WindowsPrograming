// ConnectDialog.cpp : implementation file
//

#include "stdafx.h"
#include "netchess.h"
#include "ConnectDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectDialog dialog


CConnectDialog::CConnectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDialog::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CConnectDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConnectDialog::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CConnectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectDialog, CDialog)
	//{{AFX_MSG_MAP(CConnectDialog)
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_COMMAND(ID_CONNECT, OnChooseConnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CConnectDialog, CDialog)
	//{{AFX_DISPATCH_MAP(CConnectDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IConnectDialog to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {8499670B-D7FD-48EA-A54B-7348970D8302}
static const IID IID_IConnectDialog =
{ 0x8499670b, 0xd7fd, 0x48ea, { 0xa5, 0x4b, 0x73, 0x48, 0x97, 0xd, 0x83, 0x2 } };

BEGIN_INTERFACE_MAP(CConnectDialog, CDialog)
	INTERFACE_PART(CConnectDialog, IID_IConnectDialog, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectDialog message handlers

void CConnectDialog::OnConnect() 
{
MessageBox("con","",0);
}

void CConnectDialog::OnChooseConnect() 
{
tt	
}
