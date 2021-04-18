#include "CGarfish.h"
#include "GameProcess.h"
#include "CShrimpItem.h"
#include "WinMain.h"
#include <math.h>

double CGarfish::std[9]
=
{
	297.5,252.5,207.5,162.5,117.5,72.5,
	27.5,-17.5,-62.5
};



CGarfish::CGarfish() : graphic(29,true)
{
}

CGarfish::CGarfish(int a_start, int a_move_type) : graphic(29,true)
{
	CGarfish* make_enemy = new CGarfish();

	make_enemy->move_type=a_move_type;
	make_enemy->create_frame=now_frame;
	make_enemy->max_hp=2;
	make_enemy->now_hp=make_enemy->max_hp;
	make_enemy->stat=NORMAL;
	make_enemy->delay=0;

	switch(a_move_type)
	{
	case 1:
		make_enemy->x=a_start;
		make_enemy->y=-50;
		make_enemy->x_speed=0;
		make_enemy->y_speed=2;
		break;
	}
	make_enemy->SetArea();

	now_enemy.Append(make_enemy);
}

void CGarfish::Draw(HDC hdc)
{
	graphic.Draw(hdc,int(x),int(y));
}

void CGarfish::Move()
{
	int calc_frame=(now_frame-create_frame);

	switch(move_type)
	{
	case 1:

		switch(calc_frame/10)
		{
		case 10:
			y_speed=0;
			break;
		}

		break;
	}
	x+=x_speed;
	y+=y_speed;

	if(stat==READY_ATTACK)
	{
		delay++;
		if(delay>15)
			stat=ATTACK;
		else
			return;
	}

	if(stat==ATTACK)
	{
		Attack();
		return;
	}

	if(calc_frame/10>=18&&stat==NORMAL)
	{
		if(GetCutNum()==graphic.GetNowCut())
		{
			x_speed=(player.GetX()-x)/100;
			y_speed=(player.GetY()-y)/100;
			stat=READY_ATTACK;
		}
		else
		{
			graphic.Move();
		}
	}
	else if(calc_frame/10>=10)
	{
		graphic.Move();
	}
}

void CGarfish::Attack()
{
	x+=x_speed;
	y+=y_speed;
	
	if ( area.left > player.GetArea().right ||
		 area.right < player.GetArea().left ||
		 area.top > player.GetArea().bottom ||
		 area.bottom < player.GetArea().top   )
	{
		return;
	}
	stat=DIE;

	MakeEffect(PBB_EFFECT,player.GetX()+random(20),player.GetY()+random(20));
	if(player.GetHp()-2<=0)
		GameOver();
	else
		player.SetHp(player.GetHp()-2);
}

void CGarfish::Die()
{
	score.AddScore(21);
	score.AddKillPoint(1);
	if(random(100)>96)
		DropItem();
}

void CGarfish::DropItem()
{
	CShrimpItem make_item(x+40,y+40);
}

int CGarfish::GetCutNum()
{
	double tx=player.GetX()-x,ty=player.GetY()-y;
	double angle=-atan2(ty, tx) * 180 / PIE;
	int i;

	if(angle<-62.5)
		angle=360+angle;

	for(i=0;i<8;i++)
	{
		if(angle<=std[i] && angle>=std[i+1])
		{
			return i;
		}
	}
	return -1;
}

void CGarfish::SetArea()
{
	area.top=int(y)+20;
	area.left=int(x)+20;
	area.right=int(x)+60;
	area.bottom=int(y)+60;
}

bool CGarfish::IsScreenOut()
{
	if(stat==DIE)
		return true;

	if(area.top  > SCREEN_Y || area.bottom <0 ||
	   area.left > SCREEN_X || area.right  <0  )
	{
		return true;
	}
	return false;
}