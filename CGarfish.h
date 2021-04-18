#pragma once

#include "CEnemy.h"
#define PIE 3.141592
#define NORMAL 0
#define ATTACK 1
#define READY_ATTACK 2
#define DIE			3


class CGarfish : public CEnemy
{
	static double std[9];
private:
	int create_frame;
	CAnimation graphic;
	CGarfish();
	virtual void DropItem();
	int GetCutNum(); // 캐릭터 위치에 따르면 Garfish 의 그래픽이 몇번째 컷이어야 하는지 산출.
	int stat;  //돌아댕기는 상태인지 공격 돌입한 상태인지.
	int delay;
public:
	CGarfish(int a_start,int a_move_type);
	virtual void Draw(HDC hdc);
	virtual void Move();
	virtual void Attack();
	virtual void SetArea();
	virtual void Die();
	virtual bool IsScreenOut();
};