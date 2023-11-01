#pragma once

#include "Object.h"

class Monster : public Object
{
public:
	Monster() {}
	~Monster() {}

	virtual void Update(float elapsed) override = 0;
	virtual bool Hit(int damage) = 0;

	//Render
public:
	virtual void Draw(HDC& memdc) override = 0;
	virtual void ImgDraw(HDC& memdc) = 0;
	virtual void HpDraw(HDC& memdc) = 0;

	//Gettor, Settor
public:
	bool GetCanDie()		{ return m_bCanDie; }
	int  GetDamage()		{ return m_iDamage; }
	int  GetExperi()		{ return m_iExperi; }
	//int  GetMoney()		{ return m_iMoney; }
	int  GetCurrentHp()		{ return m_iCurrentHp; }
	int  GetMaxHp()			{ return m_iMaxHp; }
	int  GetSpeed()			{ return m_iSpeed; }

private:
	bool m_bCanDie;
	int m_iDamage, m_iExperi; // , m_iMoney;
	int m_iCurrentHp, m_iMaxHp, m_iSpeed;
};

