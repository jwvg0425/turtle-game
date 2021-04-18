#pragma once

#include "CBigCuttlefish.h"
#include "GameProcess.h"
#define LEFT 0
#define RIGHT 1


class CBigCuttlefishLeg : public CEnemy
{
	friend class CBigCuttlefish;
	//TODO: 본체와 좌표 관계 설정을 plus_data 배열에 저장함. CBigCuttlefish 에서도 사용해야하므로 friend 선언할 것.
	static POINT plus_data[6];
	static RECT cut[2][9]; // 애니메이션 컷에 따른 영역 설정용 변수.
	static int num;   // 다리 개수.
private:
	int type; //왼쪽? 오른쪽?
	CAnimation graphic;
	CBigCuttlefish* entity; // 본체 포인터
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

