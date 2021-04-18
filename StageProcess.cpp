#include"WinMain.h"
#include"resource.h"
#include"StageProcess.h"
#include"CLittleCuttlefish.h"
#include"CStarfish.h"
#include"CBigCuttlefish.h"
#include"GameProcess.h"
#include"CGarfish.h"

CDArray StageData[STAGE_NUM] = {};
CBitmap BgGraphic[STAGE_NUM];
CBitmap BgEffect;
int now_stage; //���� �÷������� ��������.

//�ӽ÷� tag_stage�� �����迭��Ų���� �ش� �����͸� �Ѱ���. �̰� �޾Ƽ� CDArray�� �־���ٰ� ���� ��.
tag_stage* MakeTmpData();

void StageDataSet()
{
	int i;
	HANDLE hFile; //�ִϸ��̼� �����͸� �ҷ����� ���� ���� �ڵ�
	TCHAR str[256]; //��θ� �ҷ����� ���ڿ�.
	TCHAR buf[18]; //�б�� ����.
	TCHAR* pBuf; //��ȯ�� ������
	DWORD dwRead; //���� ��. �̰ɷ� ������ ���� �� �Ǻ�.
	tag_stage* tmp;
	

	for(i=0;i<STAGE_NUM;i++)
	{
		LoadString(g_hInst,IDS_STAGE1+i,str,256);
		hFile=CreateFile(str,GENERIC_READ,0,NULL,OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,NULL);
		if(INVALID_HANDLE_VALUE!=hFile)
		{
			for(ReadFile(hFile,buf,18,&dwRead,NULL);
				dwRead;
				ReadFile(hFile,buf,18,&dwRead,NULL))
			{
				tmp=MakeTmpData();
				pBuf = strtok(buf," ");
				tmp->frame=atoi(pBuf);
				pBuf = strtok(NULL," ");
				tmp->kind=atoi(pBuf);
				pBuf = strtok(NULL," ");
				tmp->start=atoi(pBuf);
				pBuf = strtok(NULL," ");
				tmp->move_type=atoi(pBuf);
				strset(buf,' ');
				strset(str,' ');
				StageData[i].Append(tmp);
			}
		}
		CloseHandle(hFile);
	}
}

tag_stage* MakeTmpData()
{
	tag_stage* tmp=new tag_stage;
	return tmp;
}

//���� ����
void MakeEnemy()
{
	int i;
	tag_stage* pStage;

	for(i=0;i<StageData[now_stage].GetNum();i++)
	{
		pStage=(tag_stage*)StageData[now_stage].GetIdx(i);

		if(pStage->frame<now_frame/10)
		{
			switch(pStage->kind)
			{
			case 1: //���� ��¡��
				makeLCF(pStage->start,pStage->move_type);
				StageData[now_stage].Delete(i);
				break;
			case 2: //�Ұ��縮
				makeSF(pStage->start,pStage->move_type);
				StageData[now_stage].Delete(i);
				break;
			case 3: // (�ϴ���) �Ŵ� ��¡�� - 1�������� ����
				makeBCF(pStage->start);
				StageData[now_stage].Delete(i);
				break;
			case 4: // ����ġ
				makeGF(pStage->start,pStage->move_type);
				StageData[now_stage].Delete(i);
				break;
			}
		}
	}
}
void makeLCF(int start, int move_type)
{
	CLittleCuttlefish tmp(start,move_type);
}

void makeSF(int start, int move_type)
{
	CStarfish tmp(start,move_type);
}

void makeBCF(int start)
{
	CBigCuttlefish tmp(start);
}

void makeGF(int start,int move_type)
{
	CGarfish tmp(start,move_type);
}