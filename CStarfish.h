#pragma once
#include "CEnemy.h"

class CStarfish : public CEnemy
{
	int create_frame;
	CAnimation graphic;
	CStarfish();
	virtual void DropItem();
public:
	CStarfish(int a_start,int a_move_type=1);
	virtual void Draw(HDC hdc);
	virtual void Move();
	virtual void Attack();
	virtual void SetArea();
	virtual void Die();
};