#include "Common.h"
#include "GameRoom.h"

#include "Wolf.h"
#include "Bat.h"
#include "Castle.h"
#include "MonsterState.h"
#include "MemoryStream.h"

GameRoom::GameRoom(array<SOCKET, MAX_ROOMS>& ClientSocket)
{
	m_iWolfSN = m_iBatSN = 0;
	m_pCastle = new Castle();
	m_pStream = new MemoryStream(ClientSocket);
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
	UpdateUseStateMsg(StateMsg);
	UpdateEnemy();
	SpawnEnemy();
	m_pStream->Send();
}

void GameRoom::SpawnEnemy()
{
	switch (m_iPhase)
	{
	case WolfPhase:
		m_fWolfSpawnTimer += m_fElapsedTime;

		if (m_fWolfSpawnTimer >= 3.f)
		{
			WriteMonsterSpawn(MonsterType::Wolf, m_iBatSN);

			m_WolfMap.insert({ m_iWolfSN, new Wolf(m_iWolfSN)});
			m_iWolfSN++;
			m_fWolfSpawnTimer = 0.f;
		}
		break;
	case BatPhase:
		m_fBatSpawnTimer += m_fElapsedTime;

		if (m_fBatSpawnTimer >= 3.f)
		{
			WriteMonsterSpawn(MonsterType::Bat, m_iBatSN);

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
			WriteMonsterState(MonsterType::Bat, it.first, MonsterStateType::Attack);
			m_pCastle->GetDamage(it.second->GetDamage());
			WriteCastleHp();
		}
	}
	for (auto it : m_WolfMap)
	{
		it.second->Update(m_fElapsedTime);
		if (it.second->GetCanAttack())
		{
			WriteMonsterState(MonsterType::Wolf, it.first, MonsterStateType::Attack);
			m_pCastle->GetDamage(it.second->GetDamage());
			WriteCastleHp();
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
	int SerialNum = HpMsg->SerialId;
	int Damage = HpMsg->Damage;

	switch (HpMsg->Type)
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

void GameRoom::UpdateUseStateMsg(array<StateMsgInfo, MAX_CLIENTS> StateMsg)
{
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		switch (StateMsg[i].StateMsg)
		{
		//case (int)StateMsgType::MonsterHp:
		//	ProcessMonsterHpMsg(StateMsg[i].pStateMsgArgu);
		//	break;
		case (int)StateMsgType::PlayerLocation:
			ReadPlayerLocation(StateMsg[i].pStateMsgArgu);
			break;
		//case (int)StateMsgType::CastleHp:

		//	break;
		case (int)StateMsgType::UseCard:

			break;
		default:
			printf("GameRoom::UpdateEnemy Error!\n");
			break;
		}
	}

}

//=======================Write==============================
//
void GameRoom::WriteMonsterState(MonsterType MT, BYTE id, MonsterStateType MST)
{
	MonsterStateMsg MSM;
	MSM.Type = MT;
	MSM.SerialId = id;
	MSM.State = MST;

	m_pStream->Write(StateMsgType::MonsterState);
	m_pStream->Write(MSM);
}

void GameRoom::WritePlayerLocation()
{
	PlayerLocationMsg PLM;

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		PLM.PlayerId = i;
		PLM.Location.x = m_PlayerLocations[i].x;
		PLM.Location.y = m_PlayerLocations[i].y;

		m_pStream->Write(StateMsgType::PlayerLocation);
		m_pStream->Write(PLM);
	}
}

void GameRoom::WriteMonsterSpawn(MonsterType MT, BYTE id)
{
	MonsterSpawnStateMsg MSSM;
	MSSM.Type = MT;
	MSSM.SerialId = id;

	m_pStream->Write(StateMsgType::MonsterSpawn);
	m_pStream->Write(MSSM);
}

void GameRoom::WriteCastleHp()
{
	m_pStream->Write(StateMsgType::CastleHp);
	m_pStream->Write(m_pCastle->GetCurrnetHp());
}

//=========================Read==================================
//
void GameRoom::ReadPlayerLocation(StateMsgArgu* SMA)
{
	PlayerLocationMsg* PLM = dynamic_cast<PlayerLocationMsg*>(SMA);
	int ClientNum = PLM->PlayerId;
	POINT Location = PLM->Location;

	m_PlayerLocations[ClientNum].x = Location.x;
	m_PlayerLocations[ClientNum].y = Location.y;
}
