#pragma once
class Wolf : public _Object {
public:
	WolfStatus status;
	Status st;
	bool canDie, isBoss;
	int damage, experi, money;

	Wolf() {
		//start = {0,1}
		size = { 86 * 2, 58 * 2 };
		offset = { 86, 58 };
		hitBox = { WINWIDTH - 200, 634 - size.y, WINWIDTH + size.x - 200, 634 };
		img = &wolfImg;
		count = 0, wait = 0;
		status = Wolf_Move;
		speed = 6;
		hp = 20;
		maxHp = 20;
		damage = 20, experi = 20, money = 3, isBoss = false;
	}

	void draw() {
		int frame;
		HBRUSH hBrush, oldBrush;

		switch (status)
		{
		case Wolf_Move:
			frame = 6;
			break;
		case Wolf_Dead:
			frame = 8;
			break;
		case Wolf_Attact:
			frame = 10;
			break;
		case Wolf_Hit:
			frame = 6;
			break;
		default:
			frame = 1;
			break;
		}

		if(status != Wolf_Die)
			img->Draw(memdc, hitBox.left, hitBox.top, size.x, size.y,
				0 + offset.x * (count % frame), 1 + offset.y * (status), offset.x - 2, offset.y - 2);
		else
			img->AlphaBlend(memdc, hitBox.left, hitBox.top, size.x, size.y,
				0 + offset.x * (7), 1 + offset.y * (1), offset.x - 2, offset.y - 2, 255 - count, AC_SRC_OVER);

		hBrush = CreateSolidBrush(RGB(255, 64, 64));
		oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
		Rectangle(memdc, hitBox.left + 20, hitBox.bottom, hitBox.left + 20 + ((hitBox.right - hitBox.left - 20) * hp / maxHp), hitBox.bottom + 10);
		SelectObject(memdc, oldBrush); DeleteObject(hBrush);
	}

	void update() {
		if (++wait % 3 == 0) {
			count++;
			if (st == Ice_s) {
				count--;
				if (wait > 120) {
					status = Wolf_Move;
					st = NULL_S;
				}
			}
			else
			switch (status)
			{
			case Wolf_Move:
				//hit(1);
				if (st == Fire_s) {
					if (wait % 5 == 0)
						hit(1);					
					if (wait > 120) {
						status = Wolf_Move;
						st = NULL_S;
					}
				}
				hitBox.left -= speed;
				hitBox.right -= speed;
				if (hitBox.left < CASTLEXPOINT - 50) {
					status = Wolf_Attact;
					count = 0, wait = 0;
				}
				break;
			case Wolf_Dead:
				if (count == 8) {
					status = Wolf_Die;
					count = 0, wait = 0;
				}
				break;
			case Wolf_Attact:
				if (st == Fire_s) {
					if(wait % 5 == 0)
						hit(1);
					if (wait > 120) {
						status = Wolf_Move;
						st = NULL_S;
					}
				}
				if (count % 10 == 6) {
					hitCastle(damage);
				}
				break;
			case Wolf_Hit:
				if (count == 6) {
					status = Wolf_Move;
					count = 0, wait = 0;
				}
				break;
			case Wolf_Die:
				count += 6;
				if (count > 249) {
					canDie = true;

				}
				break;
			default:
				break;
			}
		}
	}

	void hit(int att) {
		status = Wolf_Hit;
		count = 0, wait = 0;
		hp -= att;
		if (hp <= 0) {
			hp = 0;
			status = Wolf_Dead;
			getExp(experi);
			getMoney(getRand(3) + money);
			count = 0, wait = 0;
		}
	}
};
Wolf* wolf[MAXWOLF] = {nullptr, };