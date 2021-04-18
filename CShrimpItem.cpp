#include"CShrimpItem.h"
#include"WinMain.h"

CShrimpItem::CShrimpItem() : graphic(11,true)
{
}

CShrimpItem::CShrimpItem(double ax,double ay) : graphic(11,true)
{
	CShrimpItem* make_item=new CShrimpItem();

	make_item->x=ax;
	make_item->y=ay;
	//임의로 설정
	make_item->x_speed=0.1;
	make_item->y_speed=0.1;
	make_item->SetArea();
	now_item.Append(make_item);
}

void CShrimpItem::SetArea()
{
	area.left=int(x);
	area.top=int(y);
	area.right=int(x+30);
	area.bottom=int(y+30);
}

void CShrimpItem::Move()
{
	x+=x_speed;
	y+=y_speed;
	SetArea();
}

void CShrimpItem::Draw(HDC hdc)
{
	graphic.Draw(hdc,int(x),int(y));
}

void CShrimpItem::GetItem()
{
	player.SetMinusDelay(player.GetMinusDelay()+15);
}