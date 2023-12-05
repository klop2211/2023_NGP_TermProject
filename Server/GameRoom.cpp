#include "Common.h"
#include "GameRoom.h"

#include "Wolf.h"
#include "Bat.h"
#include "Papyrus.h"
#include "MonsterState.h"
#include "Castle.h"

#include "PlayerInfo.h"
#include "MemoryWriteStream.h"

GameRoom::GameRoom(array<SOCKET, MAX_CLIENTS>& ClientSocket) :
	m_iWolfSN(0),
	m_iBatSN(0),
	m_iPhase(GameRoom::WolfPhase),
	m_Papyrus(nullptr),
	m_bIsOver(false)
{
	m_pCastle = new Castle();
	m_pStream = new MemoryWriteStream(ClientSocket);
	for (auto& p : m_pPlayerList)
	{
		p = new PlayerInfo();
	}
}

GameRoom::~GameRoom()
{
	delete m_pCastle;
	delete m_pStream;
	for (auto& p : m_pPlayerList)
	{
		delete p;
		//p = nullptr;
	}
}

void GameRoom::SetElapsedTime()
{
	auto currentTime = std::chrono::system_clock::now();

	std::chrono::duration<float> elapsedSeconds = currentTime - m_tPreviousTime;

	m_tPreviousTime = currentTime;

	m_fElapsedTime = elapsedSeconds.count();
}

void GameRoom::Update(array<queue<StateMsgInfo>, MAX_CLIENTS> StateMsg)
{
	SetElapsedTime();
	UpdateUseStateMsg(StateMsg);
	WritePlayerLocation();
	//SpawnEnemy();
	//UpdateEnemy();
	DoCollisionCheck();

	m_pStream->Send();
}

void GameRoom::SpawnEnemy()
{
	switch (m_iPhase)
	{
	case WolfPhase:
		m_fWolfSpawnTimer += m_fElapsedTime;

		if (m_fWolfSpawnTimer >= 5.f)
		{
			WriteMonsterSpawn(MonsterType::Wolf, m_iBatSN);

			m_WolfMap.insert({ m_iWolfSN, new Wolf(m_iWolfSN)});
			m_iWolfSN++;
			m_fWolfSpawnTimer = 0.f;
		}
		break;
	case BatPhase:
		m_fBatSpawnTimer += m_fElapsedTime;

		if (m_fBatSpawnTimer >= 5.f)
		{
			WriteMonsterSpawn(MonsterType::Bat, m_iBatSN);

			m_BatMap.insert({ m_iBatSN, new Bat(m_iBatSN) });
			m_iBatSN++;
			m_fBatSpawnTimer = 0.f;
		}
		break;
	case BossPhase:
		if (!m_Papyrus)
		{
			m_Papyrus = new Papyrus();
		}
		break;
	default:
		break;
	}
}

void GameRoom::UpdateEnemy()
{
	for (const auto& it : m_BatMap)
	{
		int MonNum = it.first;
		Bat* bat = it.second;

		bat->Update(m_fElapsedTime);
		if (bat->GetCanAttack())
		{
			bat->SetCanAttack(false);
			WriteMonsterState(MonsterType::Bat, MonNum, MonsterStateType::Attack);
			m_pCastle->GetDamage(bat->GetDamage());
			WriteCastleHp();
		}
	}
	for (const auto& it : m_WolfMap)
	{
		int MonNum = it.first;
		Wolf* wolf = it.second;

		wolf->Update(m_fElapsedTime);
		if (wolf->GetCanAttack())
		{
			wolf->SetCanAttack(false);
			WriteMonsterState(MonsterType::Wolf, it.first, MonsterStateType::Attack);
			m_pCastle->GetDamage(wolf->GetDamage());
			WriteCastleHp();
		}
	}

	if (m_Papyrus)
	{
		m_Papyrus->Update(m_fElapsedTime);
		if (m_Papyrus->GetIsStateChanged())
		{
			m_Papyrus->SetIsStateChanged(false);

			BossPatternMsg BPM;
			BPM.Pattern = m_Papyrus->GetStateType();

			m_pStream->Write(StateMsgType::BossState);
			m_pStream->Write(BPM);
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
	for (const auto& it : m_BatMap)
	{
		if (IsCollision(m_pCastle->GetBB(), it.second->GetBoundingBox()))
		{
			it.second->ChangeState(MonsterAttackState::Instance());

		}
	}
	for (const auto& it : m_WolfMap)
	{
		if (IsCollision(m_pCastle->GetBB(), it.second->GetBoundingBox()))
		{
			it.second->ChangeState(MonsterAttackState::Instance());
		}
	}
}

void GameRoom::IsCollisionMonsterWithPlayer(PlayerInfo* p)
{
	for (const auto& it : m_BatMap)
	{
		int SN = it.first;
		Bat* bat = it.second;
		if (IsCollision(p->GetBB(), bat->GetBoundingBox()))
		{
			bool IsDead = bat->GetDamageAndIsDead(
				p->GetDamage(),
				0, 0, 0,
				p->GetType());

			MonsterHpStateMsg MHSM;
			MHSM.SerialId = SN;
			MHSM.Type = MonsterType::Bat;
			MHSM.Hp = bat->GetCurrentHp();

			m_pStream->Write(StateMsgType::MonsterHp);
			m_pStream->Write(MHSM);

			if (IsDead)
			{
				p->AddKillCount(MonsterType::Bat);
				m_BatMap.erase(SN);
			}
		}
	}
	for (const auto& it : m_WolfMap)
	{
		int SN = it.first;
		Wolf* wolf = it.second;
		if (IsCollision(p->GetBB(), wolf->GetBoundingBox()))
		{
			bool IsDead = wolf->GetDamageAndIsDead(
				p->GetDamage(),
				0, 0, 0,
				p->GetType());

			MonsterHpStateMsg MHSM;
			MHSM.SerialId = SN;
			MHSM.Type = MonsterType::Wolf;
			MHSM.Hp = wolf->GetCurrentHp();

			m_pStream->Write(StateMsgType::MonsterHp);
			m_pStream->Write(MHSM);

			if (IsDead)
			{
				p->AddKillCount(MonsterType::Wolf);
				m_WolfMap.erase(SN);
			}
		}
	}

	if (m_Papyrus)
	{
		if (IsCollision(p->GetBB(), m_Papyrus->GetBoundingBox()))
		{
			bool IsDead = m_Papyrus->GetDamageAndIsDead(
				p->GetDamage(),
				p->GetStunDamage(),
				p->GetDestuction(),
				p->GetNamedDamage(),
				p->GetType());

			MonsterHpStateMsg MHSM;
			MHSM.SerialId = 0;
			MHSM.Type = MonsterType::Papyrus;
			MHSM.Hp = m_Papyrus->GetCurrentHp();

			m_pStream->Write(StateMsgType::MonsterHp);
			m_pStream->Write(MHSM);

			if (IsDead)
			{
				// TODO: 게임종료
			}
		}
	}
}

void GameRoom::DoCollisionCheck()
{
	// TODO: Collision Group으로 개선 필요
	for (const auto& p : m_pPlayerList)
	{
		if (p->GetShouldCollisionCheck())
		{
			IsCollisionMonsterWithPlayer(p);
		}
	}
	IsCollisionMonsterWithCastle();
}

//void GameRoom::ProcessMonsterHpMsg(StateMsgArgu* Arg)
//{
//	MonsterHpStateMsg* HpMsg = (MonsterHpStateMsg*)Arg;
//	int SerialNum = HpMsg->SerialId;
//	int Damage = HpMsg->Damage;
//
//	switch (HpMsg->Type)
//	{
//	case MonsterType::Wolf:
//		m_WolfMap[SerialNum]->IsDead(Damage);
//		break;
//	case MonsterType::Bat:
//		m_BatMap[SerialNum]->IsDead(Damage);
//		break;
//	case MonsterType::Papyrus:
//		break;
//	default:
//		break;
//	}
//}

void GameRoom::UpdateUseStateMsg(array<queue<StateMsgInfo>, MAX_CLIENTS> StateMsg)
{
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		while (!StateMsg[i].empty())
		{
			StateMsgInfo SMI = StateMsg[i].front();
			StateMsg[i].pop();

			switch (SMI.StateMsg)
			{
			case StateMsgType::PlayerLocation:
				ReadPlayerLocation(SMI.pStateMsgArgu);
				break;
			case StateMsgType::UseCard:
				ReadUseCard(SMI.pStateMsgArgu);
				break;
			default:
				printf("GameRoom::UpdateEnemy Error!\n");
				break;
			}

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
		PLM.Location.x = m_pPlayerList[i]->GetLocation().x;
		PLM.Location.y = m_pPlayerList[i]->GetLocation().y;
		PLM.State = m_pPlayerList[i]->GetState();
		PLM.Direction = m_pPlayerList[i]->GetDirection();

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
	PlayerLocationMsg* PLM = (PlayerLocationMsg*)SMA;
	//memcpy(PLM, SMA, sizeof(PlayerLocationMsg));

	int ClientNum = PLM->PlayerId;
	POINT Location = PLM->Location;
	PStateName PSN = PLM->State;
	int dirction = PLM->Direction;

	// Dummy Data 무시 (클라측에선 -1)
	if (ClientNum == 255)
	{
		return;
	}

	m_pPlayerList[ClientNum]->SetLocation(FPOINT(Location.x, Location.y));
	m_pPlayerList[ClientNum]->SetState(PSN);
	m_pPlayerList[ClientNum]->SetDirection(dirction);

	// 충돌처리 off
	m_pPlayerList[ClientNum]->SetShouldCollisionCheck(false);
	m_pPlayerList[ClientNum]->SetAllCardProperty(0, 0, 0, 0, 0);
}

void GameRoom::ReadUseCard(StateMsgArgu* SMA)
{
	UseCardStateMsg* UCSM = (UseCardStateMsg*)SMA;
	int ClientNum = UCSM->PlayerId;

	// 충돌처리 on
	m_pPlayerList[ClientNum]->SetShouldCollisionCheck(true);
	m_pPlayerList[ClientNum]->SetAllCardProperty(
		UCSM->Damage,
		UCSM->StunDamage,
		UCSM->Destuction,
		UCSM->NamedDamage,
		UCSM->Type
	);
}

//===============================Getter================================
array<array<WORD, (int)MonsterType::END>, MAX_CLIENTS> GameRoom::GetKillCount()
{
	array<array<WORD, (int)MonsterType::END>, MAX_CLIENTS> ReturnValue;

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		ReturnValue[i] = m_pPlayerList[i]->GetKillCount();
	}

	return ReturnValue;
}
