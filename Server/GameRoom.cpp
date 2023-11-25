#include "Common.h"
#include "GameRoom.h"

GameRoom::GameRoom()
{
}

GameRoom::~GameRoom()
{
}

void GameRoom::SetElapsedTime()
{
	auto currentTime = std::chrono::system_clock::now();

	std::chrono::duration<float> elapsedSeconds = currentTime - m_tPreviousTime;

	m_tPreviousTime = currentTime;

	m_fElapsedTime = elapsedSeconds.count();

}

void GameRoom::Update()
{
	SetElapsedTime();
	UpdateEnemy();
	SpawnEnemy();
}

void GameRoom::SpawnEnemy()
{
	switch (Phase)
	{
	case WolfPhase:
		WolfSpawnTimer += m_fElapsedTime;

		if (WolfSpawnTimer >= 3.f)
		{
			// TODO: Wolf Spawn Code
			WolfSpawnTimer = 0.f;
		}
		break;
	case BatPhase:
		BatSpawnTimer += m_fElapsedTime;

		if (BatSpawnTimer >= 3.f)
		{
			// TODO: Bat Spawn Code
			BatSpawnTimer = 0.f;
		}
		break;
	case BossPhase:

		break;
	default:
		break;
	}
}

void GameRoom::UpdateEnemy()
{

}
