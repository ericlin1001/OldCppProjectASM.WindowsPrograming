// drawSep7.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "userdefine.h"
#include<stdio.h>
#define MAX_LOADSTRING 100
// Global Variables:
//user
HBITMAP bgBmp,drawBmp;
HDC mdc;
//
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
//

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//
int rolex=0,roley=0;
void MyPaint(HDC hdc){

	static HPEN pen=CreatePen(PS_SOLID,1,RGB(0,0,0));
	static HPEN oldPen;
	static HBRUSH brush=CreateSolidBrush(RGB(0,255,0));
	static HBRUSH oldBrush;
	oldPen=(HPEN)SelectObject(hdc,pen);
	oldBrush=(HBRUSH)SelectObject(hdc,brush);
	//begin paint
	//
	SelectObject(mdc,bgBmp);
	BitBlt(hdc,0,0,BMP1_WIDTH,BMP1_HEIGHT,mdc,0,0,SRCCOPY);
	int drawx,drawy;
	drawx=rolex;
	drawy=roley;
	SelectObject(mdc,drawBmp);
	BitBlt(hdc,drawx,drawy,BMP2_WIDTH/2,BMP2_HEIGHT,mdc,BMP2_WIDTH/2,0,SRCAND);
	BitBlt(hdc,drawx,drawy,BMP2_WIDTH/2,BMP2_HEIGHT,mdc,0,0,SRCPAINT);

//	BitBlt(hdc,drawx+50,drawy,BMP2_WIDTH/2,BMP2_HEIGHT,mdc,BMP2_WIDTH/2,0,SRCAND);
//	BitBlt(hdc,drawx+50,drawy,BMP2_WIDTH/2,BMP2_HEIGHT,mdc,0,0,SRCPAINT);
	//
//	BitBlt(hdc,100,100,500,500,mdc,100,100,SRCCOPY);
	/*
	2.Chord(hdc,0,0,100,100,25,40,100,600);
	1.InvalidateRect(hWnd,NULL,true);
	UpdateWindow(hWnd);
	int x,y;
	char buffer[20];
	x=LOWORD(lParam);
	y=HIWORD(lParam);
	SetTextColor(hdc,RGB(255,0,0));
	strcpy(buffer,"mouse:");
	TextOut(hdc,10,10,buffer,strlen(buffer));
	sprintf(buffer,"x:%d  ",x);
	TextOut(hdc,10,50,buffer,strlen(buffer));
	sprintf(buffer,"y:%d ",y);
	TextOut(hdc,100,50,buffer,strlen(buffer));
	*/
	//end paint
	SelectObject(hdc,brush);
	SelectObject(hdc,pen);
}
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAWSEP7, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DRAWSEP7);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_DRAWSEP7);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_DRAWSEP7;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
	HDC hdc;
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      INIT_X, INIT_Y, APP_WIDTH, APP_HEIGHT, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
//init:
   hdc=GetDC(hWnd);
   mdc=CreateCompatibleDC(hdc);
   bgBmp=(HBITMAP)LoadImage(NULL,BMP1_PATH,IMAGE_BITMAP,BMP1_WIDTH,BMP1_HEIGHT,LR_LOADFROMFILE);
   drawBmp=(HBITMAP)LoadImage(NULL,BMP2_PATH,IMAGE_BITMAP,BMP2_WIDTH,BMP2_HEIGHT,LR_LOADFROMFILE);
   MyPaint(hdc);
   ReleaseDC(hWnd,hdc);
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	//
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_KEYDOWN:
			int speed;

				speed=8
					;
			switch(wParam){
			case VK_DOWN:
				roley+=speed;
				break;
			case VK_UP:
				roley-=speed;
				break;
			case VK_LEFT:
				rolex-=speed;
				break;
			case VK_RIGHT:
				rolex+=speed;
				break;
			}
			Sleep(80);
			InvalidateRect(hWnd,NULL,true);
			UpdateWindow(hWnd);
		case WM_MOUSEMOVE:
			hdc=GetDC(hWnd);
			ReleaseDC(hWnd,hdc);
				break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			MyPaint(hdc);
			char buffer[20];
			sprintf(buffer,"(%d,%d)   (%d,%d)",rt.left,rt.top,rt.right,rt.bottom);
			TextOut(hdc,0,0,buffer,strlen(buffer));
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			DeleteDC(mdc);
			DeleteObject(bgBmp);
			DeleteObject(drawBmp);
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
