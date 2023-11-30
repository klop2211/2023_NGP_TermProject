#include "Common.h"
#include "GameRoom.h"

#include "Wolf.h"
#include "Bat.h"
#include "Castle.h"
#include "MonsterState.h"
#include "MemoryStream.h"

GameRoom::GameRoom()
{
	m_iWolfSN = m_iBatSN = 0;
	m_pCastle = new Castle();
	m_pStream = new MemoryStream();
}

GameRoom::~GameRoom()
{
	delete m_pCastle;
	delete m_pStream;
}

void GameRoom::SetElapsedTime()
{
	auto currentTime = std::chrono::system_clock::now();

	std::chrono::duration<float> elapsedSeconds = currentTime - m_tPreviousTime;

	m_tPreviousTime = currentTime;

	m_fElapsedTime = elapsedSeconds.count();
}

void GameRoom::Update(array<StateMsgInfo, MAX_CLIENTS> StateMsg)
{
	SetElapsedTime();
	UpdateEnemyUseStateMsg(StateMsg);
	UpdateEnemy();
	SpawnEnemy();

}

void GameRoom::SpawnEnemy()
{
	switch (m_iPhase)
	{
	case WolfPhase:
		m_fWolfSpawnTimer += m_fElapsedTime;

		if (m_fWolfSpawnTimer >= 3.f)
		{
			// TODO: Wolf Spawn Code
			MonsterSpawnStateMsg* SpawnMsg;
			StateMsgByte SMB = MakeStateMsgByte(StateMsgType::MonsterSpawn);

			m_WolfMap.insert({ m_iWolfSN, new Wolf(m_iWolfSN)});
			m_iWolfSN++;
			m_fWolfSpawnTimer = 0.f;
		}
		break;
	case BatPhase:
		m_fBatSpawnTimer += m_fElapsedTime;

		if (m_fBatSpawnTimer >= 3.f)
		{
			// TODO: Bat Spawn 메세지 전송
			MonsterSpawnStateMsg* SpawnMsg;
			StateMsgByte SMB = 0;
			MakeStateMsgByte(StateMsgType::MonsterSpawn);

			m_BatMap.insert({ m_iBatSN, new Bat(m_iBatSN) });
			m_iBatSN++;
			m_fBatSpawnTimer = 0.f;
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
	for (auto it : m_BatMap)
	{
		it.second->Update(m_fElapsedTime);
		if (it.second->GetCanAttack())
		{
			// TODO: 공격 메세지
			//m_pStream->Write();
		}
	}
	for (auto it : m_WolfMap)
	{
		it.second->Update(m_fElapsedTime);
		if (it.second->GetCanAttack())
		{
			// TODO: 공격 메세지
			//m_pStream->Write();
		}
	}
}

bool GameRoom::IsCollision(const RECT& a, const RECT& b)
{
	if (a.left > b.right) return false;
	if (a.right < b.left) return false;
	if (a.top > b.bottom) return false;
	if (a.bottom < b.top) return false;

	return true;
}

void GameRoom::IsCollisionMonsterWithCastle()
{
	RECT BB;
	for (auto it : m_BatMap)
	{
		if (IsCollision(m_pCastle->GetBB(), it.second->GetBoundingBox()))
		{
			// TODO: 공격 상태로 변경 메세지 전송
			it.second->ChangeState(MonsterAttackState::Instance());

		}
	}
	for (auto it : m_WolfMap)
	{
		if (IsCollision(m_pCastle->GetBB(), it.second->GetBoundingBox()))
		{
			it.second->ChangeState(MonsterAttackState::Instance());
		}
	}
}

void GameRoom::ProcessMonsterHpMsg(StateMsgArgu* Arg)
{
	MonsterHpStateMsg* HpMsg = (MonsterHpStateMsg*)Arg;
	int SerialNum = HpMsg->MonsterSerialId;
	int Damage = HpMsg->Damage;

	switch (HpMsg->MonsterId)
	{
	case MonsterType::Wolf:
		m_WolfMap[SerialNum]->IsDead(Damage);
		break;
	case MonsterType::Bat:
		m_BatMap[SerialNum]->IsDead(Damage);
		break;
	case MonsterType::Papyrus:
		break;
	default:
		break;
	}
}

StateMsgByte GameRoom::MakeStateMsgByte(StateMsgType SMT)
{
	// 
	StateMsgByte ReturnValue = 0;
	ReturnValue = (StateMsgByte)SMT;

	return ReturnValue;
}

void GameRoom::UpdateEnemyUseStateMsg(array<StateMsgInfo, MAX_CLIENTS> StateMsg)
{
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		switch (StateMsg[i].StateMsg)
		{
		case (int)StateMsgType::MonsterHp:
			ProcessMonsterHpMsg(StateMsg[i].pStateMsgArgu);
			break;
		case (int)StateMsgType::PlayerMove:

			break;
		case (int)StateMsgType::CastleHp:

			break;
		case (int)StateMsgType::UseCard:

			break;
		default:
			printf("GameRoom::UpdateEnemy Error!\n");
			break;
		}
	}

}
