#pragma once
#include"CBullet.h"
#include"CEnemy.h"


class CEnemyBaseBullet : public CBullet
{
private:
	CAnimation graphic;
	CEnemyBaseBullet();
public:
	CEnemyBaseBullet(double ax, double ay, double ax_speed, double ay_speed);
	virtual void Draw(HDC hdc);
	virtual void Move();
	virtual void Attack();
	virtual void SetArea();
	virtual bool IsCollusion(RECT enemy_rect);
	virtual int GetEffectType(){return PBB_EFFECT;}
	virtual int GetX(){return int(x);}
	virtual int GetY(){return int(y);}
	int GetDamage(){return 1;}
};