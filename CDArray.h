#pragma once
#include<stdlib.h>

//�����ϰ� ������ �ְ� ���� �� �� �� ����.
class CDArray
{
private:
	unsigned size;
	unsigned num;
	unsigned growby;
	unsigned typesize;
	void** ar; //������.
public:
	CDArray(unsigned asize=5, unsigned agrowby=4,unsigned atypesize=sizeof(void*));
	void InitArray(unsigned asize, unsigned agrowby);
	void Insert(int idx,void* value);
	void Delete(int idx);
	void Append(void* value);
	void* GetIdx(int idx);
	int GetNum(){return num;}
	void Init();
	~CDArray();
};