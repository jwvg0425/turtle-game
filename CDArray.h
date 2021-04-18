#pragma once
#include<stdlib.h>

//순수하게 데이터 넣고 빼고 뭐 몇 개 없음.
class CDArray
{
private:
	unsigned size;
	unsigned num;
	unsigned growby;
	unsigned typesize;
	void** ar; //포인터.
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