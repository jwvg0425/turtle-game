#pragma once
#include <Windows.h>

class CObject
{
protected:
	int x,y; //현재 x,y 좌표
	RECT area; //이 오브젝트가 차지하는 범위
public:
	virtual int GetX();
	virtual int GetY();
	void SetX(int ax){x=ax;}
	void SetY(int ay){y=ay;}
	virtual RECT GetArea(){return area;}
	virtual void Draw(HDC hdc)=0;
	virtual bool IsScreenOut(); // 화면밖으로 나갔는지 아닌지. 나갔으면 삭제시켜야함.
};