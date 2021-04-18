#include"CPlayer.h"
#include"WinMain.h"
#include"GameProcess.h"

CPlayer::CPlayer() : graphic(0,true), hp_bar(5,true)
{
	Init();
}

void CPlayer::SetArea()
{
	area.left=x+19;
	area.top=y+15;
	area.right=x+43;
	area.bottom=y+44;
}

int CPlayer::GetSpeed()
{
	return speed;
}

void CPlayer::SetSpeed(int as)
{
	speed=as;
}

void CPlayer::Input()
{
	int hp_cut=10-(now_hp*9/max_hp);
	hp_bar.SetCut((hp_cut-1)%5,(hp_cut-1)/5);
	graphic.Move();

	if (GetKeyState(MOVE_LEFT) & 0x8000)
	{
		if(x > 3) x-=GetSpeed();
	}
	if (GetKeyState(MOVE_RIGHT) & 0x8000)
	{   
		if(x < SCREEN_X - 63) x+=GetSpeed();
	}
	if (GetKeyState(MOVE_UP) & 0x8000)
	{
		if(y > 3) y-=GetSpeed();
	}
	if (GetKeyState(MOVE_DOWN) & 0x8000)
	{
		if(y < SCREEN_Y - 63) y+=GetSpeed();
	}
	if ( GetKeyState(SHOOT) & 0x8000 )
	{
		MakeBullet();
	}

	SetArea();
}
void CPlayer::Draw(HDC hdc)
{
	graphic.Draw(hdc,x,y);
	hp_bar.Draw(hdc,x+2,y+55);
}

void CPlayer::MakeBullet()
{
	int delay=(bullet_delay-minus_delay<0)?0:bullet_delay-minus_delay;

	switch ( bullet_type )
	{
	case BASE_BULLET:

		if ( now_frame - bullet_delay_frame > delay )
		{
			CPlayerBaseBullet tmp(x+26,y);

			bullet_delay_frame = now_frame;
		}

		break;
	}
}

void CPlayer::Init()
{
	x=370;
	y=500;
	max_hp=10;
	now_hp=max_hp;
	attack=1;
	SetArea();
	SetSpeed(2);
	bullet_type = BASE_BULLET;
	bullet_delay_frame = now_frame;
	bullet_delay = 35;
	minus_delay = 0;
}

void CPlayer::StageInit()
{
	x=370;
	y=500;
	bullet_delay_frame = now_frame;
}