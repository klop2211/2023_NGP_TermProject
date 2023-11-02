#pragma once
#include "Monster.h"

class Wolf : public Monster
{
public:
	Wolf(CImage* WolfImg) {}
	~Wolf() {}

	virtual void Update(float elapsed) override;
	virtual bool Hit(int damage);

	//Render
public:
	virtual void Draw(HDC& memdc) override;
	virtual void ImgDraw(HDC& memdc);
	virtual void HpDraw(HDC& memdc);

	//Gettor, Settor
public:

private:
	MonsterStatus status;
	//Status st;
};

