#pragma once

#define PLAYERDEFAULTSIZE 100

#include "StateMessage.h"


class PlayerInfo
{
public:
	RECT GetBB();

public:
	FPOINT GetLocation() const			{ return m_PlayerLocation; }
	PStateName GetState() const			{ return m_PlayerState; }
	BYTE GetDirection()	const			{ return m_PlayerDirection; }
	bool GetShouldCollisionCheck() const { return m_bShouldCollisionCheck; }

	void SetLocation(FPOINT point)					{ m_PlayerLocation = point; };
	void SetState(PStateName name)					{ m_PlayerState = name; };
	void SetDirection(BYTE direction)				{ m_PlayerDirection = direction; };
	void SetShouldCollisionCheck(bool ShouldCheck)	{ m_bShouldCollisionCheck = ShouldCheck; };

private:
	// 플레이어의 위치
	FPOINT m_PlayerLocation;
	// 플레이어의 상태
	PStateName m_PlayerState;
	// 플레이어 방향
	BYTE m_PlayerDirection;
	//카드를 사용 중이라 몬스터와 충돌처리를 해야하는지
	bool m_bShouldCollisionCheck;
};

