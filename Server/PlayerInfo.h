#pragma once

#include "StateMessage.h"

class PlayerInfo
{
public:
	FPOINT GetLocation() const	{ return m_PlayerLocation; }
	PStateName GetState() const { return m_PlayerState; }
	BYTE GetDirection()	const	{ return m_PlayerDirection; }

	void SetLocation(FPOINT point)		{ m_PlayerLocation = point; };
	void SetState(PStateName name)		{ m_PlayerState = name; };
	void SetDirection(BYTE direction)	{ m_PlayerDirection = direction; };

private:
	// 플레이어의 위치
	FPOINT m_PlayerLocation;
	// 플레이어의 상태
	PStateName m_PlayerState;
	// 플레이어 방향
	BYTE m_PlayerDirection;
};

