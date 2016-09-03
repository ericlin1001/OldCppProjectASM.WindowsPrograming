#include "CMouseHook.h"

CMouseHook::CMouseHook(){
}
CMouseHook::~CMouseHook(){
	StopHook();
}
BOOL CMouseHook::StartHook(HWND hWnd){
	BOOL bResult=FALSE;
	glhHook=SetWindowsHookEx(WH_MOUSE,MouseProc,glhInstance,0);
	if(glhHook!=NULL)bResult=TRUE;
	glhDisplayWnd=hWnd;
	return bResult;
}
BOOL CMouseHook::StopHook(){
	BOOL bResult=FALSE;
	if(glhHook){
		bResult=UnhookWindowsHookEx(glhHook);
		if(bResult){
			glhPrevTartWnd=NULL;
			glhDisplayWnd=NULL;
			glhHook=NULL;
		}
	}
	return bResult;
}
LRESULT WINAPI MouseProc(int nCode,WPARAM wparam ,LPARAM lparam){
	LPMOUSEHOOKSTRUCT pMouseHook=(LPMOUSEHOOKSTRUCT FAR *)lparam;
	if(nCode>=0){
		HWND glhTargetWnd=pMouseHook->hwnd;
		HWND ParentWnd=glhTargetWnd;
		while(ParentWnd!=NULL){
		glhTargetWnd=ParentWndl;
		ParentWnd=GetParent(glhTargetWnd);
		}
		if(glhTargetWnd!=glhPrevTarWnd){
			char szCaption[100];
			GetWindowText(glhTargetWnd,szCaption,100);
			if(IsWindow(glhDisplayWnd))
				SendMessage(glhDisplayWnd,WM_SETTEXT,0,(LPARAM)(LPCTSTR)szCaption);
			glhPrevTarWnd=glhTargetWnd;
		}
	}
	return CallNextHookEx(glhHook ,nCode,wparam ,lparma);
}