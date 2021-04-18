#include"CTitle.h"
#include"GameProcess.h"
#include"WinMain.h"

CTitle::CTitle() : graphic(7,true), cursor(8,true), story(9,true), exit(10,true)
{
	cur_pos=0;
}

void CTitle::Draw(HDC hdc)
{
	graphic.Draw(hdc,0,0);
	cursor.Draw(hdc,300,BUTTON_START+(27+BUTTON_SPLIT)*cur_pos);
	story.Draw(hdc,350,BUTTON_START);
	exit.Draw(hdc,350,BUTTON_START+(27+BUTTON_SPLIT));
}

void CTitle::SelectButton()
{
	switch(cur_pos)
	{
	case 0: //story
		mode=UPGRADE;
		break;
	case 1: //exit
		DestroyWindow(hWndMain);
		break;
	}

}

void CTitle::TitleProcesser()
{
	static bool put=false;

	if (GetKeyState(VK_RETURN) & 0x8000)
	{
		if(put)
			return;
		put=true;

		SelectButton();
		return;
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		if(put)
			return;
		put=true;

		if(cur_pos==0)
			cur_pos=BUTTON_NUM-1;
		else
			cur_pos--;
		return;
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		if(put)
			return;
		put=true;

		if(cur_pos==BUTTON_NUM-1)
			cur_pos=0;
		else
			cur_pos++;
		return;
	}
	put=false;
}

//포지션 바뀌면 true 아니면 false. 즉, 버튼 위에 마우스가 있는 지 없는 지 판별 가능.
bool CTitle::MouseMove(WPARAM wParam, LPARAM lParam)
{
	int x=LOWORD(lParam), y=HIWORD(lParam);
	int i;

	if(x>=350&&x<=450)
	{
		for(i=0;i<BUTTON_NUM;i++)
		{
			if(y>=BUTTON_START+(27+BUTTON_SPLIT)*i &&
			   y<=BUTTON_START+(27+BUTTON_SPLIT)*i+27)
			{
				cur_pos=i;
				return true;
			}
		}
	}
	return false;
}

void CTitle::MouseSelect(WPARAM wParam, LPARAM lParam)
{
	if(MouseMove(wParam,lParam))
	{
		SelectButton();
	}
}