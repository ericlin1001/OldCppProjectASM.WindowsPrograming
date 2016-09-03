
// singleDocTest1View.cpp : implementation of the CsingleDocTest1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "singleDocTest1.h"
#endif

#include "singleDocTest1Doc.h"
#include "singleDocTest1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsingleDocTest1View

IMPLEMENT_DYNCREATE(CsingleDocTest1View, CView)

BEGIN_MESSAGE_MAP(CsingleDocTest1View, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CsingleDocTest1View construction/destruction

CsingleDocTest1View::CsingleDocTest1View()
{
	// TODO: add construction code here

}

CsingleDocTest1View::~CsingleDocTest1View()
{
}

BOOL CsingleDocTest1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CsingleDocTest1View drawing

void CsingleDocTest1View::OnDraw(CDC* pdc/*pDC*/)
{
	CsingleDocTest1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	/*pdc->TextOut(100,100,"texout");
	pdc->SetPixel(10,10,RGB(0,0,255));
	//
	CPen pen;
	pen.CreatePen(PS_SOLID,2,RGB(128,128,128));
	//CPen * pOldPen=(CPen *)pdc->SelectObject(pen);
	//
//	pdc->SelectObject(pOldPen);
	//
	pen.DeleteObject();
pen.CreatePen(PS_SOLID,2,RGB(128,128,128));
CPen* pOldPen=(CPen*)pdc->SelectObject(&pen);
pdc->SelectStockObject(NULL_BRUSH);//选入空刷子
pdc->Rectangle(CRect(0,0,20,20));//画矩形
//
CRectRgn r;*/
	CPen pen;
	pen.CreatePen(PS_SOLID,2,RGB(128,0,0));
	CPen * pOldPen=(CPen *)pdc->SelectObject(pen);
	CsingleDocTest1Doc *pdoc=this->GetDocument();
	if(pdoc->getPointCount()>0)pdc->MoveTo(pdoc->getHeadPoint().x,pdoc->getHeadPoint().y);
	/**/for(int i=1;i<pdoc->getPointCount();i++){
		MyPoint *p=&pdoc->m_pointList[i];
		pdc->LineTo(p->x,p->y);
	}
	//
	pdc->SelectObject(pOldPen);
}


// CsingleDocTest1View diagnostics

#ifdef _DEBUG
void CsingleDocTest1View::AssertValid() const
{
	CView::AssertValid();
}

void CsingleDocTest1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CsingleDocTest1Doc* CsingleDocTest1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CsingleDocTest1Doc)));
	return (CsingleDocTest1Doc*)m_pDocument;
}
#endif //_DEBUG


// CsingleDocTest1View message handlers


void CsingleDocTest1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CsingleDocTest1Doc *pdoc=this->GetDocument();
	pdoc->addPoint(point.x,point.y);

	this->Invalidate(1);
	this->UpdateWindow();
	CView::OnLButtonDown(nFlags, point);

	
}


void CsingleDocTest1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnMouseMove(nFlags, point);
}


void CsingleDocTest1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CMenu menu;
	menu.LoadMenu(ID_FILE_NEW);
	CMenu* pM=menu.GetSubMenu(0);
	CPoint pt;
	GetCursorPos(&pt);
	pM->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
	CView::OnLButtonUp(nFlags, point);
}
