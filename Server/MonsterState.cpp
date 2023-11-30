#include "MonsterState.h"
#include "Monster.h"

MonsterMoveState* MonsterMoveState::Instance()
{
	static MonsterMoveState instance;
	return &instance;
}

void MonsterMoveState::Enter(Monster* monster)
{
	std::cout << typeid(monster).name() << "의 " << monster->GetSerialNum() << "번 객체: Move ENTER" << std::endl;
}

void MonsterMoveState::Execute(Monster* monster, float ElapsedTime)
{
	// 이동
	int NewLocation = monster->GetLocation().x + monster->GetSpeed() * 20 * ElapsedTime;
	monster->SetLocation(FPOINT(NewLocation, 0));
}

void MonsterMoveState::Exit(Monster* monster)
{
	std::cout << typeid(monster).name() << "의 " << monster->GetSerialNum() << "번 객체: Move EXIT" << std::endl;
}

MonsterAttackState* MonsterAttackState::Instance()
{
	static MonsterAttackState instance;
	return &instance;
}

void MonsterAttackState::Enter(Monster* monster)
{
	std::cout << typeid(monster).name() << "의 " << monster->GetSerialNum() << "번 객체: Attack ENTER" << std::endl;
}

void MonsterAttackState::Execute(Monster* monster, float ElapsedTime)
{
	// TODO: 공격 메세지
}

void MonsterAttackState::Exit(Monster* monster)
{
	std::cout << typeid(monster).name() << "의 " << monster->GetSerialNum() << "번 객체: Attack EXIT" << std::endl;
}
