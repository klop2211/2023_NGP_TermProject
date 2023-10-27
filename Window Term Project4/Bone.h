#pragma once
class Bone : public _Object {
public:
	bool canDie;
	int num, randValue;
	POINT start;
	bool canDown;

	Bone() {}
	Bone(int num, int x, int y) {
		this->num = num;
		if (num == 0) {
			offset = { 49, 54 };
			start = { 99, 109 };
			size = { offset.x * 4, offset.y * 4 };
			hitBox = { x - size.x, y - size.y, x , y };
			canDown = false;
		}
		else if (num == 1) {
			offset = { 33, 8 };
			start = { 246, 371 };
			randValue = getRand(5) + 5;
			size = { 1, offset.y * randValue };
			hitBox = { x - size.x, y - size.y - 100, x , y - 100 };
			canDown = false;
		}
		else if (num == 2) {
			offset = { 11, 11 };
			start = { 246, 325 };
			size = { offset.x * 3, offset.y * 3 };
			hitBox = { x , y , x + size.x , y + size.y };
			canDown = false;
		}
		img = &papyrusImg;
		count = 0, wait = 0;
		hp = maxHp = 0;

		canDie = false;
	}

	void draw() {
		switch (num)
		{
		case 0:
			img->Draw(memdc, hitBox.left, hitBox.top, size.x, size.y,
				start.x, start.y, offset.x - 1, offset.y - 1);
			break;
		case 1:
			img->Draw(memdc, hitBox.left, hitBox.top, size.x, size.y,
				start.x, start.y, offset.x - 1, offset.y - 1);
			break;
		case 2:
			img->Draw(memdc, hitBox.left, hitBox.top, size.x, size.y,
				start.x + offset.x * (count % 4), start.y, offset.x - 1, offset.y - 1);
			break;
		default:
			break;
		}
	}

	void update() {
		switch (num)
		{
		case 0:
			if (++wait % 2 == 0) {
				if (wait == 50)
					canDie = true;
				else {
					hitBox.left -= 16;
					hitBox.right -= 16;
				}
			}
			break;
		case 1:
			if (++wait % 5 == 0) {
				if (canDown) {
					hitBox.top += 40;
					hitBox.bottom += 40;
					if (hitBox.bottom > GROUNDYPOINT) {
						canDie = true;
					}
				}
				else {
					hitBox.left -= 20;
					size.x += 20;
					if (hitBox.right - hitBox.left > offset.x * randValue * 2) {
						canDown = true;
					}
				}
			}
			break;
		case 2:
			if (++wait % 5 == 0) {
				++count;
				if (canDown) {
					hitBox.top += 40;
					hitBox.bottom += 40;
					if (hitBox.bottom > GROUNDYPOINT) {
						hitBox.bottom = GROUNDYPOINT;
						hitBox.top= GROUNDYPOINT - size.x;
						--count;

						if (wait == 450) {
							canDie = true;
						}
					}
				}
				else {
					hitBox.top -= 70;
					hitBox.bottom -= 70;
					if (hitBox.bottom < 0) {
						int temp = getRand(hitBox.left - 100) + 100;
						count = getRand(4);
						hitBox = { temp,-size.y,temp + size.x,0 };
						canDown = true;
						wait = 0;
					}
				}
			}
			break;
		default:
			break;
		}
	}
};

Bone* bone[2] = { nullptr, };
Bone* miniBone[15] = { nullptr, };