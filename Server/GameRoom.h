#pragma once

#include <chrono>
#include <map>
#include "StateMessage.h"

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

	void ProcessMonsterHpMsg(StateMsgArgu* Arg);

	// COllision Fuction
	bool IsCollision(const RECT& a, const RECT& b);
	void IsCollisionMonsterWithCastle();

	// 송수신 관련 함수
	void WriteMonsterState(MonsterType, BYTE, MonsterStateType);
	void WritePlayerLocation();
	void WriteMonsterSpawn(MonsterType, BYTE);
	void WriteCastleHp();

	void ReadPlayerLocation(StateMsgArgu*);
private:
	std::chrono::time_point<std::chrono::system_clock> m_tPreviousTime;
	float m_fElapsedTime;

	// 현재 가지고 있는 몬스터 리스트
	std::map<int, class Bat*> m_BatMap;
	std::map<int, class Wolf*> m_WolfMap;

	// 플레이어 리스트
	std::array<class PlayerInfo* , MAX_CLIENTS> m_pPlayerList;

	// 몬스터의 일련 번호
	BYTE m_iWolfSN, m_iBatSN;

	// 성
	class Castle* m_pCastle;

	// 현재 몇 페이즈 인지
	int m_iPhase;

	// 스폰 타이머
	float m_fBatSpawnTimer, m_fWolfSpawnTimer;

	class MemoryWriteStream* m_pStream;
};
