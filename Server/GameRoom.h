#pragma once

#include <chrono>
#include <map>
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
	void UpdateEnemyUseStateMsg(array<StateMsgInfo, MAX_CLIENTS> StateMsg);
	void UpdateEnemy();

private:
	std::chrono::time_point<std::chrono::system_clock> m_tPreviousTime;
	float m_fElapsedTime;

	// ���� ������ �ִ� ���� ����Ʈ
	std::map<int, class Bat*> m_BatMap;
	std::map<int, class Wolf*> m_WolfMap;

	// ������ �Ϸ� ��ȣ
	BYTE m_iWolfSN, m_iBatSN;



	// ���� �� ������ ����
	int Phase;

	// ���� Ÿ�̸�
	float BatSpawnTimer;
	float WolfSpawnTimer;
};