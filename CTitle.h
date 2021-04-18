#pragma once

#include "CAnimation.h"

#define BUTTON_START 350 //첫 버튼이 놓아지는 위치.(y좌표)
#define BUTTON_SPLIT 50  //버튼간 간격.
#define BUTTON_NUM 2 //버튼 개수.

// 아이템 번호 0 = 게임 시작, 1 = 게임 종료.
// 클래스로 만들라캤는데 못 만들겠다. 그냥 CTitle 내에서 구조지향적으로 처리...

class CTitle
{
private:
	CAnimation graphic;
	CAnimation story,exit; // 각 버튼 그래픽.
	CAnimation cursor; //커서 그래픽.
	int cur_pos; //현재 가리키고 있는 버튼.
	void SelectButton(); // 버튼 선택 함수

public:
	CTitle();
	bool MouseMove(WPARAM wParam, LPARAM lParam);     // 마우스 위치에 따라 커서 위치 변경
	void MouseSelect(WPARAM wParam, LPARAM lParam);   // 마우스 클릭을 통한 버튼 선택.
	void Draw(HDC hdc);
	void TitleProcesser(); // 타이틀 관련 모든 처리 담당.
};