#pragma once
#include "Common.h"

enum class MonsterType : BYTE { Wolf, Bat, Papyrus, END };
enum class CardType : BYTE { N_rhlddufvk, N_sktjsckd, N_dbtjdrkdcjs, N_wjrfydvh, N_aodfyddufvk, N_qksdnjftja, N_dusghkstja, N_cjdfydwls, N_cjdfydcnftn, N_ghltjsckd, N_dmsgkdbtjdxks };
enum class StateMsgType : BYTE {MonsterLocation, MonsterHp, MonsterState, PlayerLocation, CastleHp, UseCard, GameStart, BossState, BossHp, GameOver};
enum class MonsterStateType : BYTE {Move, Attack, Ice, Fire};
enum class BossStateType : BYTE { Move, UBPattern, BPattern1, BPattern2, CantMove };
enum class PStateName : BYTE { Move, Stay, Stun, Skill };

// 메세지의 헤더 역할, 이거보고 다음에 뭐가 올지 알 수 있음
//typedef BYTE StateMsgByte;

// StateMsg 로직 처리
struct StateMsgArgu
{
	// dynamic cast를 위해
	//virtual void Func() {};
};

// 수신 구현 : *
// 송신 구현 : /

// 서버 -> 클라 /
struct MonsterLocationMsg : StateMsgArgu
{
	MonsterType Type;
	BYTE SerialId;
	POINT Location;
};

// 서버 -> 클라 (충돌처리 후 전송)
struct MonsterHpMsg : StateMsgArgu
{
	MonsterType Type;
	BYTE SerialId;
	BYTE Hp;
};

// 서버 -> 클라 /
struct MonsterStateMsg : StateMsgArgu
{
	MonsterType Type;
	BYTE SerialId;
	MonsterStateType State;
};

// 서버 <-> 클라 /*
struct PlayerLocationMsg : StateMsgArgu
{
	BYTE PlayerId;
	POINT Location;
	PStateName State;
	BYTE Direction;
};

// 서버 <-> 클라 
struct PlayerTripordMsg : StateMsgArgu
{
	BYTE PlayerId;
	CardType Card;
	BYTE Tripord[3];
};

// 서버 <-> 클라
struct UseCardStateMsg : StateMsgArgu
{
	BYTE PlayerId;
	CardType Card;

	BYTE Damage;
	BYTE StunDamage;
	BYTE Destuction;
	BYTE NamedDamage;	
	BYTE Type;	

	BYTE Tripord[4];
};

// 서버 -> 클라 /
struct CastleHpStateMsg : StateMsgArgu
{
	int Hp;
};

struct BossHpMsg : StateMsgArgu
{
	BYTE Hp;
	BYTE BreakCount;
	BYTE KnockDown;
};

struct BossStateMsg : StateMsgArgu
{
	BossStateType Pattern;
};

// 서버->클라
struct GameOverMsg : StateMsgArgu
{
	array<array<WORD, (int)MonsterType::END>, MAX_CLIENTS> KillScore;
};

// 서버에서 배열로 관리하기위해
struct StateMsgInfo
{
	StateMsgInfo() {};
	StateMsgInfo(StateMsgType smt, StateMsgArgu* sma)
	{
		StateMsg = smt;
		pStateMsgArgu = sma;
	}

	StateMsgType StateMsg;
	StateMsgArgu* pStateMsgArgu;
};