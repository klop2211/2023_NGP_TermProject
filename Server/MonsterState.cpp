#include "MonsterState.h"
#include "Monster.h"

#include "StateMessage.h"

MonsterMoveState* MonsterMoveState::Instance()
{
	static MonsterMoveState instance;
	return &instance;
}

void MonsterMoveState::Enter(Monster* monster)
{
	std::cout << typeid(monster).name() << "ÀÇ " << monster->GetSerialNum() << "¹ø °´Ã¼: Move ENTER" << std::endl;
}

void MonsterMoveState::Execute(Monster* monster, float ElapsedTime)
{
	// ÀÌµ¿
	int NewLocation = monster->GetLocation().x + monster->GetSpeed() * 20 * ElapsedTime;
	monster->SetLocation(FPOINT(NewLocation, 0));
}

void MonsterMoveState::Exit(Monster* monster)
{
	std::cout << typeid(monster).name() << "ÀÇ " << monster->GetSerialNum() << "¹ø °´Ã¼: Move EXIT" << std::endl;
}

MonsterAttackState* MonsterAttackState::Instance()
{
	static MonsterAttackState instance;
	return &instance;
}

void MonsterAttackState::Enter(Monster* monster)
{
	std::cout << typeid(monster).name() << "ÀÇ " << monster->GetSerialNum() << "¹ø °´Ã¼: Attack ENTER" << std::endl;
}

void MonsterAttackState::Execute(Monster* monster, float ElapsedTime)
{
	monster->MinusElapsedTime(ElapsedTime);
	if (monster->GetAttackTimer() < 0.f)
	{
		monster->SetCanAttack(true);
		monster->InitAttackCoolTime();
	}
}

void MonsterAttackState::Exit(Monster* monster)
{
	std::cout << typeid(monster).name() << "ÀÇ " << monster->GetSerialNum() << "¹ø °´Ã¼: Attack EXIT" << std::endl;
}
