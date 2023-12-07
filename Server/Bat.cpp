#include "Bat.h"
#include "MonsterState.h"

Bat::Bat(int SN) : CommonMonster(SN)
{
	m_iSpeed = 5;
	m_iMaxHp = 10;
	m_iCurrentHp = 10;
	m_iDamage = 15;
	m_iExperi = 15;
	m_fAttackCoolTime = 3.f;

	m_Size = { 67 * 2,49 * 2 };
	m_Location = { (float)(CLIENTWINWIDTH),  (float)(400 - m_Size.y) };
}

void Bat::Update(float ElapsedTime)
{
	m_pMonsterState->Execute(this, ElapsedTime);
}

