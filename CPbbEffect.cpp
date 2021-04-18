#include "CPbbEffect.h"

CPbbEffect::CPbbEffect() : graphic(3,false)
{
}

CPbbEffect::CPbbEffect(int ax, int ay) : graphic(3,false)
{
	CPbbEffect* make_effect= new CPbbEffect();

	make_effect->x=ax;
	make_effect->y=ay;
	now_effect.Append(make_effect);
}

bool CPbbEffect::Move()
{
	graphic.Move();
	return graphic.GetDraw();
}

void CPbbEffect::Draw(HDC hdc)
{
	graphic.Draw(hdc,x,y);
}