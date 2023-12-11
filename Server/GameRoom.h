#pragma once

#include <chrono>
#include <map>
#include <list>
#include "StateMessage.h"

class PlayerInfo;
class Papyrus;
class CommonMonster;
class SkillObjectInfo;
class Monster;

class GameRoom
{
public:
	enum PhaseEnum : BYTE {WolfPhase, BatPhase, BossPhase};
	enum GameOverFlag : char {Win = 1, NotYet = 0, Lose = -1};

	GameRoom(array<SOCKET, MAX_CLIENTS>&);
	~GameRoom();
public:
	void SetElapsedTime();
	void Update(array<queue<StateMsgInfo>, MAX_CLIENTS>& StateMsg);

	void SpawnEnemy();
	void UpdateUseStateMsg(array<queue<StateMsgInfo>, MAX_CLIENTS>& StateMsg);
	void UpdateEnemy();

	//void ProcessMonsterHpMsg(StateMsgArgu* Arg);
	void DoGarbageCollector();

	// COllision Fuction
	bool IsCollision(const RECT& a, const RECT& b);
	void IsCollisionMonsterWithCastle();
	void IsCollisionMonsterWithPlayer(PlayerInfo*);
	void IsCollisionBoneWithPlayer(PlayerInfo*);
	void DoCollisionCheck();
	void CollisionSkillObject();
	void DamageToMonsterUsingSkillObject(SkillObjectInfo*, Monster*);

	// �ۼ��� ���� �Լ�
	void WriteMonsterLocation(MonsterType, BYTE, POINT location = {0, 0});
	void WriteMonsterState(MonsterType, BYTE, MonsterStateType);
	void WriteMonsterHp(MonsterType, BYTE, BYTE);
	void WritePlayerLocation();
	void WriteCastleHp();
	void WriteBossHp();
	void WriteBossState(BossStateType);
	void WriteBones();
	void WriteMonsterKill(MonsterType MT, BYTE Serial, PlayerInfo* player);
	void WriteUseCard(UseCardStateMsg UCSM, int ClientNum);

	void ReadPlayerLocation(StateMsgArgu*);
	void ReadUseCard(StateMsgArgu*);
	void ReadSkillObjectLocation(StateMsgArgu*);

	void CheckMonsterChangeState(CommonMonster* monster, MonsterType ,int SN);
	void CheckMonsterChangeState(Papyrus* papyrus);

	// ųī��Ʈ Gameover�� ���
	array<array<WORD, 3>, MAX_CLIENTS> GetKillCount();

public:
	char GetIsOver() { return m_bIsOver; }

private:
	std::chrono::time_point<std::chrono::system_clock> m_tPreviousTime;
	float m_fElapsedTime;

	// ���� ������ �ִ� ���� ����Ʈ
	std::map<int, class Bat*> m_BatMap;
	std::map<int, class Wolf*> m_WolfMap;
	class Papyrus* m_Papyrus;

	std::map<int, SkillObjectInfo*> m_SkillObject;

	// �÷��̾� ����Ʈ
	std::array<class PlayerInfo* , MAX_CLIENTS> m_pPlayerList;

	// ������ �Ϸ� ��ȣ
	BYTE m_iWolfSN, m_iBatSN;

	// ��
	class Castle* m_pCastle;

	// TODO: ������ �����ϴ� �ڵ� �ʿ� 
	// ���� �� ������ ����
	int m_iPhase;
	float m_fPhaseChangeTimer, m_fPhaseInitTimer;

	// ���� Ÿ�̸�
	float m_fBatSpawnTimer, m_fWolfSpawnTimer;

	class MemoryWriteStream* m_pStream;

	// �����Ǵ� �ڵ� -1: �й�, 0 �ȳ���, 1: �¸�
	char m_bIsOver;
};
