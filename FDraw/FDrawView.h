// FDrawView.h : interface of the CFDrawView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FDRAWVIEW_H__FF8EB062_2606_4672_A432_7682A1BC3C5A__INCLUDED_)
#define AFX_FDRAWVIEW_H__FF8EB062_2606_4672_A432_7682A1BC3C5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFDrawView : public CScrollView
{
protected: // create from serialization only
	CFDrawView();
	DECLARE_DYNCREATE(CFDrawView)

// Attributes
public:
	CFDrawDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFDrawView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFDrawView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FDrawView.cpp
inline CFDrawDoc* CFDrawView::GetDocument()
   { return (CFDrawDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FDRAWVIEW_H__FF8EB062_2606_4672_A432_7682A1BC3C5A__INCLUDED_)
