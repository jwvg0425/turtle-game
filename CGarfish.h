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
	int GetCutNum(); // ĳ���� ��ġ�� ������ Garfish �� �׷����� ���° ���̾�� �ϴ��� ����.
	int stat;  //���ƴ��� �������� ���� ������ ��������.
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