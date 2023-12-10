#pragma once
#include "Monster.h"

class MonsterState;

class CommonMonster : public Monster
{
public:
	CommonMonster(int SN);

	virtual void ChangeState(MonsterState* pNewState);
	void Update(float) = 0;

	MonsterStateType GetStateType();

protected:
	MonsterState* m_pMonsterState;
};

