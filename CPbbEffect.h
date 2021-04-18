#pragma once

#include "CEffect.h"

class CPbbEffect : public CEffect
{
private:
	CAnimation graphic;
	CPbbEffect();
public:
	CPbbEffect(int ax, int ay);
	virtual bool Move();
	virtual void Draw(HDC hdc);
	virtual int GetX(){return x;}
	virtual int GetY(){return y;}
};