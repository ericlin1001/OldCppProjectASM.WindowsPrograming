// FDrawDoc.h : interface of the CFDrawDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FDRAWDOC_H__D192B7D6_8837_4A48_ABEC_E8460599B1A6__INCLUDED_)
#define AFX_FDRAWDOC_H__D192B7D6_8837_4A48_ABEC_E8460599B1A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFDrawDoc : public CDocument
{
protected: // create from serialization only
	CFDrawDoc();
	DECLARE_DYNCREATE(CFDrawDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFDrawDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFDrawDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FDRAWDOC_H__D192B7D6_8837_4A48_ABEC_E8460599B1A6__INCLUDED_)
