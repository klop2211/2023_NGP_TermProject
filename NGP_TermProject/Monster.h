#pragma once

#include "Object.h"
#include "../Server/StateMessage.h"

class CastleInteraction;

enum class MonsterState : BYTE { Move, Dead, Attack, Hit, Die };
enum class StatusEffect : BYTE { Ice_s = 1, Fire_s, NULL_S };

class Monster : public Object
{
public:
	Monster() {}
	~Monster() {}

	virtual void Update(float elapsed) override = 0;
	virtual bool Hit(int damage) { return 0; };

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

	void SetCurrentHp(int Hp) { m_iCurrentHp = Hp; }
	void SetLocation(POINT p) { m_Location.x = p.x; m_Location.y = p.y; }

	virtual CImage GetImg() const = 0;

	void SetCastleInteraction(CastleInteraction* castleIntercation);

protected:
	bool m_bCanDie;
	int m_iDamage, m_iExperi; // , m_iMoney;
	int m_iCurrentHp, m_iMaxHp, m_iSpeed;

	int m_iCount;
	float m_fWait;

	int m_iFrame;

	// int m_iSize;

	// 상태이상
	StatusEffect m_eSE;

	// 몬스터와 성의 공격 상호작용
	CastleInteraction* m_pCastleInteraction;
};