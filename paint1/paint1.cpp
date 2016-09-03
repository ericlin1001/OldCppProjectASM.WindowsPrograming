// paint1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int,HWND &);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
int RandInt(int min,int max){
	return rand()%(max-min+1)+min;
}
void draw(HDC hdc,int x){
	static HPEN pen=CreatePen(PS_DOT,1,RGB(0,0,0));
	static int BS[10]={HS_CROSS,HS_DIAGCROSS,HS_VERTICAL,HS_HORIZONTAL};
	static HBRUSH brush=CreateHatchBrush(2,RGB(255,0,0));
	static HPEN oldPen;
	static HBRUSH oldBrush;	
	//
	x*=10;
	//hWnd=NULL;
	oldPen=(HPEN)SelectObject(hdc,pen);
	oldBrush=(HBRUSH)SelectObject(hdc,brush);
	//begin draw.
	//Rectangle(hdc,x+10,10,150,150);
	RECT rect={10,10,180,180};
	FrameRect(hdc,&rect,brush);
	FillRect(hdc,&rect,brush);
	Ellipse(hdc,0,0,150,150);
	RoundRect(hdc,10,10,120,120,50,30);
	const int numV=5;
	POINT points[]={{2,2},{50,50},{50,100},{20,100},{2,80}};
	Polygon(hdc,points,numV);
	
	//end draw.
	SelectObject(hdc,oldBrush);
	SelectObject(hdc,oldPen);
}
#include<time.h>
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
//	srand(time(NULL));
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PAINT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	HWND hWnd;
	if (!InitInstance (hInstance, nCmdShow,hWnd)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_PAINT1);

	// Main message loop:
	//until WM_QUIT.
	int i=0;
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		i++;
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
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_PAINT1);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow,HWND &hWnd)
{
 //  HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable
/*WS_POPUP WS_BORDER    WS_SYSMENU*///WS_OVERLAPPEDWINDOW
   hWnd = CreateWindow(szWindowClass,szTitle, WS_OVERLAPPEDWINDOW, //WS_POPUP|WS_BORDER|WS_SYSMENU,//WS_OVERLAPPEDWINDOW|WS_HSCROLL|WS_VSCROLL|WS_POPUP,
      200, 200, 200, 200, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	//
	static int cx,cy;
	static const int nVerts=5;
	static POINT verts[nVerts];
	const int numLinePerSide=30;
	switch (message) 
	{
		case WM_KEYDOWN:
			switch(wParam){
			case VK_SPACE:
			//	MoveWindow(hWnd,
				About(hWnd,message,wParam,lParam);
				MessageBox(hWnd,"mess","w",0);
				hdc=GetDC(hWnd);
				draw(hdc,2);
				ReleaseDC(hWnd,hdc);
				break;
			case 'W':
				MessageBox(hWnd,"mess","w",0);
				hdc=GetDC(hWnd);
				draw(hdc,2);
				ReleaseDC(hWnd,hdc);
				break;
			case 's':
				break;
			}
			break;
		case WM_CREATE:
			RECT rect;
			GetClientRect(hWnd,&rect);
			cx=rect.right;
			cy=rect.bottom;
				break;
		case WM_SIZE:
			cx=LOWORD(lParam);
			cy=HIWORD(lParam);
			InvalidateRect(hWnd,NULL,true);
			UpdateWindow(hWnd);
			break;
		case WM_ACTIVATE:
			//MessageBox(hWnd,"output","active",0);
			//cout<<"sss"<<endl;
				break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			
			int xStep,yStep;
			int i;
			 yStep=cy/numLinePerSide;
			 xStep=cx/numLinePerSide;
			for( i=0;i<numLinePerSide;i++){
				MoveToEx(hdc,i*xStep,cy,0);
				LineTo(hdc,cx,cy-i*yStep);
				//
				MoveToEx(hdc,0,yStep*i,0);
				LineTo(hdc,i*xStep,cy);
				//
				MoveToEx(hdc,cx-i*xStep,0,0);
				LineTo(hdc,0,i*yStep);
				MoveToEx(hdc,cx-i*xStep,0,0);
				LineTo(hdc,cx,cy-i*yStep);
				//

			}
			//OutText(
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);

				//
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
