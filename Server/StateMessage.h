#pragma once
enum class MonsterType : BYTE { Wolf, Bat, Papyrus };
enum class PlayerMove : BYTE {};
enum class CardType : BYTE {};
enum class StateMsgType : BYTE {MonsterSpawn, MonsterHp, MonsterState, PlayerMove, CastleHp, UseCard, GameStart};
enum class MonsterStateType : BYTE {Move, Attack, Ice, Fire};

// StateMsg ���� ó��
struct StateMsgArgu {};

// ���� -> Ŭ��
struct MonsterSpawnStateMsg : StateMsgArgu
{
	MonsterType MonsterId;
	BYTE MonsterSerialId;
};

// ���� -> Ŭ�� (�浹ó�� �� ����)
struct MonsterHpStateMsg : StateMsgArgu
{
	MonsterType MonsterId;
	BYTE MonsterSerialId;
	BYTE Damage;
};

struct MonsterStateMsg : StateMsgArgu
{
	MonsterType MonsterId;
	BYTE MonsterSerialId;
	MonsterStateType MonsterState;
};

// ���� <-> Ŭ��
struct PlayerMoveStateMsg : StateMsgArgu
{
	BYTE PlayerId;
	PlayerMove pMove;
};

// ���� <-> Ŭ��
struct UseCardStateMsg : StateMsgArgu
{
	BYTE PlayerId;
	CardType card;
};

// ���� -> Ŭ��
struct CastleHpStateMsg : StateMsgArgu
{
	BYTE Hp;
};

struct StateMsgInfo
{
	StateMsgByte StateMsg;
	StateMsgArgu* pStateMsgArgu;
};