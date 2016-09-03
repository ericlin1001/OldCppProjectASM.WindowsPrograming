
// singleDocTest1View.h : interface of the CsingleDocTest1View class
//

#pragma once


class CsingleDocTest1View : public CView
{
protected: // create from serialization only
	CsingleDocTest1View();
	DECLARE_DYNCREATE(CsingleDocTest1View)

// Attributes
public:
	CsingleDocTest1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CsingleDocTest1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in singleDocTest1View.cpp
inline CsingleDocTest1Doc* CsingleDocTest1View::GetDocument() const
   { return reinterpret_cast<CsingleDocTest1Doc*>(m_pDocument); }
#endif

