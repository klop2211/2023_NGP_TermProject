#pragma once
enum class MonsterType : BYTE { Wolf, Bat, Papyrus };
enum class PlayerMove : BYTE {};
enum class CardType : BYTE {};
enum class StateMsgType : BYTE {MonsterSpawn, MonsterHp, PlayerMove, CastleHp, UseCard};

// StateMsg ���� ó��
struct StateMsgArgu {};

// ���� -> Ŭ��
struct MonsterSpawnStateMsg : StateMsgArgu
{
	MonsterType MonsterId;
	int MonsterSerialId;
};

// ���� -> Ŭ�� (�浹ó�� �� ����)
struct MonsterHpStateMsg : StateMsgArgu
{
	MonsterType MonsterId;
	int MonsterSerialId;
	int Damage;
};

// ���� <-> Ŭ��
struct PlayerMoveStateMsg : StateMsgArgu
{
	int PlayerId;
	PlayerMove pMove;
};

// ���� <-> Ŭ��
struct UseCardStateMsg : StateMsgArgu
{
	int PlayerId;
	CardType card;
};

// ���� -> Ŭ��
struct CastleHpStateMsg : StateMsgArgu
{
	int Hp;
};

struct StateMsgInfo
{
	StateMsgByte StateMsg;
	StateMsgArgu* pStateMsgArgu;
};