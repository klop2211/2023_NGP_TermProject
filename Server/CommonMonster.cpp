#include "CommonMonster.h"
#include "MonsterState.h"

CommonMonster::CommonMonster(int SN) : Monster(SN)
{
	m_pMonsterState = MonsterMoveState::Instance();
}

void CommonMonster::ChangeState(MonsterState* pNewState)
{
	m_pMonsterState->Exit(this);

	m_pMonsterState = pNewState;

	m_pMonsterState->Enter(this);
}