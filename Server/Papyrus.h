#pragma once
#include "Monster.h"
#include "StateMessage.h"

class BossState;

class Papyrus : public Monster
{
public:
	Papyrus();
	~Papyrus();

public:
	void MinusBreakTimer(float ElapsedTime) { m_fBreakTimer -= ElapsedTime; }
	void MinusRemainTimer(float ElapsedTime) { m_fRemainTimeToChangeState -= ElapsedTime; }

	void ChangeState(BossPatternType State);
	void ChangeState(BossState* pNewState);
	virtual void Update(float ElaspedTime);

	virtual bool GetDamageAndIsDead(int Damage, int StunDamage, int Destuction, int NamedDamage, int Type);

private:

public:
	bool	GetBreaked() { return m_bBreaked; }
	bool	GetCanDown() { return m_bCanDown; }
	int		GetBreakCount() { return m_iBreakCount; }
	int		GetKnockDown() { return m_iKnockDown; }
	float	GetBreakTimer() { return m_fBreakTimer; }
	float	GetRemainTimer() { return m_fRemainTimeToChangeState; }
	bool	GetIsStateChanged() { return m_bIsStateChanged; }

	BossPatternType GetStateType() { m_State->GetStateType(); }

	void	SetBreaked(bool bBreaked) { m_bBreaked = bBreaked; };
	void	SetCanDown(bool bCandown) { m_bCanDown = bCandown; };
	void	SetBreakCount(int iBreakcount) { m_iBreakCount = iBreakcount; };
	void	SetKnockDown(int iKnockDown) { m_iKnockDown = iKnockDown; };
	void	SetBreakTimer(float fBreakTimer) { m_fBreakTimer = fBreakTimer; };
	void	SetIsStateChanged(bool bChanged) { m_bIsStateChanged = bChanged; };

private:
	BossState* m_State;

	// 부위파괴가 진행 되었는지
	bool m_bBreaked;
	// 부위파괴나 무력화로 누워있는지?
	bool m_bCanDown;

	// 부위파괴를 넣은 수ㅊㅣ
	int m_iBreakCount;
	// 무력화를 넣은 수치?
	int m_iKnockDown;

	// 넘어져있는 시간
	float m_fBreakTimer;

	// 다음 상태로 넘어가기까지 필요한 타이머
	float m_fRemainTimeToChangeState;

	// 상태가 바뀌어서 메세지를 보내야하는가/
	bool m_bIsStateChanged;
};


