#pragma once

#define PLAYERDEFAULTSIZE 100

#include "StateMessage.h"


class PlayerInfo
{
public:
	PlayerInfo(int num);

	RECT GetBB() const;
	void AddKillCount(MonsterType MT) { m_KillCount[(int)MT]++; }

	// 충돌된 객체 추가
	void AddSerialNum(MonsterType MT, int SerialNum);
	void InitCollisionList();
	std::vector<int>& GetCollisionList(int n) { return m_CollisionList[n]; }
	void AddCollisionList(MonsterType MT, int n) { m_CollisionList[(int)MT].push_back(n); }

public:
	FPOINT GetLocation() const				{ return m_PlayerLocation; }
	PStateName GetState() const				{ return m_PlayerState; }
	BYTE GetDirection()	const				{ return m_PlayerDirection; }
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
	
	bool GetShouldCollisionCheck() const	{ return m_bShouldCollisionCheck; }
	void SetShouldCollisionCheck(bool ShouldCheck) { m_bShouldCollisionCheck = ShouldCheck; };

	void SetAllCardProperty(int Damage, int StunDamage, int Destuction, int NamedDamage, int Type);

private:
	unsigned char m_iPlayerNum;

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
	array<WORD, 3> m_KillCount;

	// 두 번 충돌 되지않게
	array<std::vector<int>, 3> m_CollisionList;
};

