#include "CommonMonster.h"
#include "MonsterState.h"

CommonMonster::CommonMonster(int SN) : Monster(SN)
{
	m_pMonsterState = MonsterMoveState::Instance();
}

void CommonMonster::ChangeState(MonsterState* pNewState)
{
	m_bChangedState = true;

	m_pMonsterState->Exit(this);

	m_pMonsterState = pNewState;

	m_pMonsterState->Enter(this);
}

MonsterStateType CommonMonster::GetStateType()
{
	return m_pMonsterState->GetStateType();
}
