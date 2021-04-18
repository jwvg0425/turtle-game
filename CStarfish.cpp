#include"CStarfish.h"
#include"GameProcess.h"
#include"WinMain.h"
#include"CEnemyBaseBullet.h"
#include"CShrimpItem.h"


CStarfish::CStarfish() : graphic(6,true)
{
}

CStarfish::CStarfish(int a_start,int a_move_type/*=1*/) : graphic(6,true)
{
	CStarfish* make_enemy=new CStarfish();

	make_enemy->move_type=a_move_type;
	make_enemy->create_frame=now_frame;
	make_enemy->attack_frame=70;
	make_enemy->max_hp=2;
	make_enemy->now_hp=make_enemy->max_hp;

	switch(a_move_type)
	{
	case 1:
		make_enemy->x=a_start;
		make_enemy->y=-50;
		make_enemy->x_speed=0.6;
		make_enemy->y_speed=0.4;
		break;
	case 2:
		make_enemy->x=-54;
		make_enemy->y=a_start;
		make_enemy->x_speed=1.7;
		make_enemy->y_speed=0;
	}
	make_enemy->SetArea();

	now_enemy.Append(make_enemy);
}

void CStarfish::Draw(HDC hdc)
{
	graphic.Draw(hdc,int(x),int(y));
}

void CStarfish::Move()
{
	int calc_frame=(now_frame-create_frame);
	//추가해라
	
	switch(move_type)
	{
	case 1:
		switch(calc_frame/10)
		{
		case 30:
			x_speed=0;
			y_speed=0;
			break;
		case 60:
			x_speed=0.5;
			y_speed=2;
			break;
		case 70:
			x_speed=2;
			y_speed=3;
			break;
		}
		break;
	case 2:
		switch(calc_frame/10)
		{
		case 10:
			x_speed=0;
			y_speed=0;
			break;
		case 30:
			x_speed=-1.7;
			y_speed=0;
			break;
		case 35:
			x_speed=1.7;
			y_speed=0;
			break;
		}
		break;
	}
	x+=x_speed;
	y+=y_speed;

	graphic.Move();
	if(calc_frame%attack_frame==0)
	{
		Attack();
	}
	SetArea();
}

void CStarfish::Attack()
{
	CEnemyBaseBullet tmp(x+13,y+28,-3,0);
	CEnemyBaseBullet tmp2(x+38,y+11,0,-3);
	CEnemyBaseBullet tmp3(x+69,y+28,3,0);
	CEnemyBaseBullet tmp4(x+16,y+65,-1.5,1.5);
	CEnemyBaseBullet tmp5(x+59,y+65,1.5,1.5);
	//5방향 공격!
}

void CStarfish::SetArea()
{
	area.left=int(x+24);
	area.top=int(y+26);
	area.right=int(x+57);
	area.bottom=int(y+61);
}

void CStarfish::Die()
{
	if(move_type<3)
	{
		score.AddKillPoint(1);
	}

	score.AddScore(16);
	if(random(100)>97)
		DropItem();
}

void CStarfish::DropItem()
{
	CShrimpItem make_item(x+40,y+40);
}