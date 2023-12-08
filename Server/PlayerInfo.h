#pragma once

#define PLAYERDEFAULTSIZE 100

#include "StateMessage.h"


class PlayerInfo
{
public:
	PlayerInfo(int num) :
		m_iPlayerNum(num),
		m_iDamage(0),
		m_iStunDamage(0),
		m_iDestuction(0),
		m_iNamedDamage(0),
		m_iType(0)
	{}

	RECT GetBB() const;
	void AddKillCount(MonsterType MT) { m_KillCount[(int)MT]++; }

public:
	FPOINT GetLocation() const				{ return m_PlayerLocation; }
	PStateName GetState() const				{ return m_PlayerState; }
	BYTE GetDirection()	const				{ return m_PlayerDirection; }
	bool GetShouldCollisionCheck() const	{ return m_bShouldCollisionCheck; }
	int GetDamage() const					{ return m_iDamage; }
	int GetStunDamage() const				{ return m_iStunDamage; }
	int GetDestuction() const				{ return m_iDestuction; }
	int GetNamedDamage() const				{ return m_iNamedDamage; }
	int GetType() const						{ return m_iType; }
	array<WORD, 3> GetKillCount()			{ return m_KillCount; };
	int GetPlayerNum()						{ return m_iPlayerNum; }

	void SetLocation(FPOINT point) { m_PlayerLocation = point; };
	void SetState(PStateName name) { m_PlayerState = name; };
	void SetDirection(BYTE direction) { m_PlayerDirection = direction; };
	void SetShouldCollisionCheck(bool ShouldCheck) { m_bShouldCollisionCheck = ShouldCheck; };

	void SetAllCardProperty(int Damage, int StunDamage, int Destuction, int NamedDamage, int Type);

private:
	unsigned char m_iPlayerNum;

	// �÷��̾��� ��ġ
	FPOINT m_PlayerLocation;
	// �÷��̾��� ����
	PStateName m_PlayerState;
	// �÷��̾� ����
	BYTE m_PlayerDirection;

	// ī�� ��� �� �浹�� ������ ����� ���� ��ġ
	BYTE m_iDamage, m_iStunDamage, m_iDestuction, m_iNamedDamage, m_iType;

	//ī�带 ��� ���̶� ���Ϳ� �浹ó���� �ؾ��ϴ���
	bool m_bShouldCollisionCheck;

	// ���� ���� ��
	array<WORD, 3> m_KillCount;
};

