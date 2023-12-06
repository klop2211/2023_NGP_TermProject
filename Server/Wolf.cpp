#include "Wolf.h"
#include "MonsterState.h"

Wolf::Wolf(int SN) : CommonMonster(SN)
{
	m_iSpeed = 6;
	m_iMaxHp = 20;
	m_iCurrentHp = 20;
	m_iDamage = 20;
	m_iExperi = 20;
	m_fAttackCoolTime = 3.f;

	m_Size = { 86 * 2, 58 * 2 };
	m_Location = { (float)(CLIENTWINWIDTH),  (float)(634 - m_Size.y) };
}

void Wolf::Update(float ElapsedTime)
{
	m_pMonsterState->Execute(this, ElapsedTime);
}
