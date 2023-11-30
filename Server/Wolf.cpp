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

	m_Size = { 67 * 2,49 * 2 };
	m_Location = { (float)(CLIENTWINWIDTH - 200),  (float)(CLIENTWINWIDTH - 200 + m_Size.x) };
}

void Wolf::Update(float ElapsedTime)
{
	m_State->Execute(this, ElapsedTime);
}
