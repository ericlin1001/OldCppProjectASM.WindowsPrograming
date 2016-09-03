// gamesTest1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[30]="title";								// The title bar text
TCHAR szWindowClass[30]="mywinclass";	
//							// The title bar text
HPEN hPen[7];
HBRUSH hBrush[7];
int sPen[7]={PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT,
			 PS_DASHDOTDOT,PS_NULL,PS_INSIDEFRAME};
int sBrush[7]={HS_VERTICAL,HS_HORIZONTAL,HS_CROSS,HS_DIAGCROSS,HS_FDIAGONAL,HS_BDIAGONAL};


// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int,HWND *hWnd);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MyRegisterClass(hInstance);
	HWND hWnd1,hWnd2;
	InitInstance (hInstance, nCmdShow,&hWnd1);
	InitInstance (hInstance, nCmdShow,&hWnd2);
	MoveWindow(hWnd1,150,150,300,300,true);
	UpdateWindow(hWnd1);
	// Main message loop:
	MSG msg;
	//SendMessage();
	while (GetMessage(&msg, NULL, 0, 0)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);//call Windows Procedure.
	}

	UnregisterClass(szWindowClass,hInstance);
	return msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)//str classname
{
	WNDCLASSEX wcex;
	wcex.cbSize			= sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_GAMESTEST1);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;//(LPCSTR)IDC_GAMESTEST1;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
	return RegisterClassEx(&wcex);
}
/*
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define INIT_X 100
#define INIT_Y 100*/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow,HWND *hWnd)
{
	/*
	WS_OVERLAPPED     | \
                                     | \
                             WS_SYSMENU        | \
                             WS_THICKFRAME     | \
                             WS_MINIMIZEBOX    | \
                             WS_MAXIMIZEBOX)*/
	hInst = hInstance; // Store instance handle in our global variable
	*hWnd = CreateWindow(szWindowClass, szTitle, WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX,
      INIT_X, INIT_Y, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
//	MoveWindow(hWnd,0,0,500,500,true);
   ShowWindow(*hWnd, nCmdShow);
   UpdateWindow(*hWnd);
   return TRUE;
}
#define NUM_VERTEXS 6
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	//
	static HPEN BluePen =CreatePen(PS_SOLID,1,RGB(0,0,255));
	static HPEN OldPen =NULL;
	static HBRUSH RedBrush =CreateSolidBrush(RGB(255,0,0));
	static HBRUSH OldBrush = NULL;
	static int cx,cy;
	static POINT vertexs[NUM_VERTEXS];
	static int iVertexs=NUM_VERTEXS;
	switch (message) 
	{
		case WM_PAINT:

			PAINTSTRUCT ps;
			BeginPaint(hWnd,&ps);
				OldPen=(HPEN)SelectObject(ps.hdc,BluePen);
					OldBrush=(HBRUSH)SelectObject(ps.hdc,RedBrush);
						Polygon(ps.hdc,vertexs,iVertexs);
					SelectObject(ps.hdc,OldBrush);
				SelectObject(ps.hdc,OldPen);
			EndPaint(hWnd,&ps);
			break;
		case WM_CREATE:
			RECT rect;
			GetClientRect(hWnd,&rect);
			cx=rect.right;
			cy=rect.bottom;
			srand(2);
			int i;
			for(i=0;i<iVertexs;i++){
				vertexs[i].x=i*5;
				vertexs[i].y=i*10;
			}
			break;
		case WM_SIZE:
			GetClientRect(hWnd,&rect);
			cx=rect.right;
			cy=rect.bottom;
			/*
			cx=LOWORD(lParam);
			cy=HIWORD(lParam);
			*/
			break;
		case WM_KEYDOWN:
			if(GetAsyncKeyState(VK_DOWN)&0xf000)
				MoveWindow(hWnd,0,0,50,50,true);
				//SendMessage(hWnd,WM_DESTROY,wParam,lParam);
				//PostQuitMessage(0);
			break;
		case WM_KEYUP:
			switch(wParam){
			case VK_SPACE:
				for(int i=0;i<iVertexs;i++){
					vertexs[i].x=i*5;
					vertexs[i].y=i*10;
				RandomInt(
				}
				InvalidateRect(hWnd,NULL,true);
				UpdateWindow(hWnd);
				break;
			}
			break;
		
		case WM_DESTROY:
			PostQuitMessage(0);//for real quit the application.
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
	/*
			HDC GetDc();
			ReleaseDc();
			CreatePen();
			CreateHatchBrush();
			CreateSolidBrush();
			SelectObject();
			*/