#include"Paint.h"
#include"CAnimation.h"
#include"GameProcess.h"
#include"StageProcess.h"
#include"CEnemy.h"
#include"CLittleCuttlefish.h"
#include"CStarfish.h"
#include"CBigCuttlefish.h"
#include"CGarfish.h"
#include"WinMain.h"
#include"CEffect.h"
#include"CItem.h"
#include"CScore.h"


HBITMAP dBuffer; //더블 버퍼링에 이용하기 위한 비트맵 버퍼.

//더블 버퍼링용 비트맵 버퍼에 그림을 그림.
void BufferProc()
{
	int i,bgy=(0 < -(BgGraphic[now_stage].GetHeight()-SCREEN_Y-now_frame/8))?
			  0 : -(BgGraphic[now_stage].GetHeight()-SCREEN_Y-now_frame/8);
	//테스트용 프레임 표시기
	//char frame[20];
	///
	CEnemy* pEnemy;
	CBullet* pBullet;
	CEffect* pEffect;
	CItem* pItem;

	RECT crt;
	HDC hdc,hMemDC;
	HBITMAP OldBit;
	
	GetClientRect(hWndMain,&crt);
	hdc=GetDC(hWndMain);

	if(dBuffer==NULL)
	{
		dBuffer=CreateCompatibleBitmap(hdc,crt.right,crt.bottom);
	}
	hMemDC=CreateCompatibleDC(hdc);
	OldBit=(HBITMAP)SelectObject(hMemDC,dBuffer);

	FillRect(hMemDC,&crt,GetSysColorBrush(COLOR_WINDOW));

	switch(mode)
	{
	case TITLE:
		title.Draw(hMemDC);
		break;
	case STAGE:
	case GAME_OVER:
	case STAGE_CLEAR:

		BgGraphic[now_stage].Draw(hMemDC,0,bgy,
							 800,BgGraphic[now_stage].GetHeight());

		// 테스트용 프레임 표시기. 
		/*SetBkMode(hMemDC,TRANSPARENT);
		itoa(now_frame/10,frame,10);
		TextOut(hMemDC,20,20,TEXT(frame),strlen(frame));*/
		///

		for(i=0;i<now_enemy.GetNum();i++)
		{
			pEnemy=(CEnemy*)now_enemy.GetIdx(i);
			pEnemy->Draw(hMemDC);
		}

		for( i = 0 ; i < now_bullet.GetNum(); i++)
		{
			pBullet = (CBullet*)now_bullet.GetIdx(i);
			pBullet -> Draw(hMemDC);
		}

		player.Draw(hMemDC);

		for( i = 0 ; i < now_effect.GetNum(); i++)
		{
			pEffect = (CEffect*)now_effect.GetIdx(i);
			pEffect->Draw(hMemDC);
		}

		for( i = 0 ; i < now_item.GetNum(); i++)
		{
			pItem = (CItem*)now_item.GetIdx(i);
			pItem->Draw(hMemDC);
		}
		item_slot.Draw(hMemDC);
		score.Draw(hMemDC);
		break;
	case UPGRADE:
		upgrade.Draw(hMemDC);
		break;
	}
	

	SelectObject(hMemDC,OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWndMain,hdc);
	InvalidateRect(hWndMain,NULL,FALSE);
}


//전체 그리기 담당 함수. 단순히 비트맵 버퍼를 hdc에 옮겨그림. 끝!
void PaintProc(HDC hdc)
{
	HDC hMemDC;
	HBITMAP OldBit;
	RECT crt;

	GetClientRect(hWndMain,&crt);
	hMemDC=CreateCompatibleDC(hdc);
	OldBit=(HBITMAP)SelectObject(hMemDC,dBuffer);
	BitBlt(hdc,0,0,crt.right,crt.bottom,hMemDC,0,0,SRCCOPY);
	SelectObject(hMemDC,OldBit);
	DeleteDC(hMemDC);
}



void DrawBitmap(HDC hdc,int x,int y,HBITMAP hBit,COLORREF Alpha, int wDest,int hDest,int wSrc,int hSrc,int wOrigin,int hOrigin)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	BITMAP bit;

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC,hBit);

	GetObject(hBit,sizeof(BITMAP),&bit);
	if(-1==wDest)
	{
		wDest=bit.bmWidth;
	}
	if(-1==hDest)
	{
		hDest=bit.bmHeight;
	}
	if(-1==wSrc)
	{
		wSrc=wDest;
	}
	if(-1==hSrc)
	{
		hSrc=hDest;
	}

	TransparentBlt(hdc,x,y,wDest,hDest,MemDC,wOrigin,hOrigin,wSrc-wOrigin,hSrc-hOrigin,Alpha);
	DeleteDC(MemDC);
}