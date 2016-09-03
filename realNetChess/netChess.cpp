// netChess.cpp : Defines the entry point for the application.
//




//

#include "stdafx.h"
#include "resource.h"
#include"userDefines.h"
#include "netTran.h"
#define MAX_COLS 15
#define MAX_ROWS 15
#define MAX_LOADSTRING 100

// Global Variables:
HDC hdc,mdc,stonedc;
HWND hWnd;
HBITMAP hbmp;

int stoneSize=25;
//
void intToStr(int num,char *str){
	char *p=str;
	while(num!=0){
		*str++=num%10+'0';
		num/=10;
	}
	*str--=0;
	while(p<str){
		char ch=*p;
		*p=*str;
		*str=ch;
		p++;str--;
	}
	
}
int intlen(int num){
	int len;
	len=0;
	while(num!=0){
		num/=10;
		len++;
	}
	return len;
}
void baiscMusic(int i,int duration=200){
	int fre=0;
	int k=1;
	switch(i){
	case 1:
		fre=1046;
		break;
		case 2:
		fre=1174;
		break;
		case 3:
		fre=1318;
		break;
		case 4:
		fre=1396;
		break;
		case 5:
		fre=1567;
		break;
		case 6:
		fre=1864;
		break;
		case 7:
		fre=1975;
		break;
		case 0:
		k=2;
		break;
		default:
			fre=0;
	}
	fre+=-500+k*300+200;
	Beep(fre,duration);
}
void playMusic(char *str){
	while(*str){
		baiscMusic(*str-'0');
		str++;
	}
}
unsigned long WINAPI waitForPlayer(LPVOID lParam){
	netTran *pmynet=(netTran *)lParam;
	pmynet->wait();
	playMusic("335.335.3507665");
	MessageBox(NULL,"wait success!","",0);
	return 0;
}
class CChess;
#define CLIENT 
class CChess{
public:
	CChess(){
		int row,col;
		for(row=0;row<numRows;row++){
			for(col=0;col<numCols;col++){
				arr[row][col]=0;
			}
		}
		//
		x=0;
		y=0;
		pNext=1;
		sizeEdge=5;
#ifdef CLIENT
		int countfial=0;
		while(!startConnectTo("192.168.67.219")){
			if(countfial++>=2){
				MessageBox(NULL,"exiting...!","Exit.",0);
				exit(1);
			}
			Sleep(2000);

		}
		MessageBox(NULL,"connect successfully!","success.",0);
		startRecv();
#else
	startWait();
	startRecv();
#endif
		
	}
	void tellAnother(int row,int col,int num){
		char buffer[5];
		buffer[0]='$';
		buffer[1]=row;
		buffer[2]=col;
		buffer[3]=num;
		buffer[4]='#';
		buffer[5]=0;
		mynet.sendMess(buffer);
	}
	static unsigned long WINAPI otherPlay(LPVOID lParam){
		CChess *chess=(CChess *)lParam;
		while(1){
			if(chess->mynet.bReady){
				char buffer[20];
				chess->mynet.recvMess(buffer,20);
				if(strlen(buffer)>0){
				//	MessageBox(NULL,buffer,"revc success!",0);
					if(buffer[0]=='$' && buffer[0]=='$'){
					//	MessageBox(NULL,buffer,"revc correct!",0);
						int row,col,num;
						row=buffer[1];
						col=buffer[2];
						num=buffer[3];
						if(num==chess->pNext){
						//	MessageBox(NULL,buffer,"num correct! and put a stone",0);
							chess->put(row,col);
							playMusic("767");
							InvalidateRect(hWnd,NULL,true);
							UpdateWindow(hWnd);
						}else{
							MessageBox(NULL,"Error:synchronision!","Error",0);
							MessageBox(NULL,"exiting...!","Exit.",0);
							exit(1);
						}
					}
				}
			}
			
		}
		return 0;
	}
	bool  putAndSend(int row,int col){
		put(row,col);
		tellAnother(row,col,pNext-1);
		return true;
	}
	bool startRecv(){
		DWORD dwThread;
		bool b;
		HANDLE hThread=	CreateThread(NULL,0,otherPlay,(LPVOID)this,0,&dwThread);
		b=hThread!=NULL;
		CloseHandle(hThread);
		return b;
	}
	bool startWait(){
		DWORD dwThread;
		bool b;
		HANDLE hThread=	CreateThread(NULL,0,waitForPlayer,(LPVOID)&mynet,0,&dwThread);
		b=hThread!=NULL;
		CloseHandle(hThread);
		return b;
	}
	bool  startConnectTo(char *ip,int port=0){
		return mynet.connectTo(ip,port);
	}
	~CChess(){
	}
	int getWidth(){
		return x+sizeEdge*2+size*(numCols-1);
	}
	int getHeight(){
		return y+sizeEdge*2+size*(numRows-1);
	}
	bool  click(int x,int y){
		if(isYouPlay()){
			int col=(x-this->x-sizeEdge+size*0.5)/size;
			int row=(y-this->y-sizeEdge+size*0.5)/size;
			return putAndSend(row,col);
		}
		return false;
	}
	bool inRange(int row,int col){
		return 0<=row && row<numRows && 0<=col && col<numCols;
	}
	bool  put(int row,int col){
		if(inRange(row,col) && arr[row][col]==0){
			arr[row][col]=pNext;
			pNext++;
			reDrawAll();
			return true;
		}
		return false;
	}
	bool isYouPlay(){
#ifdef CLIENT
		return pNext%2==0;
#else
			return pNext%2==1;
#endif
	}
	bool isBlack(){
		return pNext%2==1;
	}
	bool isWhite(){
		return !isBlack();
	}
	void reDrawAll(){
		drawBK();
		int row,col;
		for(row=0;row<numRows;row++){
			for(col=0;col<numCols;col++){
				reDraw(row,col);
			}
		}
	}
	void drawNum(int x,int y,int num){
		char buffer[5];
		
		intToStr(num,buffer);
		SetTextColor(destDC,RGB(0,0,0));
		//SetBkColor(destDC,RGB(255,255,255));
		TextOut(destDC,x,y,buffer,strlen(buffer));
	}
	void drawText(int x,int y,char *buffer){
		SetTextColor(destDC,RGB(0,0,0));
		SetBkColor(destDC,RGB(200,200,0));
		TextOut(destDC,x,y,buffer,strlen(buffer));
	}
	void drawBK(){
		HPEN hPen,oldPen;
		hPen=CreatePen(PS_SOLID,1,RGB(0,0,0));
		HBRUSH brush=CreateSolidBrush(RGB(200,200,0));
		HBRUSH oldBrush;	
		oldPen=(HPEN)SelectObject(hdc,hPen);
		oldBrush=(HBRUSH)SelectObject(hdc,brush);
		//
		Rectangle(destDC,x,y,x+sizeEdge*2+size*(numCols-1),y+sizeEdge*2+size*(numRows-1));
		int row,col;
		char buffer[3];
		
		for(row=0;row<numRows;row++){
			MoveToEx(destDC,x+sizeEdge,y+sizeEdge+row*size,NULL);
			LineTo(destDC,x+sizeEdge+(numCols-1)*size,y+sizeEdge+row*size);
			//
			buffer[0]=numRows-1-row+'A';
			buffer[1]=0;
			drawText(sizeEdge*0.5-4+x,y+sizeEdge+row*size-8,buffer);
		}
		for(col=0;col<numCols;col++){
			MoveToEx(destDC,x+sizeEdge+col*size,y+sizeEdge,NULL);
			LineTo(destDC,x+sizeEdge+col*size,y+sizeEdge+(numRows-1)*size);
			//
			intToStr(col+1,buffer);
			
			drawText(x+sizeEdge+col*size-4,y+sizeEdge*1.5+(numRows-1)*size-8,buffer);
			
		}
		brush=CreateSolidBrush(RGB(0,0,0));
		SelectObject(hdc,brush);
		int midx,midy;
		midx=(getWidth()+x)*0.5;
		midy=(getHeight()+y)*0.5;
		int r=3;
		Ellipse(destDC,midx-r,midy-r,midx+r,midy+r);
		//
		SelectObject(hdc,oldPen);
		SelectObject(hdc,oldBrush);
	}
	void reDraw(int row,int col){
		if(arr[row][col]>0){
			drawStone(x+sizeEdge+col*size-stoneSize*0.5,y+sizeEdge+row*size-stoneSize*0.5,arr[row][col]%2);
			drawNum(x+sizeEdge+col*size-4*intlen(arr[row][col]),y+sizeEdge+row*size-8,arr[row][col]);
		}
	}
	RECT getRect(){
		RECT rect;
		return rect;
	}
	void test(){	
	}
	void drawStone(int destx,int desty,int type){
		
		if(type==1){//black
			BitBlt(destDC,destx,desty,stoneSize,stoneSize,srcDC,stoneSize*2,0,SRCAND);
			BitBlt(destDC,destx,desty,stoneSize,stoneSize,srcDC,0,0,SRCPAINT);
			
		}else if (type==0){//white
			BitBlt(destDC,destx,desty,stoneSize,stoneSize,srcDC,stoneSize*2,0,SRCAND);
			BitBlt(destDC,destx,desty,stoneSize,stoneSize,srcDC,stoneSize,0,SRCPAINT);
			
		}
	}
	int x,y;
	int sizeEdge;
	int numCols,numRows;
	int arr[MAX_ROWS][MAX_COLS];
	int size;
	int pNext;
	int stoneSize;
	//COLORREF color;
	HDC srcDC,destDC,bufferDC;
	//for net:
	netTran mynet;
};
CChess myChess;
//
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
	LoadString(hInstance, IDC_NETCHESS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_NETCHESS);
	
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
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_NETCHESS);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_NETCHESS;
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
void initChess(){
	myChess.srcDC=mdc;
	myChess.destDC=hdc;
	myChess.numCols=15;
	myChess.numRows=15;
	myChess.x=0;
	myChess.y=0;
	myChess.sizeEdge=35;
	myChess.stoneSize=stoneSize;
	myChess.size=(int)(stoneSize*1.2);
	//	test();
	myChess.reDrawAll();
	//	myChess.stoneSize=stoneSize;
}
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
	//
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//
	::hWnd=hWnd;
	
	hbmp=(HBITMAP)LoadImage(NULL,BMP1_PATH,IMAGE_BITMAP,stoneSize*3,stoneSize,LR_LOADFROMFILE);
	//
	hdc=GetDC(hWnd);
	mdc=CreateCompatibleDC(hdc);
	SelectObject(mdc,hbmp);
	//
	//
	//
	initChess();
	RECT crect,wrect;
	GetClientRect(hWnd,&crect);
	GetWindowRect(hWnd,&wrect);
	int ww,wh;
	ww=wrect.right-wrect.left-(crect.right-crect.left)+myChess.getWidth();
	wh=wrect.bottom-wrect.top-(crect.bottom-crect.top)+myChess.getHeight();
	
	MoveWindow(hWnd,300, 200,ww,wh,true);
	//
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	//
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
	case WM_LBUTTONDOWN:
		int mouseX,mouseY;
		mouseX=LOWORD(lParam);
		mouseY=HIWORD(lParam);
		myChess.click(mouseX,mouseY);
		
		InvalidateRect(hWnd,NULL,true);
		UpdateWindow(hWnd);
		
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
			// TODO: Add any drawing code here...
			myChess.reDrawAll();
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
		if(LOWORD(wParam)==IDC_CONNECT){
			char buffer[10];
			//GetWindowText(IDC_PORT,buffer,10);
			MessageBox(hWnd,buffer,"",0);
		}
		break;
	}
    return FALSE;
}
