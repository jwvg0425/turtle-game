#pragma once

#include "CObject.h"
#include "CDArray.h"
#include "CAnimation.h"
#include "CEffect.h"
#define PBB_X_SPD 0
#define PBB_Y_SPD -6.5

extern CDArray now_bullet;

class CBullet : public CObject
{
protected:
	double x_speed,y_speed;
	double x,y;
	bool is_player;
public:
	virtual void Draw(HDC hdc)=0;
	virtual void Move()=0;
	virtual void Attack()=0;
	virtual void SetArea()=0;
	virtual bool IsCollusion(RECT enemy_rect)=0;
	virtual int GetEffectType()=0;
	bool GetIsPlayer(){return is_player;}
};