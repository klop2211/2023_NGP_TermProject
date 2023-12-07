#pragma once

#include <chrono>
#include <map>
#include "StateMessage.h"

class PlayerInfo;
class Papyrus;
class CommonMonster;

class GameRoom
{
public:
	enum PhaseEnum : BYTE {WolfPhase, BatPhase, BossPhase};
	enum GameOverFlag : char {Win = 1, NotYet = 0, Lose = -1};

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

	// 송수신 관련 함수
	void WriteMonsterLocation(MonsterType, BYTE, POINT location = {0, 0});
	void WriteMonsterState(MonsterType, BYTE, MonsterStateType);
	void WriteMonsterHp(MonsterType, BYTE, BYTE);
	void WritePlayerLocation();
	void WriteCastleHp();
	void WriteBossHp();
	void WriteBossState(BossStateType);
	void WriteBones();

	void ReadPlayerLocation(StateMsgArgu*);
	void ReadUseCard(StateMsgArgu*);

	void CheckMonsterChangeState(CommonMonster* monster, MonsterType ,int SN);
	void CheckMonsterChangeState(Papyrus* papyrus);

	// 킬카운트 Gameover시 사용
	array<array<WORD, 3>, MAX_CLIENTS> GetKillCount();

public:
	char GetIsOver() { return m_bIsOver; }

private:
	std::chrono::time_point<std::chrono::system_clock> m_tPreviousTime;
	float m_fElapsedTime;

	// 현재 가지고 있는 몬스터 리스트
	std::map<int, class Bat*> m_BatMap;
	std::map<int, class Wolf*> m_WolfMap;
	class Papyrus* m_Papyrus;

	// 플레이어 리스트
	std::array<class PlayerInfo* , MAX_CLIENTS> m_pPlayerList;

	// 몬스터의 일련 번호
	BYTE m_iWolfSN, m_iBatSN;

	// 성
	class Castle* m_pCastle;

	// TODO: 페이즈 증가하는 코드 필요 
	// 현재 몇 페이즈 인지
	int m_iPhase;

	// 스폰 타이머
	float m_fBatSpawnTimer, m_fWolfSpawnTimer;

	class MemoryWriteStream* m_pStream;

	// 종료판단 코드 -1: 패배, 0 안끝남, 1: 승리
	char m_bIsOver;
};
