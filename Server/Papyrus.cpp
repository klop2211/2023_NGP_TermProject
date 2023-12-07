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
	m_Location = { (float)(CLIENTWINWIDTH),  (float)(634 - m_Size.y) };

	m_fRemainTimeToChangeState = 0.f;
	m_State = BossMoveState::Instance();
}

Papyrus::~Papyrus()
{
}

void Papyrus::ChangeState(BossStateType State)
{
	switch (State)
	{
	case BossStateType::Move:
		m_fRemainTimeToChangeState = 3.f;
		ChangeState(BossMoveState::Instance());
		break;
	case BossStateType::UBPattern:
		m_fRemainTimeToChangeState = 3.f;
		ChangeState(BossUnBreakPatternState::Instance());
		break;
	case BossStateType::BPattern1:
		m_fRemainTimeToChangeState = 3.f;
		ChangeState(BossBreakPattern1State::Instance());
		break;
	case BossStateType::BPattern2:
		m_fRemainTimeToChangeState = 3.f;
		ChangeState(BossBreakPattern2State::Instance());
		break;
	case BossStateType::CantMove:
		// m_fRemainTimeToChangeState = 3.f;
		ChangeState(BossCantMoveState::Instance());
		break;
	default:
		break;
	}

	m_bIsStateChanged = true;
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

	if (m_iCurrentHp <= 0)
	{
		return true;
	}
	if (m_iKnockDown <= 0)
	{
		m_bCanDown = true;
		m_fRemainTimeToChangeState = 1.f;
		ChangeState(BossStateType::CantMove);
	}
	if (m_iBreakCount <= 0)
	{
		m_bBreaked = true;
		m_fRemainTimeToChangeState = 1.f;
		ChangeState(BossStateType::CantMove);
	}

	return false;
}

BossStateType Papyrus::GetStateType()
{
	return m_State->GetStateType();
}
