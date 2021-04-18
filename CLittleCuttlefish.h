#pragma once
#include "CEnemy.h"

class CLittleCuttlefish : public CEnemy
{
private:
	int create_frame; //������ �ñ�. �̰� �������� �����.
	CAnimation graphic;
	CLittleCuttlefish();
	virtual void DropItem();
public:
	int GetX();
	int GetY();
	CLittleCuttlefish(int a_start,int a_move_type=1);
	virtual void Draw(HDC hdc);
	virtual void Move();
	virtual void Attack();
	virtual void SetArea();
	virtual void Die();
};