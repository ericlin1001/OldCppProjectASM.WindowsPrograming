#include "stdafx.h"

#define IDB_BUTTON 100//1-99 is reversed.
//
class CHelloApp:public CWinApp{
public :
	virtual BOOL InitInstance();
};
CHelloApp theApp;
class CHelloWindow:public CFrameWnd{
	CStatic *cs;
	CButton *bt;

public:
	CHelloWindow();
	//
	afx_msg void onBtnClick();
	afx_msg void OnTimer(UINT t){
		MessageBeep(-11);
	}
	afx_msg void OnSize(UINT nType,int cx,int cy){
		CRect r;
		GetClientRect(&r);
		r.InflateRect(-20,-20);
		bt->MoveWindow(r);
	}
	DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CHelloWindow,CFrameWnd)
	ON_BN_CLICKED(IDB_BUTTON,onBtnClick)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()
//
BOOL CHelloApp::InitInstance(){

	this->m_pMainWnd=new CHelloWindow ();
	this->m_pMainWnd->ShowWindow(this->m_nCmdShow);
	this->m_pMainWnd->UpdateWindow();
	return true;
}
CHelloWindow::CHelloWindow(){
	this->Create(NULL,"hello",WS_OVERLAPPEDWINDOW,CRect(0,0,300,300));
	CRect r;
	GetClientRect(&r);
	r.SetRect(100,100,200,200);
	//

	SetTimer(102,1000,NULL);
	cs=new CStatic();
	cs->Create("helloworld",WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(0,0,100,100),this);
	//
	bt=new CButton();

	bt->Create("bt",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,r,this,IDB_BUTTON);

}
void CHelloWindow::onBtnClick(){
	cs->SetWindowTextA("onclick");
	MessageBeep(-1);
}

