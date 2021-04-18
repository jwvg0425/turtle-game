#pragma once

#include "CAnimation.h"


class CScore
{
private:
	int x,y;
	int score;
	int kp; // 킬 포인트
	CAnimation score_graphic;
	CAnimation number_graphic[8];
	CScore();
public:
	CScore(int ax,int ay);
	int GetScore(){return score;}
	int GetKillPoint(){return kp;}
	void SetKillPoint(int n){kp=n;}
	void AddKillPoint(int n){SetKillPoint(GetKillPoint()+n);}
	void SetScore(int n){score=n;}
	void AddScore(int n){SetScore(GetScore()+n);}
	void InitScore(){score=0;kp=0;}
	void Draw(HDC hdc);
};