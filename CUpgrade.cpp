#include "CUpgrade.h"
#include "WinMain.h"
#include "GameProcess.h"
#include "StageProcess.h"
#include "resource.h"
#include "CItem.h"

int const CUpgrade::button_num[ICON_NUM]
={4,1,1};

LevelInfo CUpgrade::ASLevel[7] //공격 속도 레벨별 수치. 3레벨까지 있음.
=
{
	{35,  5},
	{31, 19},
	{26, 33},
	{20, 51},
	{10, 71},
	{ 5,100},
	{ 2, -1}
};

LevelInfo CUpgrade::MSLevel[3] //이동 속도 레벨별 수치. 3레벨까지 있음.
=
{
	{2, 17},
	{3, 44},
	{4,-1}
};

int CUpgrade::button_string[ICON_NUM][MAX_BUTTON_NUM]
=
{
	{IDS_UBUTTON2,IDS_UBUTTON3,IDS_UBUTTON5,IDS_UBUTTON4},
	{IDS_UBUTTON4},
	{IDS_UBUTTON4}
};

int CUpgrade::GetASLevel()
{
	int i;

	for(i=0;i<7;i++)
	{
		if(player.GetAttackDelay()==ASLevel[i].num)
		{
			return i+1;
		}
	}

	return -1;
}

int CUpgrade::GetMSLevel()
{
	int i;

	for(i=0;i<3;i++)
	{
		if(player.GetSpeed()==MSLevel[i].num)
		{
			return i+1;
		}
	}

	return -1;
}


CUpgrade::CUpgrade(int a_next_stage)
{
	int i;
	back_ground.Load(24,true);
	cursor.Load(25,true);
	for(i=0;i<3;i++)
	{
		icon[i].Load(26,true);
		icon[i].SetCut(i,0);
	}
	button.Load(27,true);
	btn_cursor.Load(28,true);
	SetUpgrade(a_next_stage);
}

void CUpgrade::SetUpgrade(int a_next_stage)
{
	cur_pos=0;
	btn_pos=0;
	stat=ICON;
	next_stage=a_next_stage;
}

void CUpgrade::Draw(HDC hdc)
{
	char kp[40];
	int i;
	char buffer[256];
	
	back_ground.Draw(hdc,0,0);

	itoa(score.GetKillPoint(),kp,10);
	SetBkMode(hdc,TRANSPARENT);
	TextOut(hdc,20,20,"KillPoint:",strlen("KillPoint:"));
	TextOut(hdc,80,20,kp,strlen(kp));
	TextOut(hdc,20,40,"SPACE BAR : 다음 스테이지로",strlen("SPACE BAR : 다음 스테이지로"));
	TextOut(hdc,120,20,"ESC : 이전 항목으로",strlen("ESC : 이전 항목으로"));


	for(i=0;i<3;i++)
	{
		icon[i].SetCut(i,0);
		icon[i].Draw(hdc,ICON_SX+(50+ICON_SPLIT)*i,ICON_SY);
	}

	cursor.Draw(hdc,CURSOR_SX+(60+CURSOR_SPLIT)*cur_pos,CURSOR_SY);

	for(i=0;i<button_num[cur_pos];i++)
	{
		button.Draw(hdc,UBUTTON_SX,UBUTTON_SY+(28+UBUTTON_SPLIT)*i);
		LoadString(g_hInst,button_string[cur_pos][i],buffer,256);
		SetBkMode(hdc,TRANSPARENT);
		TextOut(hdc,UBUTTON_SX+5,UBUTTON_SY+(28+UBUTTON_SPLIT)*i+5,buffer,strlen(buffer));
	}
	if(stat==UBUTTON)
	{
		TextOut(hdc,30,550,"Enter : 항목 선택",strlen("Enter : 항목 선택"));
		btn_cursor.Draw(hdc,UBTNCUR_SX,UBTNCUR_SY+(40+UBTNCUR_SPLIT)*btn_pos);

		switch(cur_pos)
		{
		case STAT:
			switch(btn_pos)
			{
			case 0:
				TextOut(hdc,30,190,"현재 레벨:",strlen("현재 레벨:"));
				TextOut(hdc,30,220,"필요 Kill Point:",strlen("필요 Kill Point:"));
				i=GetASLevel();
				itoa(i,buffer,10);
				TextOut(hdc,110,190,buffer,strlen(buffer));
				if(ASLevel[i-1].kp==-1)
					TextOut(hdc,140,220,"더 이상 레벨업이 불가능합니다.",strlen("더 이상 레벨업이 불가능합니다."));
				else
				{
					itoa(ASLevel[i-1].kp,buffer,10);
					TextOut(hdc,140,220,buffer,strlen(buffer));
				}
				break;
			case 1:
				TextOut(hdc,30,190,"현재 레벨:",strlen("현재 레벨:"));
				TextOut(hdc,30,220,"필요 Kill Point:",strlen("필요 Kill Point:"));
				i=GetMSLevel();
				itoa(i,buffer,10);
				TextOut(hdc,110,190,buffer,strlen(buffer));
				if(MSLevel[i-1].kp==-1)
					TextOut(hdc,140,220,"더 이상 레벨업이 불가능합니다.",strlen("더 이상 레벨업이 불가능합니다."));
				else
				{
					itoa(MSLevel[i-1].kp,buffer,10);
					TextOut(hdc,140,220,buffer,strlen(buffer));
				}
				break;
			case 2:
				TextOut(hdc,30,190,"HP를 1 회복합니다.",strlen("HP를 1 회복합니다."));
				TextOut(hdc,30,220,"현재 HP:",strlen("현재 HP:"));
				i=player.GetHp();
				itoa(i,buffer,10);
				TextOut(hdc,92,220,buffer,strlen(buffer));
				TextOut(hdc,110,220,"/10",strlen("/10"));
				TextOut(hdc,30,250,"필요 Kill Point: 10",strlen("필요 Kill Point: 10"));
				break;
			case 3:
				TextOut(hdc,30,190,"이전 항목으로 돌아갑니다.",strlen("이전 항목으로 돌아갑니다."));
				break;
			}
			break;
		case SKILL:
			TextOut(hdc,30,190,"이전 항목으로 돌아갑니다.",strlen("이전 항목으로 돌아갑니다."));
			break;
		case WEAPON:
			TextOut(hdc,30,190,"이전 항목으로 돌아갑니다.",strlen("이전 항목으로 돌아갑니다."));
			break;
		}
	}
}

void CUpgrade::Processer()
{
	static bool put=true;

	
	if(stat==ICON)
	{
		cursor.Move();
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if(put)
				return;
			put=true;
	
			if(cur_pos==0)
				cur_pos=ICON_NUM-1;
			else
				cur_pos--;
			return;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			if(put)
				return;
			put=true;
	
			if(cur_pos==ICON_NUM-1)
				cur_pos=0;
			else
				cur_pos++;
			return;
		}
	}
	else
	{
		cursor.SetCut(3,0);
		btn_cursor.Move();
	}

	if(stat==UBUTTON)
	{
		if (GetKeyState(VK_UP) & 0x8000)
		{
			if(put)
				return;
			put=true;
	
			if(btn_pos==0)
				btn_pos=button_num[cur_pos]-1;
			else
				btn_pos--;
			return;
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			if(put)
				return;
			put=true;
	
			if(btn_pos==button_num[cur_pos]-1)
				btn_pos=0;
			else
				btn_pos++;
			return;
		}

		if(GetKeyState(VK_RETURN) & 0x8000)
		{
			if(put)
				return;
			put=true;

			SelectButton();
		}
	}

	if (GetKeyState(VK_RETURN) & 0x8000)
	{
		if(put)
			return;
		put=true;

		if(button_string[cur_pos][0]!=IDS_UBUTTON1)
			stat=UBUTTON;
		return;
	}
	if (GetKeyState(VK_ESCAPE) & 0x8000)
	{
		if(put)
			return;
		put=true;

		btn_pos=0;
		stat=ICON;
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		if(put)
			return;
		put=true;

		player.StageInit();
		/*if(next_stage==1)
		{
			MessageBox(hWndMain,"스테이지 1까지밖에 플레이가 안됩니다! alpha 0.6 버젼을 기대해주세요!","클리어! alpha 0.5",MB_OK);
			now_frame=0;
			now_enemy.Init();
			now_bullet.Init();
			now_effect.Init();
			now_item.Init();
			score.SetScore(0);
			score.SetKillPoint(5);
			player.Init();
			upgrade.SetUpgrade(0);
			for(i=0;i<STAGE_NUM;i++)
				StageData[i].Init();
				StageDataSet();
			mode=TITLE;
			return;
		}*/
		now_stage=next_stage;
		mode=STAGE;
	}

	put=false;
}


// 마우스 위치에 따라 커서 위치 변경
bool CUpgrade::MouseMove(WPARAM wParam, LPARAM lParam)
{
	int x=LOWORD(lParam), y=HIWORD(lParam);
	int i;

	switch(stat)
	{
	case ICON:
		if(y>=ICON_SY && y<=ICON_SY+50)
		{
			for(i=0;i<ICON_NUM;i++)
			{
				if(x>=ICON_SX+(50+ICON_SPLIT)*i &&
				   x<=ICON_SX+(50+ICON_SPLIT)*i+50)
				{
					cur_pos=i;
					return true;
				}
			}
		}
		return false;
	case UBUTTON:
		if(x>=UBUTTON_SX && x<=UBUTTON_SX+267)
		{
			for(i=0;i<button_num[cur_pos];i++)
			{
				if(y>=UBUTTON_SY+(28+UBUTTON_SPLIT)*i &&
				   y<=UBUTTON_SY+(28+UBUTTON_SPLIT)*i+28)
				{
					btn_pos=i;
					return true;
				}
			}
		}
		return false;
	}
	return false;
}


// 마우스 클릭을 통한 버튼 선택.
void CUpgrade::MouseSelect(WPARAM wParam, LPARAM lParam)
{
	switch(stat)
	{
	case ICON:
		if(MouseMove(wParam,lParam))
		{
			stat=UBUTTON;
		}
		break;
	case UBUTTON:
		if(MouseMove(wParam,lParam))
		{
			SelectButton();
		}
		break;
	}
}

void CUpgrade::SelectButton()
{
	int level;

	switch(cur_pos)
	{
		case STAT:
		switch(btn_pos)
		{
		case 0:
			level=GetASLevel()-1;
			if(ASLevel[level].kp==-1)
				break;

			if(score.GetKillPoint()>=ASLevel[level].kp)
			{
				player.SetAttackDelay(ASLevel[level+1].num);
				score.AddKillPoint(-ASLevel[level].kp);
			}
			break;
		case 1:
			level=GetMSLevel()-1;
			if(MSLevel[level].kp==-1)
				break;

			if(score.GetKillPoint()>=MSLevel[level].kp)
			{
				player.SetSpeed(MSLevel[level+1].num);
				score.AddKillPoint(-MSLevel[level].kp);
			}
			break;
		case 2:
			if(player.GetHp()<10 && score.GetKillPoint()>=10)
			{
				player.SetHp(player.GetHp()+1);
				score.AddKillPoint(-10);
			}
			break;
		case 3:
			btn_pos=0;
			stat=ICON;
			break;
		}
		break;

	case SKILL:
		switch(btn_pos)
		{
		case 0:
			btn_pos=0;
			stat=ICON;
			break;
		}
		break;

	case WEAPON:
		switch(btn_pos)
		{
		case 0:
			btn_pos=0;
			stat=ICON;
			break;
		}
		break;
	}
}