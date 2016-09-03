// puzzleMines.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "userDefines.h"
#define MAX_LOADSTRING 100
//global variables:
HDC mdc;
HDC hdc;
HDC minedc;
HWND hWnd;
int bmpWidth;
int bmpHeight;
bool bplayPuzzle=true;
bool bplayMines=false;
//
#define MAX_COLS 50
#define MAX_ROWS 50
class CCell{
public:	
	int row,col;
};
#define MINE_UNKNOW -2
#define MINE_ISMINE -1
class CFindMines{
public:
	CFindMines(){
		offsetx=0;
		offsety=0;
		bDraw=true;
		bLine=true;
		islost=false;
		numMines=10;
	}
	~CFindMines(){}
	//
	
	void disOrder(int n){
		int i=0;
		int row,col;
		while(i<n){
			do{
				row=rand()%numRows;
				col=rand()%numCols;
			}while(arr[row][col]==-1);
			arr[row][col]=-1;
			i++;
		}
		//cal num:
		for(row=0;row<numRows;row++){
			for(col=0;col<numCols;col++){
				if(arr[row][col]!=-1){//not a mine
					arr[row][col]=isMine(row-1,col-1)+
						isMine(row-1,col)+
						isMine(row,col-1)+
						isMine(row+1,col+1)+
						isMine(row+1,col)+
						isMine(row,col+1)+
						isMine(row+1,col-1)+
						isMine(row-1,col+1);
					
				}
			}
		}
	}
	bool isInRange(int row,int col){
		return 0<=row && row<numRows && 0<=col && col<numCols;
	}
	bool isMine(int row,int col){
		if( isInRange(row,col) && arr[row][col]==-1){
			return true;
		}
		return false;
	}
	int checkWin(){
		if(islost) return -1;
		int row,col;
		for(row=0;row<numRows;row++){
			for(col=0;col<numCols;col++){
				if(arr[row][col]!=-1 && !isKnow[row][col]){
					return 0;
				}
			}
		}
		return 1;
	}
	void markCell(int row,int col){
		mark[row][col]++;
	}
	int getMarkMinesRound(int row,int col){
		int n=0;
	
		for(int i=row-1;i<=row+1;i++){
					for(int j=col-1;j<=col+1;j++){
						n+=!isKnow[i][j] && (mark[i][j]%3==1);
					}	
		}
		return n;
	}
	void analy(int row,int col){
		if(isInRange(row,col) && isKnow[row][col]){
		//	MessageBox(hWnd,"d","",0);
			if(getMarkMinesRound(row,col)==arr[row][col]){
			//	MessageBox(hWnd,"b","",0);
				for(int i=row-1;i<=row+1;i++){
					for(int j=col-1;j<=col+1;j++){
						if(isInRange(i,j) && !isKnow[i][j] && !mark[i][j]){
							openCell(i,j);
						//	MessageBox(hWnd,"c","",0);
						}
					}
				}
			}
		}
	//	MessageBox(hWnd,"a","",0);
	}
	void openCell(int row,int col){
		if( !isInRange(row,col))return ;
		if(!isKnow[row][col]){
			isKnow[row][col]=true;
			if(arr[row][col]==-1) islost=true;
			if(arr[row][col]==0){
				openCell(row-1,col-1);
				openCell(row-1,col);
				openCell(row,col-1);
				openCell(row+1,col+1);
				openCell(row+1,col);
				openCell(row,col+1);
				openCell(row+1,col-1);
				openCell(row-1,col+1);
			}
			reDrawAll();
		}
	}
	void reDrawAll(){
		int row,col;
		for(row=0;row<numRows;row++){
			for(col=0;col<numCols;col++){
				if(isKnow[row][col]){
					reDraw(row,col,arr[row][col]);
				}else{
					reDrawUnknow(row,col);
					if(mark[row][col]%3==1){
						drawMark(row,col,"M");
					}else if(mark[row][col]%3==2){
						drawMark(row,col,"?");
					}
				}
				
			}
		}
	}
	void drawMark(int row,int col,char *buffer){
		draw(col*size,row*size,size*1,0);
		SetTextColor(hdc,RGB(rand()%256,rand()%256,rand()%256));
		SetBkColor(hdc,RGB(153,217,234));
		TextOut(hdc,offsetx+col*size+(int)(size*0.5)-5,offsety+row*size+(int)(size*0.5)-8,buffer,1);
	}
	void init(){
		/**/
		int row,col;
		for(row=0;row<numRows;row++){
			for(col=0;col<numCols;col++){
				arr[row][col]=0;
				mark[row][col]=0;
				
				isKnow[row][col]=false;
			}
		}
		disOrder(numMines);
		reDrawAll();

	}
	void reDrawUnknow(int row,int col){
		draw(col*size,row*size,size*1,0);
	}
	void reDraw(int row,int col,int num){
		if(num==-1){//is mine
			draw(col*size,row*size,size*0,0);
		}else if(num==0){//nothing
			draw(col*size,row*size,size*2,0);
		}else if(num>0){
			drawText(row,col,num);
		}
	}
	void drawText(int row,int col,int num){
		draw(col*size,row*size,size*2,0);
		char buffer[5];
		itoa(num,buffer,5);
		SetTextColor(hdc,RGB(rand()%256,rand()%256,rand()%256));
		SetBkColor(hdc,RGB(153,217,234));
		TextOut(hdc,offsetx+col*size+(int)(size*0.5)-5,offsety+row*size+(int)(size*0.5)-8,buffer,1);
	}
	
	void draw(int destX,int destY,int srcX,int srcY){
		if(bDraw)BitBlt(hdc,offsetx+destX,offsety+destY,size,size,minedc,srcX,srcY,SRCCOPY);
	}
	
public:
	int arr[MAX_ROWS][MAX_COLS];
	bool isKnow[MAX_ROWS][MAX_COLS];
	//-1:mine 0:nothing 1...
	int offsetx,offsety;
	int numCols,numRows;
	int size;
	bool bDraw;
	bool bLine;
	int numMines;
	bool islost;
	int mark[MAX_ROWS][MAX_COLS];
};
CFindMines findMines;
class CPuzzle{
public:
	void disOrder(int n){
		bDraw=false;
		for(int j =0;j<n;j++){
			int i=rand()%4;
			move(i);
		}
		move(0,numCols-1);
		move(1,numRows-1);
		bDraw=true;
	}
	void move(int direction,int times){
		for(int i=0;i<times;i++){
			move(direction);
		}
	}
	CPuzzle(){
		offsetx=0;
		offsety=0;
		bDraw=true;
		bLine=true;
	}
	~CPuzzle(){
		
	}
	bool checkWin(){
		int row,col;
		for(row=0;row<numRows;row++){
			for(col=0;col<numCols;col++){
				if(row!=numRows-1 || col !=numCols-1){
					if(arr[row][col].row==row && arr[row][col].col==col ){
					}else{
						return false;
					}
				}
			}
		}
		return true;
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
			//BitBlt(hdc,0,0,200,200,hdc,0,0,SRCCOPY);
		}else{
			//don't move;
			pBlank.row=oldrow;
			pBlank.col=oldcol;
		}
		//MessageBox(hWnd,"keydown","PressKey",0);
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
		/**/	int row,col;
		for(row=0;row<numRows;row++){
			for(col=0;col<numCols;col++){
				arr[row][col].row=row;
				arr[row][col].col=col;
			}
		}
		pBlank.row=numRows-1;
		pBlank.col=numCols-1;
		arr[numRows-1][numCols-1].row=-1;
		disOrder(500);
		reDrawAll();
	}
	void reDraw(int row,int col){
		if(bDraw){
			if(arr[row][col].row!=-1)draw(col*size,row*size,arr[row][col].col*size,arr[row][col].row*size);
			else draw(col*size,row*size,0xffffff);
			//
			if(bLine){
				HPEN oldPen,hPen;
				hPen=CreatePen(PS_SOLID,2,RGB(0,0,0));
				oldPen=(HPEN)SelectObject(hdc,hPen);
				for(row=0;row<=numRows;row++){
					MoveToEx(hdc,offsetx,offsety+row*size,NULL);
					LineTo(hdc,offsetx+numCols*size,offsety+row*size);
				}
				for(col=0;col<=numCols;col++){
					MoveToEx(hdc,offsetx+col*size,offsety,NULL);
					LineTo(hdc,offsetx+col*size,offsety+numRows*size);
				}
				
				SelectObject(hdc,oldPen);
			}
		}
	}
	void draw(int destX,int destY,int srcX,int srcY){
		if(bDraw)BitBlt(hdc,offsetx+destX,offsety+destY,size,size,mdc,srcX,srcY,SRCCOPY);
	}
	void draw(int destX,int destY,COLORREF color){
		if(bDraw){HPEN oldPen,hPen;
		hPen=CreatePen(PS_SOLID,1,RGB(0,0,0));
		HBRUSH brush=CreateSolidBrush(color);
		HBRUSH oldBrush;	
		oldPen=(HPEN)SelectObject(hdc,hPen);
		oldBrush=(HBRUSH)SelectObject(hdc,brush);
		//
		Rectangle(hdc,offsetx+destX,offsety+destY,offsetx+destX+size,offsety+destY+size);
		//
		SelectObject(hdc,oldPen);
		SelectObject(hdc,oldBrush);
		//
		}
	}
public:
	CCell arr[MAX_ROWS][MAX_COLS];
	CCell pBlank;
	int offsetx,offsety;
	int numCols,numRows;
	int size;
	bool bDraw;
	bool bLine;
};

CPuzzle puzzle;
/*
#define INIT_X 200
#define INIT_Y 200
#define INIT_WIDTH 200
#define INIT_HEIGHT 200*/
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
	LoadString(hInstance, IDC_PUZZLEMINES, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_PUZZLEMINES);
	
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
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_PUZZLEMINES);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_PUZZLEMINES;
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
void initPlayMines(){
	
	findMines.offsetx=1;
	findMines.offsety=1;
	findMines.size=SIZE;
	findMines.numCols=9;
	findMines.numRows=9;
	findMines.numMines=10;
	findMines.init();
	
	//
	RECT crect,wrect;
	GetClientRect(hWnd,&crect);
	GetWindowRect(hWnd,&wrect);
	int ww,wh;
	ww=wrect.right-wrect.left-(crect.right-crect.left)+findMines.numCols*findMines.size+findMines.offsetx+1;
	wh=wrect.bottom-wrect.top-(crect.bottom-crect.top)+findMines.numRows*findMines.size+findMines.offsety+1;
	MoveWindow(hWnd,INIT_X,INIT_Y,ww,wh,false);
	//
	
	InvalidateRect(hWnd,NULL,true);
	UpdateWindow(hWnd);
	MessageBox(hWnd,"find 10 mines","",0);
}
void initPuzzle(){
	puzzle.offsetx=1;
	puzzle.offsety=1;
	puzzle.size=SIZE;
	puzzle.numCols=4;
	puzzle.numRows=4;
	puzzle.init();
	//
	bmpWidth=BMP1_WIDTH;
	bmpHeight=BMP1_HEIGHT;
	///**/
	//
	puzzle.bDraw=true;
	RECT crect,wrect;
	GetClientRect(hWnd,&crect);
	GetWindowRect(hWnd,&wrect);
	int ww,wh;
	ww=wrect.right-wrect.left-(crect.right-crect.left)+puzzle.numCols*puzzle.size+puzzle.offsetx+1;
	wh=wrect.bottom-wrect.top-(crect.bottom-crect.top)+puzzle.numRows*puzzle.size+puzzle.offsety+1;
	MoveWindow(hWnd,INIT_X,INIT_Y,ww,wh,false);
	//
	InvalidateRect(hWnd,NULL,true);
	UpdateWindow(hWnd);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	
	hInst = hInstance; // Store instance handle in our global variable
	
	hWnd = CreateWindow(szWindowClass,  szTitle,WS_OVERLAPPEDWINDOW,//WS_POPUPWINDOW,//
		INIT_X, INIT_Y, INIT_WIDTH, INIT_HEIGHT, NULL, NULL, hInstance, NULL);
	
	if (!hWnd)
	{
		return FALSE;
	}
	::hWnd=hWnd;
	//
	HBITMAP hbmp;
	hbmp=(HBITMAP)LoadImage(NULL,BMP1_PATH,IMAGE_BITMAP,BMP1_WIDTH,BMP1_HEIGHT,LR_LOADFROMFILE);
	//
	hdc=GetDC(hWnd);
	mdc=CreateCompatibleDC(hdc);
	SelectObject(mdc,hbmp);
	//
	hbmp=(HBITMAP)LoadImage(NULL,BMP2_PATH,IMAGE_BITMAP,BMP2_WIDTH,BMP2_HEIGHT,LR_LOADFROMFILE);
	//
	minedc=CreateCompatibleDC(hdc);
	SelectObject(minedc,hbmp);
	//
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	initPlayMines();
	if(bplayPuzzle) initPuzzle();
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
#include<stdio.h>
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps; 
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	short mouseX,mouseY;
	int row,col;
	switch (message) 
	{
		//WM_LBUTTONDBLCLK
	case WM_MBUTTONDOWN:
		if(bplayMines){
		mouseX=LOWORD(lParam);
		mouseY=HIWORD(lParam);
		row=mouseY/SIZE;
		col=mouseX/SIZE;
		findMines.analy(row,col);
		InvalidateRect(hWnd,NULL,true);
		UpdateWindow(hWnd);
		//MessageBox(hWnd,"adfas","",0);
		int r;
		r=findMines.checkWin();
		if(r==-1){MessageBox(hWnd,"You lost!!","Lost",0);
		}else if(r==1) {MessageBox(hWnd,"You win!!!","Win",0);
		}
		}
		break;
	case WM_LBUTTONDOWN:
		if(bplayMines){
			mouseX=LOWORD(lParam);
		mouseY=HIWORD(lParam);
		row=mouseY/SIZE;
		col=mouseX/SIZE;
		findMines.openCell(row,col);
		InvalidateRect(hWnd,NULL,true);
		UpdateWindow(hWnd);
		int r;
		r=findMines.checkWin();
		if(r==-1){MessageBox(hWnd,"You lost!!","Lost",0);
		}else if(r==1) {MessageBox(hWnd,"You win!!!","Win",0);
		}
		}
		break;
	case WM_RBUTTONDOWN:
		if(bplayMines){
		mouseX=LOWORD(lParam);
		mouseY=HIWORD(lParam);
		row=mouseY/SIZE;
		col=mouseX/SIZE;
		findMines.markCell(row,col);
		InvalidateRect(hWnd,NULL,true);
		UpdateWindow(hWnd);
		}
		break;
	case WM_KEYDOWN:
		if(bplayPuzzle){
		if(VK_LEFT<=wParam && wParam<=VK_DOWN){
			puzzle.move(wParam-VK_LEFT);
			InvalidateRect(hWnd,NULL,true);
			UpdateWindow(hWnd);
			if(puzzle.checkWin()){
				MessageBox(hWnd,"You pass the Puzzle game!","You Win!",0);
				bplayPuzzle=false;
				bplayMines=true;
				initPlayMines();
			}
		}
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
			::hdc=BeginPaint(hWnd,&ps);
			if(bplayPuzzle){
				puzzle.reDrawAll();
			}
			if(bplayMines){
			findMines.reDrawAll();
			}
			EndPaint(hWnd,&ps);
			break;
		case WM_DESTROY:
			DeleteObject(mdc);
			DeleteObject(hdc);
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
