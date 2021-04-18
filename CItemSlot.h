#pragma once

#include"CAnimation.h"


class CItemSlot
{
private:
	CAnimation graphic;
	int x,y;
public:
	CItemSlot(int ax,int ay);
	void Draw(HDC hdc);
};