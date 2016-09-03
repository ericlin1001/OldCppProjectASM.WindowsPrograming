
// singleDocTest1Doc.cpp : implementation of the CsingleDocTest1Doc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "singleDocTest1.h"
#endif

#include "singleDocTest1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CsingleDocTest1Doc

IMPLEMENT_DYNCREATE(CsingleDocTest1Doc, CDocument)

BEGIN_MESSAGE_MAP(CsingleDocTest1Doc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CsingleDocTest1Doc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CsingleDocTest1Doc::OnUpdateFileSendMail)
END_MESSAGE_MAP()


// CsingleDocTest1Doc construction/destruction

CsingleDocTest1Doc::CsingleDocTest1Doc()
{
	// TODO: add one-time construction code here

}

CsingleDocTest1Doc::~CsingleDocTest1Doc()
{
}

BOOL CsingleDocTest1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CsingleDocTest1Doc serialization

void CsingleDocTest1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		for(int i=0;i<this->getPointCount();i++){
			ar<<this->m_pointList[i].x<<this->m_pointList[i].y;
		}
		int endx=-1;
		ar<<endx;
		ar.Flush();
		// TODO: add storing code here
	}
	else
	{
		int x,y;
		do{
			ar>>x;
			if(x==-1)break;
			ar>>y;
			this->addPoint(x,y);
		}while(1);
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CsingleDocTest1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CsingleDocTest1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CsingleDocTest1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CsingleDocTest1Doc diagnostics

#ifdef _DEBUG
void CsingleDocTest1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CsingleDocTest1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CsingleDocTest1Doc commands
