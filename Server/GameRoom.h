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

	// ���� �� ������ ����
	int Phase;

	// ���� Ÿ�̸�
	float BatSpawnTimer;
	float WolfSpawnTimer;
};