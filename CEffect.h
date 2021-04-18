#pragma once

#include "CAnimation.h"
#include "CDArray.h"
#include "CAnimation.h"

#define PBB_EFFECT 1 // 플레이어 기본 총알 이펙트.

// 여러가지 게임 효과들에 관련된 것들.

extern CDArray now_effect; //이펙트 관리.


class CEffect
{
protected:
	int x,y;
public:
	virtual bool Move()=0;
	virtual void Draw(HDC hdc)=0;
};