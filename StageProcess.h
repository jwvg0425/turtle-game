#pragma once

#include"CDArray.h"
#define STAGE_NUM 2

extern CDArray StageData[STAGE_NUM];
extern CBitmap BgGraphic[STAGE_NUM];
extern CBitmap BgEffect;
extern int now_stage;

struct tag_stage
{
	int frame,kind,start,move_type;
};

void MakeEnemy();
void makeLCF(int start, int move_type);
void makeSF(int start, int move_type);
void makeBCF(int start);
void makeGF(int start,int move_type);
void StageDataSet();
