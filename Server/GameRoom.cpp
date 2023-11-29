#include "Common.h"
#include "GameRoom.h"

#include "Wolf.h"
#include "Bat.h"

GameRoom::GameRoom()
{
	m_iWolfSN = m_iBatSN = 0;
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

void GameRoom::Update(array<StateMsgInfo, MAX_CLIENTS> StateMsg)
{
	SetElapsedTime();
	UpdateEnemyUseStateMsg(StateMsg);
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
			MonsterSpawnStateMsg* SpawnMsg;
			StateMsgByte SMB = 0;
			MakeStateMsgByte(StateMsgType::MonsterSpawn);
			m_WolfMap.insert({ m_iWolfSN++, new Wolf()});
			WolfSpawnTimer = 0.f;
		}
		break;
	case BatPhase:
		BatSpawnTimer += m_fElapsedTime;

		if (BatSpawnTimer >= 3.f)
		{
			// TODO: Bat Spawn Code
			m_iBatSN++;
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
	for (auto it : m_BatMap)
	{
		it.second->Update(m_fElapsedTime);
	}
	for (auto it : m_WolfMap)
	{
		it.second->Update(m_fElapsedTime);
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
