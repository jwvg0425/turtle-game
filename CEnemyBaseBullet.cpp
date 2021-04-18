#include "CEnemyBaseBullet.h"

CEnemyBaseBullet::CEnemyBaseBullet() : graphic(4,true)
{
}

CEnemyBaseBullet::CEnemyBaseBullet(double ax, double ay, double ax_speed, double ay_speed) : graphic(4,true)
{
	CEnemyBaseBullet* make_bullet=new CEnemyBaseBullet();

	make_bullet->x=ax;
	make_bullet->y=ay;
	make_bullet->x_speed=ax_speed;
	make_bullet->y_speed=ay_speed;
	make_bullet->is_player=false;
	SetArea();
	now_bullet.Append(make_bullet);
}

void CEnemyBaseBullet::Attack()
{
}

void CEnemyBaseBullet::Draw(HDC hdc)
{
	graphic.Draw(hdc,int(x),int(y));
}

void CEnemyBaseBullet::Move()
{
	x+=x_speed;
	y+=y_speed;
	SetArea();
}

void CEnemyBaseBullet::SetArea()
{
	area.left = int(x);
	area.right = int(x+8);
	area.top = int(y);
	area.bottom = int(y+8);
}

bool CEnemyBaseBullet::IsCollusion(RECT enemy_rect)
{
	if ( area.left > enemy_rect.right ||
		 area.right < enemy_rect.left ||
		 area.top > enemy_rect.bottom ||
		 area.bottom < enemy_rect.top   )
	{
		return false;
	}
	return true;
}