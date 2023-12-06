#pragma once
#include "Common.h"

enum class MonsterType : BYTE { Wolf, Bat, Papyrus, END };
enum class CardType : BYTE { N_rhlddufvk, N_sktjsckd, N_dbtjdrkdcjs, N_wjrfydvh, N_aodfyddufvk, N_qksdnjftja, N_dusghkstja, N_cjdfydwls, N_cjdfydcnftn, N_ghltjsckd, N_dmsgkdbtjdxks };
enum class StateMsgType : BYTE {MonsterLocation, MonsterHp, MonsterState, PlayerLocation, CastleHp, UseCard, GameStart, BossState, BossHp, GameOver};
enum class MonsterStateType : BYTE {Move, Attack, Ice, Fire};
enum class BossStateType : BYTE { Move, UBPattern, BPattern1, BPattern2, CantMove };
enum class PStateName : BYTE { Move, Stay, Stun, Skill };

// �޼����� ��� ����, �̰ź��� ������ ���� ���� �� �� ����
//typedef BYTE StateMsgByte;

// StateMsg ���� ó��
struct StateMsgArgu
{
	// dynamic cast�� ����
	//virtual void Func() {};
};

// ���� ���� : *
// �۽� ���� : /

// ���� -> Ŭ�� /
struct MonsterLocationMsg : StateMsgArgu
{
	MonsterType Type;
	BYTE SerialId;
	POINT Location;
};

// ���� -> Ŭ�� (�浹ó�� �� ����)
struct MonsterHpMsg : StateMsgArgu
{
	MonsterType Type;
	BYTE SerialId;
	BYTE Hp;
};

// ���� -> Ŭ�� /
struct MonsterStateMsg : StateMsgArgu
{
	MonsterType Type;
	BYTE SerialId;
	MonsterStateType State;
};

// ���� <-> Ŭ�� /*
struct PlayerLocationMsg : StateMsgArgu
{
	BYTE PlayerId;
	POINT Location;
	PStateName State;
	BYTE Direction;
};

// ���� <-> Ŭ�� 
struct PlayerTripordMsg : StateMsgArgu
{
	BYTE PlayerId;
	CardType Card;
	BYTE Tripord[3];
};

// ���� <-> Ŭ��
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

// ���� -> Ŭ�� /
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

// ����->Ŭ��
struct GameOverMsg : StateMsgArgu
{
	array<array<WORD, (int)MonsterType::END>, MAX_CLIENTS> KillScore;
};

// �������� �迭�� �����ϱ�����
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