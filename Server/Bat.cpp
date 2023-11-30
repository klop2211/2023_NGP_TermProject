#include "Bat.h"
#include "MonsterState.h"

Bat::Bat(int SN) : CommonMonster(SN)
{
	m_iSpeed = 5;
	m_iMaxHp = 10;
	m_iCurrentHp = 10;
	m_iDamage = 15;
	m_iExperi = 15;
}

void Bat::Update(float ElapsedTime)
{
	m_State->Execute(this, ElapsedTime);
}

