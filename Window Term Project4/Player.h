#pragma once
#include "Object.h"

enum PlayerState { Move, Stay, Skill, Run, Stun
};

class Player : public Object
{
public:
	Player();
	~Player();
	//void SetSpeed(const int& x, const int& y) { Object::SetSpeed(x, y); }
	//void SetImage(const TCHAR str[]) { Object::SetImage(str); }
	/*void SetRect(const int& left, const int& top, const int& right, const int& bottom) {
		Object::SetRect(left, top, right, bottom);
	}
	void SetDelay(const int& num) {
		Object::SetDelay(num);
	}*/
	void SetState(const int& num);
	void SetRuncount(const int& num) { run_count = num; }
	void SetStuncount(const int& num) { stun_count = num; }
	int GetStuncount() { return stun_count; }
	POINT GetPoint() { return { (rect.left + rect.right) / 2 , (rect.top + rect.bottom) / 2 }; }
	//int GetIFrame_Max() { return Object::GetFrame_Max(); }
	//int GetDelay() { return Object::GetDelay(); }
	//int GetDirection() { return Object::GetDirection(); }
	int GetState() { return state; }
	int GetRuncount() { return run_count; }
	//void Move(const int& bottom) { Object::Move(bottom); }
	//void Draw(HDC memdc, const int& num) { Object::Draw(memdc, num); }
	//void Draw(HDC memdc) { Object::Draw(memdc); }
private:
	int state, run_count, stun_count;
};

Player::Player()
{
	state = Stay;
	run_count = 0;
}

Player::~Player()
{
}

void Player::SetState(const int& num) {
	state = num;
	if (num == Stay) {
		damage = destruction = neutralization = named_damage = seed_damage = 0;
		type = None;
		Delete_Hitlist();
	}
	else if (num == Stun) {
		if (dir == Right) {
			SetImage(L"./\\윈플 텀프 이미지\\창술사_스턴.png");
		}
		else {
			SetImage(L"./\\윈플 텀프 이미지\\창술사_스턴(left).png");

		}
	}
}

Player player;