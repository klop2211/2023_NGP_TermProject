#pragma once
#include "Common.h"

class MonsterState;

class Monster
{
public:
	Monster(int SerialNum);

	virtual void Update(float ElaspedTime) = 0;
	virtual bool IsDead(int Damage);

	virtual void ChangeState(MonsterState* pNewState);

	RECT GetBoundingBox();

public:
	int GetMaxHp()			{ return m_iMaxHp; }
	int GetCurrentHp()		{ return m_iCurrentHp; }
	int GetDamage()			{ return m_iDamage; }
	int GetExperi()			{ return m_iExperi; }
	int GetSpeed()			{ return m_iSpeed; }
	int GetSerialNum()		{ return m_iSerialNum; }

	bool GetCanAttack()		{ return m_bCanAttack; }
	float GetAttackTimer()	{ return m_fAttackTimer; }

	FPOINT GetLocation()	{ return m_Location; }
	POINT GetSize()			{ return m_Size; };

	void SetMaxHp(int hp)				{ m_iMaxHp = hp; }
	void SetCurrentHp(int hp)			{ m_iCurrentHp = hp; }
	void SetDamage(int damage)			{ m_iDamage = damage; }
	void SetExperi(int exp)				{ m_iExperi = exp; }
	void SetSpeed(int speed)			{ m_iSpeed = speed; }
	void SetCanAttack(bool attack)		{ m_bCanAttack = attack; }

	void SetLocation(FPOINT Location)	{ m_Location = Location; }
	void SetSize(POINT Size)			{ m_Size = Size; }

	void AddElapsedTime(float time)		{ m_fAttackTimer += time; }

protected:
	MonsterState* m_State;
	BYTE	m_iSerialNum;

	int		m_iMaxHp;
	int		m_iCurrentHp;

	int		m_iDamage;
	int		m_iExperi;
	int		m_iSpeed;

	bool	m_bCanAttack;
	float	m_fAttackTimer;
	float	m_fAttackCoolTime;

	FPOINT	m_Location;
	POINT	m_Size;
};

