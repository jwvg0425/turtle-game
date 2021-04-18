#pragma once

#include "CBigCuttlefish.h"
#include "GameProcess.h"
#define LEFT 0
#define RIGHT 1


class CBigCuttlefishLeg : public CEnemy
{
	friend class CBigCuttlefish;
	//TODO: ��ü�� ��ǥ ���� ������ plus_data �迭�� ������. CBigCuttlefish ������ ����ؾ��ϹǷ� friend ������ ��.
	static POINT plus_data[6];
	static RECT cut[2][9]; // �ִϸ��̼� �ƿ� ���� ���� ������ ����.
	static int num;   // �ٸ� ����.
private:
	int type; //����? ������?
	CAnimation graphic;
	CBigCuttlefish* entity; // ��ü ������
	CBigCuttlefishLeg();
	virtual void DropItem();
public:
	CBigCuttlefishLeg(int a_type,CBigCuttlefish* a_entity);
	~CBigCuttlefishLeg();
	virtual void Draw(HDC hdc);
	virtual void Move();
	virtual void Attack();
	virtual void SetArea();
	virtual void Die();
	virtual bool IsScreenOut(){return false;}
};

