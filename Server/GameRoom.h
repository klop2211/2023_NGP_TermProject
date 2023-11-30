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

	void ProcessMonsterHpMsg(StateMsgArgu* Arg);

	StateMsgByte MakeStateMsgByte(StateMsgType);

	// COllision Fuction
	bool IsCollision(const RECT& a, const RECT& b);
	void IsCollisionMonsterWithCastle();

private:
	std::chrono::time_point<std::chrono::system_clock> m_tPreviousTime;
	float m_fElapsedTime;

	// 현재 가지고 있는 몬스터 리스트
	std::map<int, class Bat*> m_BatMap;
	std::map<int, class Wolf*> m_WolfMap;

	// 플레이어의 위치 리스트
	std::array<FPOINT, MAX_CLIENTS> m_PlayerLocations;

	// 몬스터의 일련 번호
	BYTE m_iWolfSN, m_iBatSN;

	// 성
	class Castle* m_pCastle;

	// 현재 몇 페이즈 인지
	int Phase;

	// 스폰 타이머
	float BatSpawnTimer;
	float WolfSpawnTimer;

	class MemoryStream* stream;
};
