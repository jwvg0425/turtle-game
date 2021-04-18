#pragma once

#include"CItemSlot.h"


CItemSlot::CItemSlot(int ax,int ay)
{
	x=ax;
	y=ay;
	graphic.Load(30,true);
}

void CItemSlot::Draw(HDC hdc)
{
	graphic.Draw(hdc,x,y);
}