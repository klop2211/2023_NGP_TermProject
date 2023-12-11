#include "Common.h"
#include "GameRoom.h"

#include "Wolf.h"
#include "Bat.h"
#include "Papyrus.h"
#include "MonsterState.h"
#include "Castle.h"
#include "Bone.h"
#include "../NGP_TermProject/SkillObject.h"
#include "SkillObject.h"

#include "PlayerInfo.h"
#include "../MemStream/MemoryWriteStream.h"

#include <algorithm>

GameRoom::GameRoom(array<SOCKET, MAX_CLIENTS>& ClientSocket) :
	m_iWolfSN(0),
	m_iBatSN(0),
	m_iPhase(GameRoom::WolfPhase),
	m_Papyrus(nullptr),
	m_bIsOver(NotYet),
	m_fPhaseInitTimer(15.f)
{
	m_fPhaseChangeTimer = m_fPhaseInitTimer;
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

void GameRoom::Update(array<queue<StateMsgInfo>, MAX_CLIENTS>& StateMsg)
{

	SetElapsedTime();
	UpdateUseStateMsg(StateMsg);
	SpawnEnemy();
	UpdateEnemy();
	DoCollisionCheck();

	WritePlayerLocation();
	
	DoGarbageCollector();

	m_pStream->Send();
}

void GameRoom::SpawnEnemy()
{
	// 페이즈 변화
	m_fPhaseChangeTimer -= m_fElapsedTime;
	if (m_fPhaseChangeTimer < 0.f)
	{
		m_fPhaseChangeTimer = m_fPhaseInitTimer;
		++m_iPhase;
		std::clamp(m_iPhase, 0, (int)PhaseEnum::BossPhase);
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

void GameRoom::DoGarbageCollector()
{
	for (auto it = m_WolfMap.begin(); it != m_WolfMap.end();) {
		if (it->second->GetCanDie())
		{ // 특정 조건에 따라 요소를 삭제하고자 할 때
			it = m_WolfMap.erase(it);
		}
		else {
			++it;
		}
	}
	for (auto it = m_BatMap.begin(); it != m_BatMap.end();) {
		if (it->second->GetCanDie())
		{ // 특정 조건에 따라 요소를 삭제하고자 할 때
			it = m_BatMap.erase(it);
		}
		else {
			++it;
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
		std::vector<int> CollisionList = p->GetCollisionList((int)MonsterType::Bat);
		bool NotInList = std::find(CollisionList.begin(), CollisionList.end(), SN) == CollisionList.end();

		if (NotInList && IsCollision(p->GetBB(), bat->GetBoundingBox()))
		{
			bool IsDead = bat->GetDamageAndIsDead(
				p->GetDamage(),
				0, 0, 0,
				p->GetType());

			CollisionList.push_back(SN);
			WriteMonsterHp(MonsterType::Bat, SN, bat->GetCurrentHp());

			if (IsDead)
			{
				p->AddKillCount(MonsterType::Bat);
				WriteMonsterKill(MonsterType::Bat, SN, p);
				bat->SetCanDie(true);
			}
		}
	}
	for (const auto& it : m_WolfMap)
	{
		int SN = it.first;
		Wolf* wolf = it.second;
		std::vector<int> CollisionList = p->GetCollisionList((int)MonsterType::Wolf);
		bool NotInList = std::find(CollisionList.begin(), CollisionList.end(), SN) == CollisionList.end();

		if (NotInList && IsCollision(p->GetBB(), wolf->GetBoundingBox()))
		{
			bool IsDead = wolf->GetDamageAndIsDead(
				p->GetDamage(),
				0, 0, 0,
				p->GetType());

			CollisionList.push_back(SN);
			WriteMonsterHp(MonsterType::Wolf, SN, wolf->GetCurrentHp());

			if (IsDead)
			{
				p->AddKillCount(MonsterType::Wolf);
				WriteMonsterKill(MonsterType::Wolf, SN, p);
				wolf->SetCanDie(true);
			}
		}
	}

	if (m_Papyrus)
	{
		std::vector<int> CollisionList = p->GetCollisionList((int)MonsterType::Papyrus);
		bool NotInList = std::find(CollisionList.begin(), CollisionList.end(), 0) == CollisionList.end();

		if (NotInList && IsCollision(p->GetBB(), m_Papyrus->GetBoundingBox()))
		{
			bool IsDead = m_Papyrus->GetDamageAndIsDead(
				p->GetDamage(),
				p->GetStunDamage(),
				p->GetDestuction(),
				p->GetNamedDamage(),
				p->GetType());

			CollisionList.push_back(0);
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
	if (!m_Papyrus)
	{
		return;
	}

	Bone** bone;

	bone = m_Papyrus->GetBone();
	for (int i = 0; i < 2; i++)
	{
		if (bone[i] && IsCollision(player->GetBB(), bone[i]->GetBoundingBox()))
		{
			//TODO: 플레이어 스턴
			player->SetState(PStateName::Stun);
			bone[i]->SetCanDie(true);
		}
	}

	bone = m_Papyrus->GetMiniBone();
	for (int i = 0; i < 15; i++)
	{
		if (bone[i] && IsCollision(player->GetBB(), bone[i]->GetBoundingBox()))
		{
			//TODO: 플레이어 스턴
			player->SetState(PStateName::Stun);
			bone[i]->SetCanDie(true);
		}
	}

	WriteBones();
}

void GameRoom::CollisionSkillObject()
{
	for (auto& SkillObject : m_SkillObject )
	{
		SkillObjectInfo* SOI = SkillObject.second;

		for (const auto& it : m_WolfMap)
		{
			int SN = it.first;
			Wolf* wolf = it.second;
			std::vector<int> CollisionList = SOI->GetCollisionList((int)MonsterType::Wolf);

			if (std::find(CollisionList.begin(), CollisionList.end(), SN) == CollisionList.end()
				&& IsCollision(SOI->GetBoundingBox(), wolf->GetBoundingBox()))
			{
				CollisionList.push_back(SN);
				DamageToMonsterUsingSkillObject(SOI, wolf);
			}
		}
		for (const auto& it : m_BatMap)
		{
			int SN = it.first;
			Bat* bat = it.second;
			std::vector<int> CollisionList = SOI->GetCollisionList((int)MonsterType::Bat);

			if (std::find(CollisionList.begin(), CollisionList.end(), SN) == CollisionList.end()
				&& IsCollision(SOI->GetBoundingBox(), bat->GetBoundingBox()))
			{
				CollisionList.push_back(SN);
				DamageToMonsterUsingSkillObject(SOI, bat);
			}
		}
		if (m_Papyrus)
		{
			std::vector<int> CollisionList = SOI->GetCollisionList((int)MonsterType::Papyrus);

			if (std::find(CollisionList.begin(), CollisionList.end(), 0) == CollisionList.end()
				&& IsCollision(SOI->GetBoundingBox(), m_Papyrus->GetBoundingBox()))
			{
				CollisionList.push_back(0);
				DamageToMonsterUsingSkillObject(SOI, m_Papyrus);
			}
		}
	}
}

void GameRoom::DoCollisionCheck()
{
	// TODO: Collision Group으로 개선 필요
	for (const auto& p : m_pPlayerList)
	{
		IsCollisionMonsterWithPlayer(p);
		IsCollisionBoneWithPlayer(p);
	}
	CollisionSkillObject();
	IsCollisionMonsterWithCastle();
}

void GameRoom::DamageToMonsterUsingSkillObject(SkillObjectInfo* SOI, Monster* monster)
{
	PlayerInfo* OwnedPlayer = m_pPlayerList[SOI->GetOwnedClientNum()];
	switch (SOI->GetObjectType())
	{
		// OVERLAP
	case Drop_Spear:

	case Meteor_Spear:

	case Explosion:

	case Hurricane:

	case Knockdown:

	case SowrdLight:

	case Rotation_Spear:

	case Airborne_Spear1:

	case Airborne_Spear2:

	case Airborne_Spear3:

	case Red_Spear:

	case Earthquake:

	case Flame_Zone:

	case Drop_Red_Spear1:

	case Drop_Red_Spear2:

	case Yellow_Spear:

	case Purple_Spear:

	case Ulti_Spear:

	case Ulti_Explosion:
	{
		bool IsDead = monster->GetDamageAndIsDead(OwnedPlayer->GetDamage(),
									OwnedPlayer->GetStunDamage(),
									OwnedPlayer->GetDestuction(),
									OwnedPlayer->GetNamedDamage(),
									OwnedPlayer->GetType());
		if(IsDead)
		{
			OwnedPlayer->AddKillCount(monster->GetMonsterType());
		}
	}
		break;
		// STATUS EFFECT
	case Ice:
		break;
	case Fire:
		break;
	case None:
		break;
		// BLOCKING
	case Wall:
		break;
	default:
		break;
	}
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

void GameRoom::UpdateUseStateMsg(array<queue<StateMsgInfo>, MAX_CLIENTS>& StateMsg)
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
			case StateMsgType::SkillObjectLocation:
				ReadSkillObjectLocation(SMI.pStateMsgArgu);
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

void GameRoom::WriteMonsterKill(MonsterType MT, BYTE Serial, PlayerInfo* player)
{
	MonsterKillMsg MKM;
	MKM.PlayerId = player->GetPlayerNum();
	MKM.SerialId = Serial;
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
	//m_pPlayerList[ClientNum]->SetShouldCollisionCheck(false);
	//m_pPlayerList[ClientNum]->SetAllCardProperty(0, 0, 0, 0, 0);
}

void GameRoom::ReadUseCard(StateMsgArgu* SMA)
{
	UseCardStateMsg* UCSM = (UseCardStateMsg*)SMA;
	int ClientNum = UCSM->PlayerId;

	// 충돌처리 on
	//m_pPlayerList[ClientNum]->SetShouldCollisionCheck(true);
	m_pPlayerList[ClientNum]->SetAllCardProperty(
		UCSM->Damage,
		UCSM->StunDamage,
		UCSM->Destuction,
		UCSM->NamedDamage,
		UCSM->Type
	);

	// 스킬사용이 끝날때 0을 보낸다
	if (UCSM->Damage == 0)
	{
		m_pPlayerList[ClientNum]->InitCollisionList();
	}

	WriteUseCard(*UCSM, ClientNum);
}

void GameRoom::ReadSkillObjectLocation(StateMsgArgu* SMA)
{
	// SkillOBject의 일련번호는 Player번호 * 100 + (int)ObjectType으로 할 예정
	SkillObjectLocationMsg* SOLM = (SkillObjectLocationMsg*)SMA;
	int SerialNum = SOLM->PlayerId * 100 + SOLM->ObjectType;

	if (SOLM->Location.x == 0 && SOLM->Location.y == 0)
	{
		delete m_SkillObject[SerialNum];
		m_SkillObject.erase(SerialNum);
	}
	else if(m_SkillObject.find(SerialNum) == m_SkillObject.end())
	{
		SkillObjectInfo* SOI = new SkillObjectInfo(SOLM->PlayerId, (ObjectType)SOLM->ObjectType, SOLM->Location, SOLM->Size);
		m_SkillObject.insert({ SerialNum, SOI });
	}
	else
	{
		m_SkillObject[SerialNum]->SetLocation(FPOINT(SOLM->Location.x, SOLM->Location.y));
	}
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
