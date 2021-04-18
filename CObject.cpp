#include"CObject.h"
#include"WinMain.h"


int CObject::GetX()
{
	return x;
}

int CObject::GetY()
{
	return y;
}

bool CObject::IsScreenOut()
{
	if(area.top  > SCREEN_Y || area.bottom <0 ||
	   area.left > SCREEN_X || area.right  <0  )
	{
		return true;
	}
	return false;
}