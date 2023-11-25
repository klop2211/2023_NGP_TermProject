#pragma once

#include <chrono>

class GameRoom
{
	enum PhaseEnum {WolfPhase, BatPhase, BossPhase};

public:
	GameRoom();
	~GameRoom();

public:
	void SetElapsedTime();
	void Update();

	void SpawnEnemy();
	void UpdateEnemy();

private:
	std::chrono::time_point<std::chrono::system_clock> m_tPreviousTime;
	float m_fElapsedTime;

	// 현재 몇 페이즈 인지
	int Phase;

	// 스폰 타이머
	float BatSpawnTimer;
	float WolfSpawnTimer;
};