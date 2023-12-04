#pragma once
#include "Monster.h"

class BossState;

class Papyrus : public Monster
{
public:
	Papyrus();
	~Papyrus();

	enum State {Move, UBPattern, BPattern1, BPattern2, CantMove};

public:
	void MinusBreakTimer(float ElapsedTime) { m_fBreakTimer -= ElapsedTime; }
	void MinusRemainTimer(float ElapsedTime) { m_fRemainTimeToChangeState -= ElapsedTime; }

	void ChangeState(State eState);
	void ChangeState(BossState* pNewState);
	virtual void Update(float ElaspedTime);

	virtual bool GetDamageAndIsDead(int Damage, int StunDamage, int Destuction, int NamedDamage, int Type);

private:

public:
	bool	GetBreaked()		{return m_bBreaked;}
	bool	GetCanDown()		{return m_bCanDown;}
	int		GetBreakCount()		{return m_iBreakCount;}
	int		GetKnockDown()		{return m_iKnockDown;}
	float	GetBreakTimer()		{return m_fBreakTimer;}
	float	GetRemainTimer()	{return m_fRemainTimeToChangeState;}

	void	SetBreaked(bool bBreaked)			{m_bBreaked = bBreaked;};
	void	SetCanDown(bool bCandown)			{m_bCanDown = bCandown;};
	void	SetBreakCount(int iBreakcount)		{m_iBreakCount = iBreakcount;};
	void	SetKnockDown(int iKnockDown)		{m_iKnockDown = iKnockDown;};
	void	SetBreakTimer(float fBreakTimer)	{m_fBreakTimer = fBreakTimer;};

private:
	BossState* m_State;

	// �����ı��� ���� �Ǿ�����
	bool m_bBreaked;
	// �����ı��� ����ȭ�� �����ִ���?
	bool m_bCanDown;

	// �����ı��� ���� ������
	int m_iBreakCount;
	// ����ȭ�� ���� ��ġ?
	int m_iKnockDown;

	// �Ѿ����ִ� �ð�
	float m_fBreakTimer;

	// ���� ���·� �Ѿ����� �ʿ��� Ÿ�̸�
	float m_fRemainTimeToChangeState;
};


