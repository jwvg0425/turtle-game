#pragma once
#define TITLE 0
#define STAGE 1
#define GAME_OVER 2
#define UPGRADE 3
#define STAGE_CLEAR 4
extern int now_frame;

void GameProcesser();
extern int mode;
void StageClear();
void GameOver();
void MakeEffect(int type,int x, int y);