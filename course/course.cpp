// course.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "userdefines.h"
#define MAX_LOADSTRING 100

// Global Variables:
HBITMAP bbmp,fbmp;
HDC mdc;
//
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//
void MyPaint(HDC hdc)
{
	//SelectObject(hdc,bbmp);
//	BitBlt(hdc,BMP1_XOFFSET,BMP1_YOFFSET,BMP1_WIDTH,BMP1_HEIGHT,mdc,0,0,SRCCOPY);
	SelectObject(mdc,fbmp);
	BitBlt(hdc,BMP2_XOFFSET,BMP2_YOFFSET,BMP2_WIDTH,BMP2_HEIGHT,mdc,0,0,SRCCOPY);
}
//
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
	LoadString(hInstance, IDC_COURSE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_COURSE);

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
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_COURSE);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_COURSE;
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
int RandInt(int min,int max)
{
	return rand()%(max-min+1)+min;
}
bool select(int x,int y)
{
	return RandInt(0,3)==0;
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_POPUP| WS_BORDER,//0,//WS_THICKFRAME,//WS_OVERLAPPEDWINDOW,
      APP_X, APP_Y, APP_WIDTH, APP_HEIGHT, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   //
   /*fbmp=(HBITMAP)LoadImage(NULL,"course.bmp",IMAGE_BITMAP,BMP1_WIDTH,BMP1_HEIGHT,LR_LOADFROMFILE);
   /*HDC hdc;
   hdc=GetDC(hWnd);
   mdc=CreateCompatibleDC(hdc);
   SelectObject(mdc,fbmp);*/
   //
   /*GetBitmapBits(HBITMAP,LONG,LPVOID);
   SetBitmapBits(HBITMAP,DWORD,CONST VOID *);
   GetObject(HGDIOBJ,INT, LPVOID);*/
	HDC hdc;
	hdc=GetDC(hWnd);
	mdc=CreateCompatibleDC(hdc);
	//
	BITMAP bm1,bm2;
	unsigned char *px1,*px2;
	//dealing with bbmp
	bbmp=(HBITMAP)LoadImage(NULL,BMP1_PATH,IMAGE_BITMAP,BMP1_WIDTH,BMP1_HEIGHT,LR_LOADFROMFILE);
	GetObject(bbmp,sizeof(BITMAP),&bm1);
	if(bm1.bmBitsPixel!=32 && bm1.bmBitsPixel!=24)
	{
		MessageBox(NULL,"Only run in 24/36 bit mode!","Warning",0);
		return FALSE;
	}
	px1=new unsigned char [bm1.bmWidthBytes*bm1.bmHeight];
	GetBitmapBits(bbmp,bm1.bmHeight*bm1.bmWidthBytes,px1);
	//dealing with fbmp
	fbmp=(HBITMAP)LoadImage(NULL,BMP2_PATH,IMAGE_BITMAP,BMP2_WIDTH,BMP2_HEIGHT,LR_LOADFROMFILE);
	GetObject(fbmp,sizeof(BITMAP),&bm2);
	px2=new unsigned char[bm2.bmWidthBytes*bm2.bmHeight];
	GetBitmapBits(fbmp,bm2.bmWidthBytes*bm2.bmHeight,px2);
	//
	const float alpha=0.7f;
	int xstart,ystart,xend,yend,x,y,i;
	xstart=BMP1_XOFFSET;
	ystart=BMP1_YOFFSET;
	int rgb_b;
	int PxBytes=bm1.bmBitsPixel/8;
	xend=xstart+BMP1_WIDTH;
	yend=ystart+BMP1_HEIGHT;

	for(y=ystart;y<yend;y++)
	{
		for(x=xstart;x<xend;x++)
		{
			rgb_b=y*bm1.bmWidthBytes+x*PxBytes;
			px1[rgb_b]=px1[rgb_b]*alpha;
			px1[rgb_b+1]=px1[rgb_b+1]*alpha;
			px1[rgb_b+2]=px1[rgb_b+2]*alpha;
		}
	}/**/
	int unalpha;
	unalpha=1-alpha;
	int constr,constg,constb;
	rgb_b=ystart*bm1.bmWidthBytes+xstart*PxBytes;
	constb=px1[rgb_b];constg=px1[rgb_b+1];constr=px1[rgb_b+2];
	for(y=0;y<bm2.bmHeight;y++)
	{
		for(x=0;x<bm2.bmWidth;x++)
		{
			rgb_b=y*bm2.bmWidthBytes+x*PxBytes;
			if(!(constb==px1[rgb_b] && constg==px1[rgb_b+1] && constr==px1[rgb_b+2]))  
			{
				i=(ystart+y)*bm2.bmWidthBytes+(xstart+x)*PxBytes;
				px2[rgb_b]=px1[rgb_b]*unalpha+px1[i];
				px2[rgb_b+1]=px1[rgb_b+1]*unalpha+px1[i];
				px2[rgb_b+2]=px1[rgb_b+2]*unalpha+px1[i];
			}else
			{

			}
		}
	}
	SetBitmapBits(fbmp,bm2.bmHeight*bm2.bmWidthBytes,px2);
	MyPaint(hdc);
	//
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
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			MyPaint(hdc);
			// TODO: Add any drawing code here...
		//	RECT rt;
		//	GetClientRect(hWnd, &rt);
		//	DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			//
		//	DeleteObject(fbmp);
		//	DeleteDC(mdc);
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
