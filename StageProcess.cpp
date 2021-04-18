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
int now_stage; //현재 플레이중인 스테이지.

//임시로 tag_stage형 동적배열시킨다음 해당 포인터를 넘겨줌. 이걸 받아서 CDArray에 넣어놨다가 쓰면 됨.
tag_stage* MakeTmpData();

void StageDataSet()
{
	int i;
	HANDLE hFile; //애니메이션 데이터를 불러오기 위한 파일 핸들
	TCHAR str[256]; //경로를 불러오는 문자열.
	TCHAR buf[18]; //읽기용 버퍼.
	TCHAR* pBuf; //변환용 포인터
	DWORD dwRead; //읽은 양. 이걸로 어디까지 읽을 지 판별.
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

//몬스터 생성
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
			case 1: //새끼 오징어
				makeLCF(pStage->start,pStage->move_type);
				StageData[now_stage].Delete(i);
				break;
			case 2: //불가사리
				makeSF(pStage->start,pStage->move_type);
				StageData[now_stage].Delete(i);
				break;
			case 3: // (일단은) 거대 오징어 - 1스테이지 보스
				makeBCF(pStage->start);
				StageData[now_stage].Delete(i);
				break;
			case 4: // 동갈치
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