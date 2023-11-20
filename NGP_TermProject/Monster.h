#pragma once

#include "Object.h"

class Monster : public Object
{
public:
	Monster() : m_iSize(1) {}
	~Monster() {}

	virtual void Update(float elapsed) override = 0;
	virtual bool Hit(int damage) {};

	void SyncLocationAtRect();
	void MoveXY(float x, float y, float elapsed);

	//Render
public:
	virtual void Draw(HDC& memdc) = 0;
	virtual void ImgDraw(HDC& memdc) {};
	virtual void HpDraw(HDC& memdc) {};

	//Gettor, Settor
public:
	bool GetCanDie()		{ return m_bCanDie; }
	int  GetDamage()		{ return m_iDamage; }
	int  GetExperi()		{ return m_iExperi; }
	//int  GetMoney()		{ return m_iMoney; }
	int  GetCurrentHp()		{ return m_iCurrentHp; }
	int  GetMaxHp()			{ return m_iMaxHp; }
	int  GetSpeed()			{ return m_iSpeed; }

	virtual CImage GetImg() const {};

protected:
	bool m_bCanDie;
	int m_iDamage, m_iExperi; // , m_iMoney;
	int m_iCurrentHp, m_iMaxHp, m_iSpeed;

	int m_iCount;
	float m_fWait;

	int m_iSize;

	// 상태이상
	StatusEffect m_eSE;
};


enum class MonsterStatus { Move, Dead, Attack, Hit, Die };
enum class StatusEffect { Ice_s = 1, Fire_s, NULL_S };