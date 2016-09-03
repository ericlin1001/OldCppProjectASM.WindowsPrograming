// FDrawDoc.cpp : implementation of the CFDrawDoc class
//

#include "stdafx.h"
#include "FDraw.h"

#include "FDrawDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFDrawDoc

IMPLEMENT_DYNCREATE(CFDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CFDrawDoc, CDocument)
	//{{AFX_MSG_MAP(CFDrawDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFDrawDoc construction/destruction

CFDrawDoc::CFDrawDoc()
{
	// TODO: add one-time construction code here

}

CFDrawDoc::~CFDrawDoc()
{
}

BOOL CFDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFDrawDoc serialization

void CFDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFDrawDoc diagnostics

#ifdef _DEBUG
void CFDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFDrawDoc commands
