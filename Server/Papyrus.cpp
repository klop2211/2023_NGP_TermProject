#include "Common.h"

#include "Papyrus.h"
#include "MonsterState.h"

Papyrus::Papyrus()
	:Monster(0)
{
	m_iSpeed = 5;

	m_iCurrentHp = 60;
	m_iMaxHp = 60;
	m_iBreakCount = 10, m_bBreaked = false;
	m_iKnockDown = 100, m_bCanDown = true;
	m_fBreakTimer = 0.f;
	m_Size = POINT{ 49 * 5, 54 * 5 };

	m_fRemainTimeToChangeState = 0.f;
	m_State = BossMoveState::Instance();
}

Papyrus::~Papyrus()
{
}

void Papyrus::ChangeState(State eState)
{
	switch (eState)
	{
	case Papyrus::Move:
		m_fRemainTimeToChangeState = 3.f;
		ChangeState(BossMoveState::Instance());
		break;
	case Papyrus::UBPattern:
		m_fRemainTimeToChangeState = 3.f;
		ChangeState(BossUnBreakPatternState::Instance());
		break;
	case Papyrus::BPattern1:
		m_fRemainTimeToChangeState = 3.f;
		ChangeState(BossBreakPattern1State::Instance());
		break;
	case Papyrus::BPattern2:
		m_fRemainTimeToChangeState = 3.f;
		ChangeState(BossBreakPattern2State::Instance());
		break;
	case Papyrus::CantMove:
		// m_fRemainTimeToChangeState = 3.f;
		ChangeState(BossCantMoveState::Instance());
		break;
	default:
		break;
	}
}

void Papyrus::ChangeState(BossState* pNewState)
{
	m_State->Exit(this);

	m_State = pNewState;

	m_State->Enter(this);
}

void Papyrus::Update(float ElapsedTime)
{
	m_State->Execute(this, ElapsedTime);
}

bool Papyrus::GetDamageAndIsDead(int Damage, int KnockDamage, int Destuction, int NamedDamage, int Type)
{
	m_iCurrentHp -= (Damage + NamedDamage);
	m_iKnockDown -= KnockDamage;
	m_iBreakCount -= Destuction;


	return false;
}
