#include "Common.h"
#include "GameRoom.h"

#include "Wolf.h"
#include "Bat.h"
#include "Papyrus.h"
#include "MonsterState.h"
#include "Castle.h"
#include "Bone.h"

#include "PlayerInfo.h"
#include "../MemStream/MemoryWriteStream.h"

#include <algorithm>

GameRoom::GameRoom(array<SOCKET, MAX_CLIENTS>& ClientSocket) :
	m_iWolfSN(0),
	m_iBatSN(0),
	m_iPhase(GameRoom::BossPhase),
	m_Papyrus(nullptr),
	m_bIsOver(NotYet),
	m_fPhaseInitTimer(15.f),
	m_fPhaseChangeTimer(m_fPhaseInitTimer)
{
	m_pCastle = new Castle();
	m_pStream = new MemoryWriteStream(ClientSocket);
	for (int i = 0; i < m_pPlayerList.size(); i++)
	{
		m_pPlayerList[i] = new PlayerInfo(i);
	}

	m_tPreviousTime = std::chrono::system_clock::now();
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
	SpawnEnemy();
	UpdateEnemy();
	DoCollisionCheck();

	m_pStream->Send();
}

void GameRoom::SpawnEnemy()
{
	// 페이즈 변화
	m_fPhaseChangeTimer -= m_fElapsedTime;
	if (m_fPhaseChangeTimer < 0.f)
	{
		m_fPhaseChangeTimer = m_fPhaseInitTimer;

		m_iPhase = min(++m_iPhase, (int)PhaseEnum::BossPhase);
	}

	switch (m_iPhase)
	{
	case BossPhase:
		if (!m_Papyrus)
		{
			m_Papyrus = new Papyrus();
		}
		break;
	case BatPhase:
		m_fBatSpawnTimer += m_fElapsedTime;

		if (m_fBatSpawnTimer >= 5.f)
		{
			m_BatMap.insert({ m_iBatSN, new Bat(m_iBatSN) });
			m_iBatSN++;
			m_fBatSpawnTimer = 0.f;
		}
		// break
	case WolfPhase:
		m_fWolfSpawnTimer += m_fElapsedTime;

		if (m_fWolfSpawnTimer >= 5.f)
		{
			m_WolfMap.insert({ m_iWolfSN, new Wolf(m_iWolfSN)});
			m_iWolfSN++;
			m_fWolfSpawnTimer = 0.f;
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

		POINT location = { int(bat->GetLocation().x), int(bat->GetLocation().y) };
		WriteMonsterLocation(MonsterType::Bat, MonNum, location);

		CheckMonsterChangeState(bat, MonsterType::Bat, MonNum);
	}
	for (const auto& it : m_WolfMap)
	{
		int MonNum = it.first;
		Wolf* wolf = it.second;

		wolf->Update(m_fElapsedTime);

		POINT location = { int(wolf->GetLocation().x), int(wolf->GetLocation().y) };
		WriteMonsterLocation(MonsterType::Wolf, MonNum, location);

		CheckMonsterChangeState(wolf, MonsterType::Wolf, MonNum);
	}

	if (m_Papyrus)
	{
		m_Papyrus->Update(m_fElapsedTime);

		POINT location = { int(m_Papyrus->GetLocation().x), int(m_Papyrus->GetLocation().y) };
		WriteMonsterLocation(MonsterType::Papyrus, 0, location);

		CheckMonsterChangeState(m_Papyrus);
	}

	if (m_pCastle->IsOver())
	{
		m_bIsOver = Lose;
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
		Bat* bat = it.second;
		if (bat->GetStateType() == MonsterStateType::Move && IsCollision(m_pCastle->GetBB(), bat->GetBoundingBox()))
		{
			bat->ChangeState(MonsterAttackState::Instance());

		}
	}
	for (const auto& it : m_WolfMap)
	{
		Wolf* wolf = it.second;
		if (wolf->GetStateType() == MonsterStateType::Move && IsCollision(m_pCastle->GetBB(), wolf->GetBoundingBox()))
		{
			wolf->ChangeState(MonsterAttackState::Instance());
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

			WriteMonsterHp(MonsterType::Bat, SN, bat->GetCurrentHp());

			if (IsDead)
			{
				p->AddKillCount(MonsterType::Bat);
				WriteMonsterKill(MonsterType::Bat, p);

				delete bat;
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

			WriteMonsterHp(MonsterType::Wolf, SN, wolf->GetCurrentHp());

			if (IsDead)
			{
				p->AddKillCount(MonsterType::Wolf);
				WriteMonsterKill(MonsterType::Wolf, p);

				delete wolf;
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

			WriteBossHp();

			if (IsDead)
			{
				// TODO: 게임종료
				m_bIsOver = Win;
			}
		}
	}
}

void GameRoom::IsCollisionBoneWithPlayer(PlayerInfo* player)
{
	Bone** bone;

	bone = m_Papyrus->GetBone();
	for (int i = 0; i < 2; i++)
	{
		if (bone[i] && IsCollision(player->GetBB(), bone[i]->GetBoundingBox()))
		{
			//TODO: 플레이어 스턴

			bone[i]->SetCanDie(true);
		}
	}

	bone = m_Papyrus->GetMiniBone();
	for (int i = 0; i < 15; i++)
	{
		if (bone[i] && IsCollision(player->GetBB(), bone[i]->GetBoundingBox()))
		{
			//TODO: 플레이어 스턴

			bone[i]->SetCanDie(true);
		}
	}

	WriteBones();
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
		IsCollisionBoneWithPlayer(p);
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

void GameRoom::WriteMonsterLocation(MonsterType MT, BYTE id, POINT location)
{
	MonsterLocationMsg MSSM;
	MSSM.Type = MT;
	MSSM.SerialId = id;
	MSSM.Location = location;

	m_pStream->Write(StateMsgType::MonsterLocation);
	m_pStream->Write(MSSM);
}

void GameRoom::WriteCastleHp()
{
	m_pStream->Write(StateMsgType::CastleHp);
	m_pStream->Write(m_pCastle->GetCurrnetHp());
}

void GameRoom::WriteMonsterHp(MonsterType MT, BYTE SN, BYTE Hp)
{
	MonsterHpMsg MHSM;
	MHSM.SerialId = SN;
	MHSM.Type = MT;
	MHSM.Hp = Hp;

	m_pStream->Write(StateMsgType::MonsterHp);
	m_pStream->Write(MHSM);
}

void GameRoom::WriteBossHp()
{
	BossHpMsg BHM;
	BHM.Hp = m_Papyrus->GetCurrentHp();
	BHM.BreakCount= m_Papyrus->GetBreakCount();
	BHM.KnockDown = m_Papyrus->GetKnockDown();

	m_pStream->Write(StateMsgType::BossHp);
	m_pStream->Write(BHM);
}

void GameRoom::WriteBossState(BossStateType BST)
{
	BossStateMsg BPM;
	BPM.Pattern = BST;

	m_pStream->Write(StateMsgType::BossState);
	m_pStream->Write(BPM);
}

void GameRoom::WriteBones()
{
	Bone** bone;

	MonsterLocationMsg MLM;

	StateMsgType SMT = StateMsgType::MonsterLocation;

	bone = m_Papyrus->GetBone();
	for (int i = 0; i < 2; i++)
	{
		if (bone[i])
		{
			if (bone[i]->GetCanDie())
			{
				MLM.Location.x = -1;
				MLM.Location.y = -1;
			}
			else
			{
				MLM.Location.x = bone[i]->GetLocation().x;
				MLM.Location.y = bone[i]->GetLocation().y;
			}
			MLM.SerialId = bone[i]->GetSerialNum();
			MLM.Type = i == 0 ? MonsterType::UBBone : MonsterType::BBone1;

			m_pStream->Write(SMT);
			m_pStream->Write(MLM);
		}
	}

	bone = m_Papyrus->GetMiniBone();
	for (int i = 0; i < 15; i++)
	{
		if (bone[i])
		{
			if (bone[i]->GetCanDie())
			{
				MLM.Location.x = -1;
				MLM.Location.y = -1;
			}
			else
			{
				MLM.Location.x = bone[i]->GetLocation().x;
				MLM.Location.y = bone[i]->GetLocation().y;
			}
			MLM.SerialId = bone[i]->GetSerialNum();
			MLM.Type = MonsterType::BBone2;

			m_pStream->Write(SMT);
			m_pStream->Write(MLM);
		}
	}
}

void GameRoom::WriteMonsterKill(MonsterType MT, PlayerInfo* player)
{
	MonsterKillMsg MKM;
	MKM.PlayerId = player->GetPlayerNum();
	MKM.type = MT;

	m_pStream->Write(StateMsgType::MonsterKill);
	m_pStream->Write(MKM);
}

void GameRoom::WriteUseCard(UseCardStateMsg UCSM, int ClientNum)
{
	m_pStream->Write(StateMsgType::UseCard);
	m_pStream->Write(UCSM);
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

	//WriteUseCard(*UCSM, ClientNum);
}

void GameRoom::CheckMonsterChangeState(CommonMonster* monster, MonsterType MT, int SN)
{
	if (monster->GetCanAttack())
	{
		monster->SetCanAttack(false);

		WriteMonsterState(MT, SN, MonsterStateType::Attack);

		m_pCastle->GetDamage(monster->GetDamage());
		WriteCastleHp();
	}
	if (monster->GetChangedState())
	{
		monster->SetChangedState(false);

		WriteMonsterState(MT, SN, monster->GetStateType());
	}
}

void GameRoom::CheckMonsterChangeState(Papyrus* papyrus)
{
	if (papyrus->GetCanAttack())
	{
		papyrus->SetCanAttack(false);

		WriteBossState(papyrus->GetStateType());
	}
	if (papyrus->GetChangedState())
	{
		papyrus->SetChangedState(false);

		WriteBossState(papyrus->GetStateType());
	}
}

//===============================Getter================================
array<array<WORD, 3>, MAX_CLIENTS> GameRoom::GetKillCount()
{
	array<array<WORD, 3>, MAX_CLIENTS> ReturnValue;

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		ReturnValue[i] = m_pPlayerList[i]->GetKillCount();
	}

	return ReturnValue;
}
