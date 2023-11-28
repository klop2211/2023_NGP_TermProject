#pragma once

#include <chrono>
#include "StateMessage.h"

class GameRoom
{
	enum PhaseEnum {WolfPhase, BatPhase, BossPhase};

public:
	GameRoom();
	~GameRoom();

public:
	void SetElapsedTime();
	void Update(array<StateMsgInfo, MAX_CLIENTS> StateMsg);
	void SpawnEnemy();
	void UpdateEnemy(array<StateMsgInfo, MAX_CLIENTS> StateMsg);

	void SplitStateMsg();

private:
	std::chrono::time_point<std::chrono::system_clock> m_tPreviousTime;
	float m_fElapsedTime;

	// 현재 몇 페이즈 인지
	int Phase;

	// 스폰 타이머
	float BatSpawnTimer;
	float WolfSpawnTimer;
};