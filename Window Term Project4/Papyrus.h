#pragma once
#include "Player.h"

class Papyrus :public _Object {
public:
	bool breaked, canDown, isBoss;
	int breakCount, knockDown;
	PapyrusStatus status;
	TCHAR name[9], hpStr[10];
	RECT nameRect;
	RECT hpRect;

	Papyrus() {
		//start 1,1
		offset = { 49, 54 };
		size = { offset.x * 5, offset.y * 5 };
		hitBox = { WINWIDTH - 300, 634 - size.y, WINWIDTH + size.x - 300, 634 };
		img = &papyrusImg;
		count = 0, wait = 0, speed = 10;
		status = UP_Move;

		hp =  60;
		maxHp = 60;
		breakCount = 10, breaked = false;
		knockDown = 100, canDown = true, isBoss = true;

		lstrcpy(name, L"파피루스");
		nameRect = { 350 + 134, 0, 1250, 50 + 50 };
		hpRect = { 350 + 134, 50 + 54, 1250 , 50 + 87 };
	}

	void draw() {
		int frame = 1;
		HBRUSH hBrush, oldBrush;
		HFONT hFont, oldFont;

		if(!breaked)
			switch (status)
			{
			case UP_Breaking:
				frame = 8;
				break;
			case UP_Move:
				frame = 4;
				break;
			case UP_Pattern:
				frame = 2;
				break;
			}
		else
			switch(status) {
			case P_Move:
				frame = 4;
				break;
			case P_Down:
				frame = 11;
				break;
			case P_Pattern1:
				frame = 5;
				break;
			case P_Pattern2:
				frame = 5;
				break;
			case P_Die:
				frame = 1;
				break;
			default:
				frame = 1;
				break;
			}
		if(!breaked)
			img->Draw(memdc, hitBox.left, hitBox.top, size.x, size.y,
				1 + offset.x * (count % frame), 1 + offset.y * status, offset.x - 1, offset.y - 1);
		else {
			if (status == P_Die) {
				img->AlphaBlend(memdc, hitBox.left, hitBox.top, size.x, size.y,
					1 + offset.x * 10, 163 + offset.y * 1, offset.x - 1, offset.y - 1, 255 - count, AC_SRC_OVER);
			}
			else{
				img->Draw(memdc, hitBox.left, hitBox.top, size.x, size.y,
					1 + offset.x * (count % frame), 163 + offset.y * status, offset.x - 1, offset.y - 1);
			}
		}

		//보스 체력바 붉은색
		hBrush = CreateSolidBrush(RGB(128, 0, 0));
		oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
		Rectangle(memdc, 350 + 134, 50 + 54, 1250 , 50 + 90);
		SelectObject(memdc, oldBrush); DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
		Rectangle(memdc, 350 + 134, 50 + 54, 350 + 134 + (766 * hp / maxHp), 50 + 90);
		SelectObject(memdc, oldBrush); DeleteObject(hBrush);

		//보스 체력바 통
		bossHpBar.Draw(memdc, 350, 50, 900, 118,
			0, 0, 883, 116);

		SetBkMode(memdc, TRANSPARENT);
		//보스 이름
		hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"바탕체");
		oldFont = (HFONT)SelectObject(memdc, hFont);
		DrawText(memdc, name, lstrlen(name), &nameRect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
		SelectObject(memdc, oldFont); DeleteObject(hFont);

		//보스 체력
		swprintf_s(hpStr, 10, L"%d / %d", hp, maxHp);//HANGEUL_CHARSET
		hFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Papyrus");
		oldFont = (HFONT)SelectObject(memdc, hFont);
		DrawText(memdc, hpStr, lstrlen(hpStr), &hpRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SelectObject(memdc, oldFont); DeleteObject(hFont);

		//무력화 수치
		if (breaked) {
			hBrush = CreateSolidBrush(RGB(163, 73, 164));
			oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
			Rectangle(memdc, nameRect.left + 5, hpRect.bottom, nameRect.left + 5 + ((nameRect.right - nameRect.left + 5 - 40) * knockDown / 100), hpRect.bottom + 5);
		}
	}

	void update() {
		if (++wait % 5 == 0) {
			if(!breaked)
				switch (status)
				{
				case UP_Breaking:
					if (wait % 4) {
						count++;
						if (count == 7){
							status = P_Move;
							wait = count = 0;
							breaked = true;
						}
					}
					break;
				case UP_Move:
				{
					RECT temp, check = { hitBox.left - 100,hitBox.top,hitBox.right - 100,hitBox.bottom };
					if (IntersectRect(&temp, &check, player.GetRect(1))) {
						if (getRand(50) < 1)
							status = UP_Pattern;
					}
					if (wait % 3 == 0) {
						hitBox.left -= 10;
						hitBox.right -= 10;
						count++;
						hit(0, 1, 0);
					}
				}
					break;
				case UP_Pattern:
					if (++count % 20 == 0) {
						for (int i = 0; i < 2; i++)
						{
							if (bone[i] == nullptr) {
								bone[i] = new Bone(0, hitBox.left, hitBox.bottom);
								break;
							}
						}
					}
					break;
				default:
					break;
				}
			else
				switch(status){
				case P_Move:
				{
					RECT temp, check = { hitBox.left - 100,hitBox.top,hitBox.right - 100,hitBox.bottom };
					if (IntersectRect(&temp, &check, player.GetRect(1))) {
						if (getRand(50) < 3) {
							status = P_Pattern1;
							wait = 0, count = 0;
						}
					}
					if (wait % 2 == 0) {
						int randInt = getRand(50);
						if (randInt < 3) {
							status = P_Pattern2;
							wait = 0, count = 0;
						}
						hitBox.left -= 10;
						hitBox.right -= 10;
						count++;
						//hit(0, 0, 60);
					}
				}
					break;
				case P_Down:
					if (canDown) {
						if (++count == 11) {
							--count;
							if (wait > 90) {
								canDown = false;
								wait = 0;
							}
							if (hp <= 0) {
								status = P_Die;
								wait = count = 0;
							}
						}
					}
					else {
						if (--count < 0) {
							status = P_Move;
							knockDown = 100;
							wait = count = 0;
						}
					}
					break;
				case P_Pattern1:
					count++;
					if (wait == 5) {
						for (int i = 0; i < 2; i++)
						{
							if (bone[i] == nullptr) {
								bone[i] = new Bone(1, hitBox.left, hitBox.top);
								break;
							}
						}
					}
					break;
				case P_Pattern2:
					count++;
					if (count % 5 == 4) {
						for (int i = 0; i < 15; i++)
						{
							if (miniBone[i] == nullptr) {
								miniBone[i] = new Bone(2, hitBox.left + 25*5, hitBox.top + 20*5);
								break;
							}
						}
					}
					if (count == 75) {
						status = P_Move;
						wait = count = 0;
					}
					break;
				case P_Die:
					if(count < 245)
						count += 10;
					break;
				default:
					break;
				}
		}
	}

	void hit(int att, int ammorBreak, int knockDown) {
		if (!breaked) {
			int temp = att*0.6;
			if (temp == 0)
				temp = 1;
			hp -= att * 0.6;
			if (hp <= 0) {
				hp = 0;
				status = P_Down;
				breaked = true;
				wait = count = 0;
			}
			breakCount -= ammorBreak;
			if (breakCount <= 0) {
				status = UP_Breaking;
				wait = count = 0;
			}
		}
		else {
			hp -= att;
			if (hp <= 0) {
				hp = 0;
				status = P_Down;
				wait = count = 0;
			}
			this->knockDown -= knockDown;
			if (this->knockDown <= 0) {
				status = P_Down;
				wait = count = 0;
			}
		}
	}

};
Papyrus papyrus;