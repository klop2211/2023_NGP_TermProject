#pragma once
#include "Monster.h"

class Bat : public Monster
{
public:
	Bat(CImage* WolfImg) {}
	~Bat() {}

	virtual void Update(float elapsed) override;
	virtual bool Hit(int damage);

	//Render
public:
	virtual void Draw(HDC& memdc);
	virtual void ImgDraw(HDC& memdc);
	virtual void HpDraw(HDC& memdc);

	//Gettor, Settor
public:

private:
	MonsterStatus status;
};

