#pragma once
#include "Monster.h"

class CommonMonster : public Monster
{
public:
	CommonMonster(int SN);

	void Update(float) = 0;

protected:
	class MonsterState* m_pMonsterState;
};

