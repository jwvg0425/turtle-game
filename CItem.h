#pragma once

#include"CObject.h"
#include"CDArray.h"

extern CDArray now_item;

class CItem : public CObject
{
protected:
	double x_speed,y_speed;
	double x,y;
public:
	virtual void Draw(HDC hdc)=0;
	virtual void Move()=0;
	virtual void SetArea()=0;
	virtual void GetItem()=0;
	bool IsCollision();
};