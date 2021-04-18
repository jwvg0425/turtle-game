#pragma once

#include "CAnimation.h"

#define BUTTON_START 350 //ù ��ư�� �������� ��ġ.(y��ǥ)
#define BUTTON_SPLIT 50  //��ư�� ����.
#define BUTTON_NUM 2 //��ư ����.

// ������ ��ȣ 0 = ���� ����, 1 = ���� ����.
// Ŭ������ �����ĺ�µ� �� ����ڴ�. �׳� CTitle ������ �������������� ó��...

class CTitle
{
private:
	CAnimation graphic;
	CAnimation story,exit; // �� ��ư �׷���.
	CAnimation cursor; //Ŀ�� �׷���.
	int cur_pos; //���� ����Ű�� �ִ� ��ư.
	void SelectButton(); // ��ư ���� �Լ�

public:
	CTitle();
	bool MouseMove(WPARAM wParam, LPARAM lParam);     // ���콺 ��ġ�� ���� Ŀ�� ��ġ ����
	void MouseSelect(WPARAM wParam, LPARAM lParam);   // ���콺 Ŭ���� ���� ��ư ����.
	void Draw(HDC hdc);
	void TitleProcesser(); // Ÿ��Ʋ ���� ��� ó�� ���.
};