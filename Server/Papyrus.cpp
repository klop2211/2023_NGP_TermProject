#include "Common.h"

#include "Papyrus.h"
#include "MonsterState.h"

Papyrus::Papyrus()
	:Monster(0)
{
	m_iCurrentHp = 60;
	m_iMaxHp = 60;
	m_iBreakCount = 10, m_bBreaked = false;
	m_iKnockDown = 100, m_bCanDown = true;
	m_fBreakTimer = 0.f;


}

Papyrus::~Papyrus()
{
}
