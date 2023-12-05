#include "MonsterState.h"
#include "Monster.h"
#include "Papyrus.h"
#include "Random.h"

#include "StateMessage.h"

MonsterMoveState* MonsterMoveState::Instance()
{
	static MonsterMoveState instance;
	return &instance;
}

void MonsterMoveState::Execute(Monster* monster, float ElapsedTime)
{
	// 이동
	int NewLocation = monster->GetLocation().x + monster->GetSpeed() * 20 * ElapsedTime;
	monster->SetLocation(FPOINT(NewLocation, 0));
}

MonsterAttackState* MonsterAttackState::Instance()
{
	static MonsterAttackState instance;
	return &instance;
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

//=======================================Papyrus========================================
BossMoveState* BossMoveState::Instance()
{
	static BossMoveState instance;
	return &instance;
}

void BossMoveState::Execute(Papyrus* papyrus, float ElapsedTime)
{
	// 이동
	int NewLocation = papyrus->GetLocation().x + papyrus->GetSpeed() * 20 * ElapsedTime;
	papyrus->SetLocation(FPOINT(NewLocation, 0));

	papyrus->MinusRemainTimer(ElapsedTime);
	if (papyrus->GetRemainTimer() < 0.f)
	{
		if (papyrus->GetBreaked())
		{
			if (Random::GetFRandom() > 0.5)
			{
				papyrus->ChangeState(BossPatternType::BPattern1);
			}
			else
			{
				papyrus->ChangeState(BossPatternType::BPattern2);
			}
		}
		else
		{
			papyrus->ChangeState(BossPatternType::UBPattern);
		}
	}
}

BossPatternType BossMoveState::GetStateType()
{
	return BossPatternType::Move;
}

BossUnBreakPatternState* BossUnBreakPatternState::Instance()
{
	static BossUnBreakPatternState instance;
	return &instance;
}

void BossUnBreakPatternState::Execute(Papyrus* papyrus, float ElapsedTime)
{
	papyrus->MinusRemainTimer(ElapsedTime);
	if (papyrus->GetRemainTimer() < 0.f)
	{
		papyrus->ChangeState(BossPatternType::Move);
	}
}

BossPatternType BossUnBreakPatternState::GetStateType()
{
	return BossPatternType::UBPattern;
}

BossBreakPattern1State* BossBreakPattern1State::Instance()
{
	static BossBreakPattern1State instance;
	return &instance;
}

void BossBreakPattern1State::Execute(Papyrus* papyrus, float ElapsedTime)
{
	papyrus->MinusRemainTimer(ElapsedTime);
	if (papyrus->GetRemainTimer() < 0.f)
	{
		papyrus->ChangeState(BossPatternType::Move);
	}
}

BossPatternType BossBreakPattern1State::GetStateType()
{
	return BossPatternType::BPattern1;
}

BossBreakPattern2State* BossBreakPattern2State::Instance()
{
	static BossBreakPattern2State instance;
	return &instance;
}

void BossBreakPattern2State::Execute(Papyrus* papyrus, float ElapsedTime)
{
	papyrus->MinusRemainTimer(ElapsedTime);
	if (papyrus->GetRemainTimer() < 0.f)
	{
		papyrus->ChangeState(BossPatternType::Move);
	}
}

BossPatternType BossBreakPattern2State::GetStateType()
{
	return BossPatternType::BPattern2;
}

BossCantMoveState* BossCantMoveState::Instance()
{
	static BossCantMoveState instance;
	return &instance;
}

void BossCantMoveState::Execute(Papyrus* papyrus, float ElapsedTime)
{
	papyrus->MinusRemainTimer(ElapsedTime);
	if (papyrus->GetRemainTimer() < 0.f)
	{
		papyrus->ChangeState(BossPatternType::Move);
	}
}

BossPatternType BossCantMoveState::GetStateType()
{
	return BossPatternType::CantMove;
}
