#pragma once

#include"CItem.h"
#include"CAnimation.h"


class CShrimpItem : public CItem
{
private:
	CAnimation graphic;
	CShrimpItem();
public:
	CShrimpItem(double ax,double ay);
	virtual void Draw(HDC hdc);
	virtual void Move();
	virtual void SetArea();
	virtual void GetItem();
};