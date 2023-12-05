#pragma once

#include <chrono>
#include <map>
#include "StateMessage.h"

class PlayerInfo;

class GameRoom
{
	enum PhaseEnum {WolfPhase, BatPhase, BossPhase};

public:
	GameRoom(array<SOCKET, MAX_CLIENTS>&);
	~GameRoom();
public:
	void SetElapsedTime();
	void Update(array<queue<StateMsgInfo>, MAX_CLIENTS> StateMsg);

	void SpawnEnemy();
	void UpdateUseStateMsg(array<queue<StateMsgInfo>, MAX_CLIENTS> StateMsg);
	void UpdateEnemy();

	//void ProcessMonsterHpMsg(StateMsgArgu* Arg);

	// COllision Fuction
	bool IsCollision(const RECT& a, const RECT& b);
	void IsCollisionMonsterWithCastle();
	void IsCollisionMonsterWithPlayer(PlayerInfo*);
	void DoCollisionCheck();

	// �ۼ��� ���� �Լ�
	void WriteMonsterState(MonsterType, BYTE, MonsterStateType);
	void WritePlayerLocation();
	void WriteMonsterSpawn(MonsterType, BYTE);
	void WriteCastleHp();

	void ReadPlayerLocation(StateMsgArgu*);
	void ReadUseCard(StateMsgArgu*);

	// Gameover
	array<array<WORD, (int)MonsterType::END>, MAX_CLIENTS> GetKillCount();

public:
	bool GetIsOver() { return m_bIsOver; }

private:
	std::chrono::time_point<std::chrono::system_clock> m_tPreviousTime;
	float m_fElapsedTime;

	// ���� ������ �ִ� ���� ����Ʈ
	std::map<int, class Bat*> m_BatMap;
	std::map<int, class Wolf*> m_WolfMap;
	class Papyrus* m_Papyrus;

	// �÷��̾� ����Ʈ
	std::array<class PlayerInfo* , MAX_CLIENTS> m_pPlayerList;

	// ������ �Ϸ� ��ȣ
	BYTE m_iWolfSN, m_iBatSN;

	// ��
	class Castle* m_pCastle;

	// TODO: ������ �����ϴ� �ڵ� �ʿ� 
	// ���� �� ������ ����
	int m_iPhase;

	// ���� Ÿ�̸�
	float m_fBatSpawnTimer, m_fWolfSpawnTimer;

	class MemoryWriteStream* m_pStream;

	// �����Ǵ� �ڵ�
	bool m_bIsOver;
};
