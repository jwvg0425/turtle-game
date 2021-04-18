#pragma once
#include <Windows.h>

class CObject
{
protected:
	int x,y; //���� x,y ��ǥ
	RECT area; //�� ������Ʈ�� �����ϴ� ����
public:
	virtual int GetX();
	virtual int GetY();
	void SetX(int ax){x=ax;}
	void SetY(int ay){y=ay;}
	virtual RECT GetArea(){return area;}
	virtual void Draw(HDC hdc)=0;
	virtual bool IsScreenOut(); // ȭ������� �������� �ƴ���. �������� �������Ѿ���.
};