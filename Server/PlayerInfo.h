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
	// �÷��̾��� ��ġ
	FPOINT m_PlayerLocation;
	// �÷��̾��� ����
	PStateName m_PlayerState;
	// �÷��̾� ����
	BYTE m_PlayerDirection;
	//ī�带 ��� ���̶� ���Ϳ� �浹ó���� �ؾ��ϴ���
	bool m_bShouldCollisionCheck;
};

