#pragma once

#include "CPlayer.h"
#include "CTitle.h"
#include "CScore.h"
#include "CUpgrade.h"
#include "CItemSlot.h"
#include <time.h>

#define SCREEN_X 800
#define SCREEN_Y 600
#define randomize() srand((unsigned)time(NULL))
#define random(n) (rand() % (n))

extern HINSTANCE g_hInst;
extern HWND hWndMain;
extern CPlayer player;
extern CTitle title;
extern CScore score;
extern CUpgrade upgrade;
extern CItemSlot item_slot;