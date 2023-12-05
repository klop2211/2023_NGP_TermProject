#pragma once

#define PLAYERDEFAULTSIZE 100

#include "StateMessage.h"


class PlayerInfo
{
public:
	PlayerInfo() :
		m_iDamage(0),
		m_iStunDamage(0),
		m_iDestuction(0),
		m_iNamedDamage(0),
		m_iType(0)
	{}

	RECT GetBB() const;
	void AddKillCount(MonsterType MT) { m_KillCount[(int)MT]++; }

public:
	FPOINT GetLocation() const { return m_PlayerLocation; }
	PStateName GetState() const { return m_PlayerState; }
	BYTE GetDirection()	const { return m_PlayerDirection; }
	bool GetShouldCollisionCheck() const { return m_bShouldCollisionCheck; }
	int GetDamage() const { return m_iDamage; }
	int GetStunDamage() const { return m_iStunDamage; }
	int GetDestuction() const { return m_iDestuction; }
	int GetNamedDamage() const { return m_iNamedDamage; }
	int GetType() const { return m_iType; }
	array<WORD, (int)MonsterType::END> GetKillCount() { return m_KillCount; };

	void SetLocation(FPOINT point) { m_PlayerLocation = point; };
	void SetState(PStateName name) { m_PlayerState = name; };
	void SetDirection(BYTE direction) { m_PlayerDirection = direction; };
	void SetShouldCollisionCheck(bool ShouldCheck) { m_bShouldCollisionCheck = ShouldCheck; };

	void SetAllCardProperty(int Damage, int StunDamage, int Destuction, int NamedDamage, int Type);

private:
	// 플레이어의 위치
	FPOINT m_PlayerLocation;
	// 플레이어의 상태
	PStateName m_PlayerState;
	// 플레이어 방향
	BYTE m_PlayerDirection;

	// 카드 사용 후 충돌시 데미지 계산을 위한 수치
	BYTE m_iDamage, m_iStunDamage, m_iDestuction, m_iNamedDamage, m_iType;

	//카드를 사용 중이라 몬스터와 충돌처리를 해야하는지
	bool m_bShouldCollisionCheck;

	// 잡은 몬스터 수
	array<WORD, (int)MonsterType::END> m_KillCount;
};

