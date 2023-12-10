#pragma once
#include "Common.h"
#include "StateMessage.h"

class Monster
{
public:
	Monster(int SerialNum);

	virtual void Update(float ElaspedTime) = 0;
	virtual bool IsDead(int Damage);

	RECT GetBoundingBox();
	virtual bool GetDamageAndIsDead(int Damage, int StunDamage, int Destuction, int NamedDamage, int Type);

public:
	int GetMaxHp()			{ return m_iMaxHp; }
	int GetCurrentHp()		{ return m_iCurrentHp; }
	int GetDamage()			{ return m_iDamage; }
	int GetExperi()			{ return m_iExperi; }
	int GetSpeed()			{ return m_iSpeed; }
	int GetSerialNum()		{ return m_iSerialNum; }

	bool GetCanAttack()		{ return m_bCanAttack; }
	bool GetChangedState()	{ return m_bChangedState; }
	float GetAttackTimer()	{ return m_fAttackTimer; }

	FPOINT GetLocation()	{ return m_Location; }
	POINT GetSize()			{ return m_Size; };

	MonsterType GetMonsterType() { return MonsterType::END; };

	void SetMaxHp(int hp)				{ m_iMaxHp = hp; }
	void SetCurrentHp(int hp)			{ m_iCurrentHp = hp; }
	void SetDamage(int damage)			{ m_iDamage = damage; }
	void SetExperi(int exp)				{ m_iExperi = exp; }
	void SetSpeed(int speed)			{ m_iSpeed = speed; }

	void SetCanAttack(bool attack)		{ m_bCanAttack = attack; }
	void SetChangedState(bool changed)	{ m_bChangedState = changed; }

	void SetLocation(FPOINT Location)	{ m_Location = Location; }
	void SetSize(POINT Size)			{ m_Size = Size; }

	void MinusElapsedTime(float time)	{ m_fAttackTimer -= time; }
	void InitAttackCoolTime()			{ m_fAttackTimer = m_fAttackCoolTime; }
protected:
	BYTE	m_iSerialNum;

	int		m_iMaxHp;
	int		m_iCurrentHp;

	int		m_iDamage;
	int		m_iExperi;
	int		m_iSpeed;

	bool	m_bCanAttack;
	bool	m_bChangedState;

	float	m_fAttackTimer;
	float	m_fAttackCoolTime;

	FPOINT	m_Location;
	POINT	m_Size;
};

