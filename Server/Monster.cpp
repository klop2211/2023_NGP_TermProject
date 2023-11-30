#include "Monster.h"
#include "MonsterState.h"

Monster::Monster(int SerialNum) :
	m_iSerialNum(SerialNum),
	m_bCanAttack(false),
	m_fAttackTimer(0.f)
{
}

bool Monster::IsDead(int Damage)
{
	m_iMaxHp -= Damage;
	if (m_iMaxHp <= 0)
	{
		return true;
	}
	return false;
}

void Monster::ChangeState(MonsterState* pNewState)
{
	m_State->Exit(this);

	m_State = pNewState;

	m_State->Enter(this);
}

RECT Monster::GetBoundingBox()
{
	RECT ReturnValue;
	ReturnValue.left = (int)m_Location.x;
	ReturnValue.top = (int)m_Location.y;
	ReturnValue.right = (int)m_Location.x + m_Size.x;
	ReturnValue.bottom = (int)m_Location.y + m_Size.y;

	return ReturnValue;
}
