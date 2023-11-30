#include "CommonMonster.h"
#include "MonsterState.h"

CommonMonster::CommonMonster(int SN) : Monster(SN)
{
	m_State = MonsterMoveState::Instance();
}
