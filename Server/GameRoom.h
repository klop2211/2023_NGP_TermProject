#pragma once

#include <chrono>
#include <map>
#include "StateMessage.h"

class GameRoom
{
	enum PhaseEnum {WolfPhase, BatPhase, BossPhase};

public:
	GameRoom(array<SOCKET, MAX_ROOMS>&);
	~GameRoom();
public:
	void SetElapsedTime();
	void Update(array<StateMsgInfo, MAX_CLIENTS> StateMsg);

	void SpawnEnemy();
	void UpdateUseStateMsg(array<StateMsgInfo, MAX_CLIENTS> StateMsg);
	void UpdateEnemy();

	void ProcessMonsterHpMsg(StateMsgArgu* Arg);

	StateMsgByte MakeStateMsgByte(StateMsgType);

	// COllision Fuction
	bool IsCollision(const RECT& a, const RECT& b);
	void IsCollisionMonsterWithCastle();

	// �ۼ��� ���� �Լ�
	void WriteMonsterState(MonsterType, BYTE, MonsterStateType);
	void WritePlayerLocation();
	void WriteMonsterSpawn(MonsterType, BYTE);
	void WriteCastleHp();

	void ReadPlayerLocation(StateMsgArgu*);
private:
	std::chrono::time_point<std::chrono::system_clock> m_tPreviousTime;
	float m_fElapsedTime;

	// ���� ������ �ִ� ���� ����Ʈ
	std::map<int, class Bat*> m_BatMap;
	std::map<int, class Wolf*> m_WolfMap;

	// �÷��̾��� ��ġ ����Ʈ
	std::array<FPOINT, MAX_CLIENTS> m_PlayerLocations;

	// ������ �Ϸ� ��ȣ
	BYTE m_iWolfSN, m_iBatSN;

	// ��
	class Castle* m_pCastle;

	// ���� �� ������ ����
	int m_iPhase;

	// ���� Ÿ�̸�
	float m_fBatSpawnTimer;
	float m_fWolfSpawnTimer;

	class MemoryStream* m_pStream;
};
