#include "CPlayerBaseBullet.h"

CPlayerBaseBullet::CPlayerBaseBullet() : graphic(2,true)
{
}

CPlayerBaseBullet::CPlayerBaseBullet(int x, int y) : graphic(2,true)
{
	CPlayerBaseBullet* make_bullet=new CPlayerBaseBullet();

	make_bullet->x=double(x);
	make_bullet->y=double(y);
	make_bullet->x_speed=double(PBB_X_SPD);
	make_bullet->y_speed=double(PBB_Y_SPD);
	make_bullet->is_player=true;
	SetArea();
	now_bullet.Append(make_bullet);
}

void CPlayerBaseBullet::Attack()
{
}

void CPlayerBaseBullet::Draw(HDC hdc)
{
	graphic.Draw(hdc,int(x),int(y));
}

void CPlayerBaseBullet::Move()
{
	x+=x_speed;
	y+=y_speed;
	SetArea();
}

void CPlayerBaseBullet::SetArea()
{
	area.left = int(x);
	area.right = int(x+3);
	area.top = int(y);
	area.bottom = int(y+11);
}

bool CPlayerBaseBullet::IsCollusion(RECT enemy_rect)
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