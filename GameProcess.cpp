#include"CAnimation.h"
#include"Paint.h"
#include"WinMain.h"
#include"CPlayer.h"
#include"StageProcess.h"
#include"GameProcess.h"
#include"CEnemy.h"
#include"CEffect.h"
#include"CPbbEffect.h"
#include"CItem.h"

int mode;

int now_frame;

void GameProcesser()
{
	int i;
	int enemy_hp;
	static int delay;
	CEnemy* pEnemy;
	CBullet* pBullet;
	CEffect* pEffect;
	CItem* pItem;

	if(GetActiveWindow() == hWndMain)
	{
		switch(mode)
		{
		case TITLE:
			title.TitleProcesser();
			break;
		case STAGE:
			player.Input();
			MakeEnemy();
			for(i=0;i<now_enemy.GetNum();i++)
			{
				pEnemy=(CEnemy*)now_enemy.GetIdx(i);
				pEnemy->SetArea();
				if(pEnemy->IsScreenOut())
				{
					now_enemy.Delete(i);
					continue;
				}
				pEnemy->Move();
			}
	
			for( i = 0 ; i < now_bullet.GetNum();i++)
			{
				pBullet = (CBullet*)now_bullet.GetIdx(i);
				pBullet->Move();
	
				if(pBullet->IsScreenOut())
				{
					now_bullet.Delete(i);
					continue;
				}

				if(pBullet->GetIsPlayer())
				{
					for( int j = 0 ; j < now_enemy.GetNum(); j++)
					{
						pEnemy = (CEnemy*)now_enemy.GetIdx(j);
						if( pBullet->IsCollusion( pEnemy->GetArea() ) )
						{
							MakeEffect(pBullet->GetEffectType(),
							pBullet->GetX()-8,pBullet->GetY()-15);
		
							now_bullet.Delete(i);
							enemy_hp=pEnemy->GetHP();
	
							if(enemy_hp-player.GetAttack()<=0)
							{
								pEnemy->Die();
								now_enemy.Delete(j);
							}
							else
								pEnemy->SetHP(pEnemy->GetHP()-player.GetAttack());
					
							break;
						}
					}
				}
				else
				{
					if(pBullet->IsCollusion(player.GetArea()))
					{
						MakeEffect(pBullet->GetEffectType(),
								   pBullet->GetX()-8,pBullet->GetY()-15);
						now_bullet.Delete(i);
					
						//TODO: 캐릭터 HP, 게임 오버 관련 처리 해야 함.
						if(player.GetHp()-1<=0)
						{
							GameOver();
							return;
						}
						player.SetHp(player.GetHp()-1); // 테스트용.
					}
				}	
			}

			for( i = 0 ; i < now_effect.GetNum() ; i ++ )
			{
				pEffect=(CEffect*)now_effect.GetIdx(i);
				if(!pEffect->Move())
					now_effect.Delete(i);
			}

			for(i=0; i< now_item.GetNum();i++)
			{
				pItem=(CItem*)now_item.GetIdx(i);
				pItem->Move();
				if(pItem->IsScreenOut())
				{
					now_item.Delete(i);
					continue;
				}

				if(pItem->IsCollision())
				{
					pItem->GetItem();
					now_item.Delete(i);
				}
			}

			now_frame++;
			break;
		case GAME_OVER:
			break;
		case UPGRADE:
			upgrade.Processer();
			break;
		case STAGE_CLEAR:
			player.Move();
			if(delay<200)
			{
				delay++;
				break;
			}
			player.SetY(player.GetY()-2);
			if(player.GetY()<-150)
			{
				delay=0;
				StageClear();
			}
			break;
		}
	}

	BufferProc();
}

void GameOver()
{
	int i;

	mode=GAME_OVER;
	MessageBox(hWndMain,"게임 오버입니다! 타이틀로 뿅!","게임오버 alpha 0.6",MB_OK);
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
}

void MakeEffect(int type,int x, int y)
{
	switch(type)
	{
	case PBB_EFFECT:
		CPbbEffect tmp(x,y);
		break;
	}
}

void StageClear()
{
	int i;

	now_frame=0;
	now_enemy.Init();
	now_bullet.Init();
	now_effect.Init();
	now_item.Init();
	upgrade.SetUpgrade(1);
	for(i=0;i<STAGE_NUM;i++)
		StageData[i].Init();
	StageDataSet();
	mode=UPGRADE;
}