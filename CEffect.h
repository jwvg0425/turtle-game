#pragma once

#include "CAnimation.h"
#include "CDArray.h"
#include "CAnimation.h"

#define PBB_EFFECT 1 // �÷��̾� �⺻ �Ѿ� ����Ʈ.

// �������� ���� ȿ���鿡 ���õ� �͵�.

extern CDArray now_effect; //����Ʈ ����.


class CEffect
{
protected:
	int x,y;
public:
	virtual bool Move()=0;
	virtual void Draw(HDC hdc)=0;
};