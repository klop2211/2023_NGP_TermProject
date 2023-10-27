#pragma once
class Bat : public _Object {
public:
	BatStatus status;
	Status st;
	bool canDie, isBoss;
	int damage, experi, money;

	Bat() {
		size = { 67*2,49*2 };
		offset = { 67,49 };
		hitBox = { WINWIDTH - 200, 400 - size.y, WINWIDTH - 200 + size.x, 400 };
		img = &batImg;
		count = 0, wait = 0, speed = 5;
		status = Bat_Move;
		maxHp = 10;
		hp = 10;
		damage = 15, experi = 15, money = 5, isBoss = false;

		canDie = false;
	}

	void draw() {
		int frame = 6;
		HBRUSH hBrush, oldBrush;

		if(status != Bat_Die)
			img->Draw(memdc, hitBox.left, hitBox.top, size.x, size.y,
				0 + offset.x * (count % frame), 0 + offset.y * status, offset.x - 2, offset.y - 2);
		else
			img->AlphaBlend(memdc, hitBox.left, hitBox.top, size.x, size.y,
				0 + offset.x * 5, 0 + offset.y * 1, offset.x - 2, offset.y - 2, 255 - count, AC_SRC_OVER);

		hBrush = CreateSolidBrush(RGB(255, 64, 64));
		oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
		Rectangle(memdc, hitBox.left + 20, hitBox.bottom, hitBox.left + 20 + ((hitBox.right - hitBox.left - 20) * hp / maxHp), hitBox.bottom + 10);
		SelectObject(memdc, oldBrush); DeleteObject(hBrush);
	}
	
	void update() {
		if (++wait % 5 == 0) {
			count++;
			
			switch (status)
			{
			case Bat_Move:
				//hit(1);
				hitBox.left -= speed;
				hitBox.right -= speed;
				if (hitBox.left < CASTLEXPOINT - 50) {
					status = Bat_Attact;
					count = 0, wait = 0;
				}
				break;
			case Bat_Dead:
				hitBox.top += 15;
				hitBox.bottom += 15;
				if (count == 5)
					--count;
				if (hitBox.bottom > GROUNDYPOINT) {
					hitBox.bottom = GROUNDYPOINT;
					hitBox.top = GROUNDYPOINT - size.y;
					status = Bat_Die;
					count = 0, wait = 0;
				}
				break;
			case Bat_Attact:
				if (count % 6 == 3) {
					hitCastle(damage);
				}
				break;
			case Bat_Hit:
				if (count == 6) {
					status = Bat_Move;
					count = 0, wait = 0;
				}
				break;
			case Bat_Die:
				count += 10;
				if (count > 245)
					canDie = true;
				break;
			default:
				break;
			}
		}
	}

	void hit(int att) {
		status = Bat_Hit;
		count = 0, wait = 0;
		hp -= att;
		if (hp <= 0) {
			hp = 0;
			status = Bat_Dead;
			getMoney(getRand(3) + money);
			getExp(experi);
			count = 0, wait = 0;
		}
	}
};

Bat* bat[MAXBAT] = { nullptr, };