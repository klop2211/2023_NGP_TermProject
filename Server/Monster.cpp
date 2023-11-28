#include "Monster.h"

bool Monster::IsDead(int Damage)
{
	m_iHp -= Damage;
	if (m_iHp <= 0)
	{
		return true;
	}
	return false;
}
