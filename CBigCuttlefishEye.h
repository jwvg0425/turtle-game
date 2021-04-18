#pragma once

#include "CBigCuttlefish.h"


class CBigCuttlefishEye : public CEnemy
{
	friend class CBigCuttlefish;
	friend class CBigCuttlefishBody;
private:
	int type; //哭率 传彬? 坷弗率 传彬?
	CBigCuttlefish* entity;
	CAnimation graphic;
	virtual void DropItem();
	CBigCuttlefishEye();
public:
	CBigCuttlefishEye(int a_type,CBigCuttlefish* a_entity);
	virtual void Draw(HDC hdc);
	virtual void Move();
	virtual void Attack();
	virtual void SetArea();
	virtual void Die();
	virtual bool IsScreenOut(){return false;}
};

