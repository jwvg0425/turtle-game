#pragma once
#include<Windows.h>

void DrawBitmap(HDC hdc,int x,int y,HBITMAP hBit,COLORREF Alpha, 
	int wDest=-1,int hDest=-1,int wSrc=-1,int hSrc=-1,int wOrigin=0,int hOrigin=0);
extern HBITMAP dBuffer;
void PaintProc(HDC hdc);
void BufferProc();