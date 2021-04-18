#pragma once
#include"CObject.h"
#include"CDArray.h"
#include"CAnimation.h"

extern CDArray now_enemy; //���� �����ִ� ���� ���� ���� �迭.

class CEnemy : public CObject
{
protected:
	int move_type; //�̵� ���
	int max_hp, now_hp;
	int attack_frame; //���� ������ ���� ������.
	double x_speed, y_speed; // x,y�� �̵� �ӵ�
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