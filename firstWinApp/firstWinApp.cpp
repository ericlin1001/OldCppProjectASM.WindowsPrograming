// firstWinApp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
char *g_szWindowClassName="winClassName";
char *g_szApplicationName="appName";
//IDI_APPLICATION
//IDC_ARROW
const int WINDOW_WIDTH=500;
const int WINDOW_HEIGHT=500;
void trace(char *pStr){
	MessageBox(NULL,pStr,"Messaga",0);
}
LRESULT CALLBACK WindowProc(HWND hWnd,
							UINT msg,
							WPARAM wParam,
							LPARAM lParam)
{
	trace("in");
	switch(msg){
	case WM_CREATE:
		{
			trace("creating...");
			return 0;
		}
		break;
	case WM_PAINT:
		return 0;
		break;
	case WM_DESTROY:
		trace("destroy....");
		return 0;
		break;
	default:
		trace("defalut");return 0;
		break;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}
int WINAPI WinMain(HINSTANCE hInstance,//ID: can be used in WINAPI.
                     HINSTANCE hPrevInstance,//useless now
                     LPSTR     lpCmdLine,//FOR command. lpCmdLine include all except the app.exe
                     int       nCmdShow)//
{
 	// TODO: Place code here.
	/*MessageBox(NULL,"Text","Caption",0);
	char *error="error details!";*/
	trace("begin");
	//
	WNDCLASSEX winclass;
	winclass.cbSize				=sizeof(WNDCLASSEX);
	winclass.style				=CS_HREDRAW|CS_VREDRAW;
	winclass.lpfnWndProc		=WindowProc;
	winclass.cbClsExtra			=0;
	winclass.cbWndExtra			=0;
	winclass.hInstance			=hInstance;
	winclass.hIcon				=LoadIcon(NULL,IDI_APPLICATION);
	winclass.hCursor			=LoadCursor(NULL,IDC_ARROW);
	winclass.hbrBackground		=(HBRUSH)GetStockObject(WHITE_BRUSH);
	winclass.lpszClassName		=g_szWindowClassName;
	winclass.hIconSm			=LoadIcon(NULL,IDI_APPLICATION);
	if(!RegisterClassEx(&winclass)){
		MessageBox(NULL,"Class Registration failed!","Error",MB_ICONWARNING);
		return 0;
	}
	HWND hWnd=CreateWindowEx(NULL,
							g_szWindowClassName,
							g_szApplicationName,
							WS_OVERLAPPEDWINDOW,
							0,
							0,
							WINDOW_WIDTH,
							WINDOW_HEIGHT,
							NULL,
							NULL,
							hInstance,
							NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	//

	UnregisterClass(g_szWindowClassName,hInstance);
	return 0;
}