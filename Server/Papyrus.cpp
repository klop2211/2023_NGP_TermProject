#include "Common.h"

#include "Papyrus.h"
#include "MonsterState.h"
#include "Bone.h"

Papyrus::Papyrus()
	:Monster(0)
{
	m_iSpeed = 1;

	m_iCurrentHp = 60;
	m_iMaxHp = 60;
	m_iBreakCount = 10, m_bBreaked = false;
	m_iKnockDown = 100, m_bCanDown = true;
	m_fBreakTimer = 0.f;
	m_Size = POINT{ 49 * 5, 54 * 5 };
	m_Location = { (float)(CLIENTWINWIDTH),  (float)(634 - m_Size.y) };

	m_fRemainTimeToChangeState = 5.f;
	m_State = BossMoveState::Instance();

	m_iBoneNum = 0;
	m_iMaxUpdateMiniBone = 0;
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
		//m_fRemainTimeToChangeState = 3.f;
		ChangeState(BossBreakPattern2State::Instance());
		break;
	case BossStateType::Breaking:
		m_fRemainTimeToChangeState = 1.f;
		ChangeState(BossBreakingState::Instance());
		break;
	case BossStateType::Stunning:
		m_fRemainTimeToChangeState = 6.f;
		ChangeState(BossStunningState::Instance());
		break;
	case BossStateType::CantMove:
		m_fRemainTimeToChangeState = 3.f;
		ChangeState(BossCantMoveState::Instance());
		break;
	default:
		break;
	}
}

void Papyrus::ChangeState(BossState* pNewState)
{
	m_bChangedState = true;

	m_State->Exit(this);

	m_State = pNewState;

	m_State->Enter(this);
}

void Papyrus::Update(float ElapsedTime)
{
	// 지울 예정인것들은 메세지를 먼저 보내기 위해 업데이트보다 빨리 호출
	BoneGarbageCollector();

	m_State->Execute(this, ElapsedTime);

	BoneUpdate(ElapsedTime);

	// TODO: 지워야함
	static float timer = 0.f;
	timer += ElapsedTime;
	if (timer > 0.25)
	{
		timer = 0.f;
		//GetDamageAndIsDead(1, 5, 1, 0);
	}
}

void Papyrus::BoneUpdate(float ElaspedTime)
{
	for (int i = 0; i < 2; i++)
	{
		if (m_pBone[i])
		{
			m_pBone[i]->Update(ElaspedTime);
		}
	}
	for (int i = 0; i < 15; i++)
	{
		if (m_pMiniBone[i])
		{
			m_pMiniBone[i]->Update(ElaspedTime);
		}
	}
}

void Papyrus::BoneGarbageCollector()
{
	for (int i = 0; i < 2; i++)
	{
		if (m_pBone[i] && m_pBone[i]->GetCanDie())
		{
			delete m_pBone[i];
			m_pBone[i] = nullptr;
		}
	}
	for (int i = 0; i < 15; i++)
	{
		if (m_pMiniBone[i] && m_pMiniBone[i]->GetCanDie())
		{
			delete m_pMiniBone[i];
			m_pMiniBone[i] = nullptr;
		}
	}
}

bool Papyrus::GetDamageAndIsDead(int Damage, int KnockDamage, int Destuction, int NamedDamage, int Type)
{
	m_iCurrentHp -= (Damage + NamedDamage);
	m_iBreakCount -= Destuction;
	if (m_bBreaked)
	{
		m_iKnockDown -= KnockDamage;
	}

	if (m_iCurrentHp <= 0)
	{
		return true;
	}
	if (m_iKnockDown <= 0)
	{
		m_iKnockDown = 10000;
		ChangeState(BossStateType::Stunning);
	}
	if (!m_bBreaked && m_iBreakCount <= 0)
	{
		m_bBreaked = true;
		ChangeState(BossStateType::Breaking);
	}

	return false;
}

void Papyrus::MakeBone(int BoneType)
{
	switch (BoneType)
	{
	case Bone::UnBreak:
	{
		FPOINT point = { m_Location.x, m_Location.y + m_Size.y};
		m_pBone[0] = new Bone(m_iBoneNum++, Bone::UnBreak, point);
	}
		break;
	case Bone::Break1:
		m_pBone[1] = new Bone(m_iBoneNum++, Bone::Break1, m_Location);
		break;
	default:
		break;
	}
}

void Papyrus::MakeMiniBone()
{
	FPOINT location = { m_Location.x + 25 * 5, m_Location.y + 20 * 5 };
	for (int i = 0; i < 15; i++)
	{
		m_pMiniBone[i] = new Bone(m_iBoneNum++, Bone::Break2, location);
	}
}

void Papyrus::MakeMiniBone(int Count)
{
	FPOINT location = { m_Location.x + 25 * 5, m_Location.y + 20 * 5 };
	m_pMiniBone[Count] = new Bone(m_iBoneNum++, Bone::Break2, location);
}

BossStateType Papyrus::GetStateType()
{
	return m_State->GetStateType();
}

Bone** Papyrus::GetBone()
{ 
	return m_pBone;
}

Bone** Papyrus::GetMiniBone()
{
	return m_pMiniBone;
}
