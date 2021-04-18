#include <windows.h>
#include "Paint.h"
#include "WinMain.h"
#include "GameProcess.h"
#include "StageProcess.h"
#include "resource.h"


LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPSTR lpszClass="우리 거북이가 달라졌어요! Alpha Ver 0.6";

CPlayer player;
CScore score(500,20);
CTitle title;
CUpgrade upgrade(0);
CItemSlot item_slot(40,520);

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		  CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		  NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	
	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	int i;
	char str[256];
	HDC hdc;
	PAINTSTRUCT ps;
	RECT wrt;

	SetRect(&wrt,0,0,SCREEN_X,SCREEN_Y);

	switch(iMessage) 
	{
	case WM_CREATE:
		AdjustWindowRect(&wrt,WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,FALSE);
		MoveWindow(hWnd,100,100,wrt.right-wrt.left,wrt.bottom-wrt.top,FALSE);
		hWndMain=hWnd;
		SetTimer(hWnd,1,10,NULL);
		score.SetKillPoint(5);
		for(i=0;i<STAGE_NUM;i++)
		{
			LoadString(g_hInst, IDS_BKGROUND1+i,str,256);
			BgGraphic[i].Load(str);
		}
		
		LoadString(g_hInst, IDS_BGEFFECT,str,256);
		BgEffect.Load(str);

		StageDataSet();
		CAnimation::DataSet();
		randomize();
		mode=TITLE;
		return 0;
	case WM_TIMER:
		GameProcesser();
		return 0;
	case WM_MOUSEMOVE:
		switch(mode)
		{
		case TITLE:
			title.MouseMove(wParam,lParam);
			break;
		case UPGRADE:
			upgrade.MouseMove(wParam,lParam);
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:
		switch(mode)
		{
		case TITLE:
			title.MouseSelect(wParam,lParam);
			break;
		case UPGRADE:
			upgrade.MouseSelect(wParam,lParam);
			break;
		}
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		PaintProc(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		if(dBuffer)
		{
			DeleteObject(dBuffer);
		}
		KillTimer(hWnd,1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}