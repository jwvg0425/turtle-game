#include "CBigCuttlefishLeg.h"
#include "WinMain.h"

int CBigCuttlefishLeg::num=0;

POINT CBigCuttlefishLeg::plus_data[6]
={{-24,240},{44,240},{54,232},{-52,235},{30,240},{-40,240}};

//이거 설정.
RECT CBigCuttlefishLeg::cut[2][9]
={{{65,30,153,206},{59,17,159,203},{68,2,140,185},{44,8,155,157},
{66,11,157,169},{65,30,153,206},{147,30,235,206},{150,8,264,148},{147,30,235,206}},
{{147,30,235,206},{143,17,243,203},{160,2,232,185},{145,8,256,157},
{143,11,234,169},{147,30,235,206},{65,30,153,206},{36,8,150,148},{65,30,153,206}}};


CBigCuttlefishLeg::CBigCuttlefishLeg()
{
}

CBigCuttlefishLeg::CBigCuttlefishLeg(int a_type,CBigCuttlefish* a_entity)
{
	CBigCuttlefishLeg* make_enemy=new CBigCuttlefishLeg();

	CBigCuttlefishLeg::num+=2;
	make_enemy->type=a_type;
	make_enemy->graphic.Load(a_type+13,true);
	make_enemy->entity=a_entity;
	make_enemy->max_hp=5;
	make_enemy->now_hp=make_enemy->max_hp;
	make_enemy->x=make_enemy->entity->x+plus_data[make_enemy->type].x;
	make_enemy->y=make_enemy->entity->y+plus_data[make_enemy->type].y;
	make_enemy->SetArea();
	make_enemy->entity->leg[make_enemy->type]=make_enemy;
	now_enemy.Append(make_enemy);
}

CBigCuttlefishLeg::~CBigCuttlefishLeg()
{
	CBigCuttlefishLeg::num--;
}

void CBigCuttlefishLeg::Draw(HDC hdc)
{
	graphic.Draw(hdc,int(x),int(y));
}

void CBigCuttlefishLeg::Move()
{ 
	graphic.Move();
	x=entity->x+plus_data[type].x;
	y=entity->y+plus_data[type].y;
	SetArea();
	Attack();
}

void CBigCuttlefishLeg::Attack()
{
	static int delay=0;

	if ( area.left > player.GetArea().right ||
		 area.right < player.GetArea().left ||
		 area.top > player.GetArea().bottom ||
		 area.bottom < player.GetArea().top   )
	{
		return;
	}
	if(delay%(2*num*num)==0)
	{
		if(player.GetHp()-1<=0)
		{
			delay=0;
			GameOver();
		}
		else
		{
			player.SetHp(player.GetHp()-1);
			MakeEffect(PBB_EFFECT,player.GetX()+random(20),player.GetY()+random(20));
			delay=0;
		}
	}
	delay++;
}

void CBigCuttlefishLeg::SetArea()
{
	area.left=int(x)+cut[type%3][graphic.GetNowCut()].top;
	area.top=int(y)+cut[type%3][graphic.GetNowCut()].left;
	area.right=int(x)+cut[type%3][graphic.GetNowCut()].right;
	area.bottom=int(y)+cut[type%3][graphic.GetNowCut()].bottom;
}

void CBigCuttlefishLeg::Die()
{
	score.AddScore(47);
}

void CBigCuttlefishLeg::DropItem()
{
}