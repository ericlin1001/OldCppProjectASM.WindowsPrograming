
// singleDocTest1Doc.h : interface of the CsingleDocTest1Doc class
//

#include<vector>
using namespace std;
#pragma once

class MyPoint{
public:
	MyPoint(){
		assign(0,0);
	}
	 operator int*(){
		 return (int *)p;
	}
	int  operator[](const int i){
		 return this->p[i];
	 }
	MyPoint(int x,int y){
		assign(x,y);
	}
	void assign(int x,int y){
		this->x=x;
		this->y=y;
		
	}
public:
	union{
		struct{int x,y;};
		struct{int p[2];};
	};
};
class CsingleDocTest1Doc : public CDocument
{
protected: // create from serialization only
	CsingleDocTest1Doc();
	DECLARE_DYNCREATE(CsingleDocTest1Doc)

// Attributes
public:
	vector<MyPoint> m_pointList;
	void addPoint(int x,int y){
		MyPoint tmp(x,y);
		this->m_pointList.push_back(tmp);
	}
	int getPointCount(){
		return this->m_pointList.size();
	}
	MyPoint getHeadPoint(){
		return this->m_pointList.front();
	}

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CsingleDocTest1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
