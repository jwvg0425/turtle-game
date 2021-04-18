#include"CScore.h"



CScore::CScore(int ax,int ay) : score_graphic(20,true)
{
	int i;

	x=ax;
	y=ay;
	score=0;

	for(i=0;i<8;i++)
	{
		number_graphic[i].Load(21,true);
	}

}

void CScore::Draw(HDC hdc)
{
	int div,px=80,i;

	score_graphic.Draw(hdc,x,y-1);

	for(div=100000000,i=0;div!=1;div/=10,px+=16,i++)
	{
		number_graphic[i].SetCut((score%div)/(div/10),0);
		number_graphic[i].Draw(hdc,x+px,y);
	}
}