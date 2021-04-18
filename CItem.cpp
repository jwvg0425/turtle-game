#include "CItem.h"
#include "WinMain.h"


CDArray now_item(5,3,sizeof(CItem*));

bool CItem::IsCollision()
{
	if ( area.left > player.GetArea().right ||
		 area.right < player.GetArea().left ||
		 area.top > player.GetArea().bottom ||
		 area.bottom < player.GetArea().top   )
	{
		return false;
	}
	return true;
}