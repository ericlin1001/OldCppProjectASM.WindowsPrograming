// PuzzleMineGame.cpp : Defines the entry point for the application.
//


//
#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//


#include "userDefines.h"
#include "resource.h"
#define MAX_LOADSTRING 100

#define MAX_LOADSTRING 100
//global variables:
HDC mdc;
HDC hdc;
//
#define MAX_COLS 50
#define MAX_ROWS 50
class CCell{
public:	
	int row,col;
};
class CPuzzle{
public:
	CPuzzle(){
		hWnd=0;
		offsetx=0;
		offsety=0;
	}
	~CPuzzle(){
		DeleteObject(mdc);
	}
	void move(int direction){
		//0:left 1:up 2:right 4:down
		int oldrow,oldcol;
		oldrow=pBlank.row;
		oldcol=pBlank.col;
		switch(direction){
		case 0://left
			pBlank.col++;
			break;
		case 1://up
			pBlank.row++;
			break;
		case 2://right
			pBlank.col--;
			break;
		case 3://down
			pBlank.row--;;
			break;
		}
		if(0<=pBlank.row && pBlank.row<numRows && 0<=pBlank.col && pBlank.col<numCols){
			//move;
			arr[oldrow][oldcol]=arr[pBlank.row][pBlank.col];
			arr[pBlank.row][pBlank.col].row=-1;
			reDraw(oldrow,oldcol);
			reDraw(pBlank.row,pBlank.col);
			//reDrawAll();
			//BitBlt(hdc,0,0,200,200,bufferDC,0,0,SRCCOPY);
		}else{
			//don't move;
			pBlank.row=oldrow;
			pBlank.col=oldcol;
		}
		//MessageBox(hWnd,"keydown","PressKey",0);
	}
	void setHwnd(HWND thWnd,HDC &tsrcdc){
		hWnd=thWnd;
		/*srcdc=CreateCompatibleDC(tsrcdc);
		BitBlt(srcdc,0,0,size*numCols,size*numRows,mdc,0,0,SRCCOPY);
		bufferDC=mdc;
		BitBlt(mdc,0,0,150,150,srcdc,50,50,SRCCOPY);*/
	}
	void reDrawAll(){
		int row,col;
		for(row=0;row<numRows;row++){
			for(col=0;col<numCols;col++){
				reDraw(row,col);
			}
		}
	}
	void init(){
	/*	int row,col;
		for(row=0;row<numRows;row++){
			for(col=0;col<numCols;col++){
				arr[row][col].row=row;
				arr[row][col].col=col;
				reDraw(row,col);
			}
		}
		pBlank.row=numRows-1;
		pBlank.col=numCols-1;
		arr[numRows-1][numCols-1].row=-1;
		reDraw(pBlank.row,pBlank.col);*/
	}
	void reDraw(int row,int col){
		if(arr[row][col].row!=-1)draw(col*size,row*size,arr[row][col].col*size,arr[row][col].row*size);
		else draw(col*size,row*size,0xffffff);
		//
		HPEN oldPen,hPen;
		hPen=CreatePen(PS_SOLID,2,RGB(0,0,0));
		oldPen=(HPEN)SelectObject(mdc,hPen);
		for(row=0;row<=numRows;row++){
			MoveToEx(mdc,offsetx,offsety+row*size,NULL);
			LineTo(mdc,offsetx+numCols*size,offsety+row*size);
		}
		for(col=0;col<=numCols;col++){
			MoveToEx(mdc,offsetx+col*size,offsety,NULL);
			LineTo(mdc,offsetx+col*size,offsety+numRows*size);
		}
		SelectObject(mdc,oldPen);
	}
	void draw(int destX,int destY,int srcX,int srcY){
		BitBlt(mdc,offsetx+destX,offsety+destY,size,size,mdc,srcX,srcY,SRCCOPY);
	}
	void draw(int destX,int destY,COLORREF color){
		HPEN oldPen,hPen;
		hPen=CreatePen(PS_SOLID,1,RGB(0,0,0));
		HBRUSH brush=CreateSolidBrush(color);
		HBRUSH oldBrush;	
		oldPen=(HPEN)SelectObject(mdc,hPen);
		oldBrush=(HBRUSH)SelectObject(mdc,brush);
		//
		Rectangle(mdc,destX,destY,destX+size,destY+size);
		//
		SelectObject(mdc,oldPen);
		SelectObject(mdc,oldBrush);
		//
	}
public:
	/*HDC srcdc;
	HDC *pBufferDC;
	HDC bufferDC;*/
	HWND hWnd;
	CCell arr[MAX_ROWS][MAX_COLS];
	CCell pBlank;
	int offsetx,offsety;
	int numCols,numRows;
	int size;
};
CPuzzle puzzle;
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

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
	LoadString(hInstance, IDC_PUZZLEMINEGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_PUZZLEMINEGAME);
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
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_PUZZLEMINEGAME);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_PUZZLEMINEGAME;
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

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   //
   HBITMAP hbmp;
   hbmp=(HBITMAP)LoadImage(NULL,BMP1_PATH,IMAGE_BITMAP,BMP1_WIDTH,BMP1_HEIGHT,LR_LOADFROMFILE);
   hdc=GetDC(hWnd);
   mdc=CreateCompatibleDC(hdc);
   SelectObject(mdc,hbmp);
   //set puzzle:
	puzzle.size=50;
	puzzle.numRows=puzzle.numCols=4;
	puzzle.setHwnd(hWnd,mdc);
	puzzle.init();
	InvalidateRect(hWnd,NULL,true);
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
			case WM_KEYDOWN:
					if(VK_LEFT<=wParam && wParam<=VK_DOWN){
			puzzle.move(wParam-VK_LEFT);
			InvalidateRect(hWnd,NULL,true);
			UpdateWindow(hWnd);
		}
		break;
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
				BitBlt(hdc,0,0,BMP1_WIDTH,BMP1_HEIGHT,mdc,0,0,SRCCOPY);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
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
;