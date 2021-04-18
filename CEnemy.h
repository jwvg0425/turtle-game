#pragma once
#include"CObject.h"
#include"CDArray.h"
#include"CAnimation.h"

extern CDArray now_enemy; //현재 나와있는 몬스터 관리 동적 배열.

class CEnemy : public CObject
{
protected:
	int move_type; //이동 방식
	int max_hp, now_hp;
	int attack_frame; //공격 딜레이 계산용 프레임.
	double x_speed, y_speed; // x,y축 이동 속도
	double x,y;
	virtual void DropItem()=0;
public:
	virtual void Draw(HDC hdc)=0;
	virtual void Move()=0;
	virtual void Attack()=0;
	virtual void SetArea()=0;
	virtual void Die()=0;
	virtual int GetHP(){return now_hp;}
	virtual void SetHP(int hp) { if (hp>0 && hp<max_hp) now_hp=hp;}
};