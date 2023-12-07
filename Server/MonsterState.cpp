#include "MonsterState.h"
#include "Monster.h"
#include "Papyrus.h"
#include "Random.h"
#include "Bone.h"

MonsterMoveState* MonsterMoveState::Instance()
{
	static MonsterMoveState instance;
	return &instance;
}

void MonsterMoveState::Execute(Monster* monster, float ElapsedTime)
{
	// 이동
	int NewLocation = monster->GetLocation().x - monster->GetSpeed() * 20 * ElapsedTime;
	monster->SetLocation(FPOINT(NewLocation, monster->GetLocation().y));
}

MonsterStateType MonsterMoveState::GetStateType()
{
	return MonsterStateType::Move;
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

MonsterStateType MonsterAttackState::GetStateType()
{
	return MonsterStateType::Attack;
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
	int NewLocation = papyrus->GetLocation().x - papyrus->GetSpeed() * 20 * ElapsedTime;
	papyrus->SetLocation(FPOINT(NewLocation, papyrus->GetLocation().y));

	papyrus->MinusRemainTimer(ElapsedTime);
	if (papyrus->GetRemainTimer() < 0.f)
	{
		if (papyrus->GetBreaked())
		{
			if (Random::GetFRandom() > 0.5)
			{
				papyrus->ChangeState(BossStateType::BPattern1);
			}
			else
			{
				papyrus->ChangeState(BossStateType::BPattern2);
			}
		}
		else
		{
			papyrus->ChangeState(BossStateType::UBPattern);
		}
	}
}

BossStateType BossMoveState::GetStateType()
{
	return BossStateType::Move;
}

BossUnBreakPatternState* BossUnBreakPatternState::Instance()
{
	static BossUnBreakPatternState instance;
	return &instance;
}

void BossUnBreakPatternState::Enter(Papyrus* papyrus)
{
	papyrus->MakeBone(Bone::BoneType::UnBreak);
}

void BossUnBreakPatternState::Execute(Papyrus* papyrus, float ElapsedTime)
{
	papyrus->MinusRemainTimer(ElapsedTime);
	if (papyrus->GetRemainTimer() < 0.f)
	{
		papyrus->ChangeState(BossStateType::Move);
	}
}

BossStateType BossUnBreakPatternState::GetStateType()
{
	return BossStateType::UBPattern;
}

BossBreakPattern1State* BossBreakPattern1State::Instance()
{
	static BossBreakPattern1State instance;
	return &instance;
}

void BossBreakPattern1State::Enter(Papyrus* papyrus)
{
	papyrus->MakeBone(Bone::BoneType::Break1);
}

void BossBreakPattern1State::Execute(Papyrus* papyrus, float ElapsedTime)
{
	papyrus->MinusRemainTimer(ElapsedTime);
	if (papyrus->GetRemainTimer() < 0.f)
	{
		papyrus->ChangeState(BossStateType::Move);
	}
}

BossStateType BossBreakPattern1State::GetStateType()
{
	return BossStateType::BPattern1;
}

BossBreakPattern2State* BossBreakPattern2State::Instance()
{
	static BossBreakPattern2State instance;
	return &instance;
}

void BossBreakPattern2State::Enter(Papyrus* papyrus)
{
}

void BossBreakPattern2State::Execute(Papyrus* papyrus, float ElapsedTime)
{
	static int Count = 0;
	static float Timer = 0.f;
	
	Timer += ElapsedTime;
	if (Timer > 0.25f)
	{
		Timer = 0.f;
		papyrus->MakeMiniBone(Count++);
		if (Count >= 15)
		{
			Count = 0;
			papyrus->ChangeState(BossStateType::Move);
		}
	}
}

BossStateType BossBreakPattern2State::GetStateType()
{
	return BossStateType::BPattern2;
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
		papyrus->ChangeState(BossStateType::Move);
	}
}

BossStateType BossCantMoveState::GetStateType()
{
	return BossStateType::CantMove;
}

BossBreakingState* BossBreakingState::Instance()
{
	static BossBreakingState instance;
	return &instance;
}

void BossBreakingState::Execute(Papyrus* papyrus, float ElapsedTime)
{
	papyrus->MinusRemainTimer(ElapsedTime);
	if (papyrus->GetRemainTimer() < 0.f)
	{
		papyrus->ChangeState(BossStateType::Move);
	}
}

BossStateType BossBreakingState::GetStateType()
{
	return BossStateType::Breaking;
}

BossStunningState* BossStunningState::Instance()
{
	static BossStunningState instance;
	return &instance;
}

void BossStunningState::Execute(Papyrus* papyrus, float ElapsedTime)
{
	papyrus->MinusRemainTimer(ElapsedTime);
	if (papyrus->GetRemainTimer() < 0.f)
	{
		papyrus->ChangeState(BossStateType::Move);
	}
}

BossStateType BossStunningState::GetStateType()
{
	return BossStateType::Stunning;
}
