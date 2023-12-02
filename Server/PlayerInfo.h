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
	// �÷��̾��� ��ġ
	FPOINT m_PlayerLocation;
	// �÷��̾��� ����
	PStateName m_PlayerState;
	// �÷��̾� ����
	BYTE m_PlayerDirection;
};

