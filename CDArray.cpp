#pragma once
#include"CDArray.h"
#include<windows.h>
#include<assert.h>

CDArray::CDArray(unsigned asize,unsigned agrowby,unsigned atypesize)
{
	size=asize;
	growby=agrowby;
	num=0;
	typesize=atypesize;
	ar=(void**)malloc(size*typesize);
}

void CDArray::Insert(int idx,void* value)
{
	unsigned need;

	need=num+1;
	if(need > size)
	{
		size=need+growby;
		ar=(void**)realloc(ar,size*typesize);
	}
	memmove(ar+idx+1,ar+idx,(num-idx)*typesize);
	ar[idx]=value;
	num++;
}

void CDArray::Delete(int idx)
{
	if(num!=0)
	{
		delete ar[idx];
		memmove(ar+idx,ar+idx+1,(num-idx-1)*typesize);
		num--;
	}
}

void CDArray::Append(void* value)
{
	Insert(num,value);
}

CDArray::~CDArray()
{
	int i;

	for(i=0;i<num;)
	{
		Delete(i);
	}
	free(ar);
}

void* CDArray::GetIdx(int idx)
{
	assert(idx<num);
	return ar[idx];
}

void CDArray::Init()
{
	int i=0;

	while(i<num) Delete(i);
}