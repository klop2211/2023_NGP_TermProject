#pragma once
enum class MonsterType : BYTE { Wolf, Bat, Papyrus };
enum class PlayerMove : BYTE {};
enum class CardType : BYTE {};
enum class StateMsgType : BYTE {MonsterSpawn, MonsterHp, PlayerMove, CastleHp, UseCard};

// StateMsg 로직 처리
struct StateMsgArgu {};

struct MonsterSpawnStateMsg : StateMsgArgu
{
	MonsterType MonsterId;
	int MonsterSerialId;
};
struct MonsterHpStateMsg : StateMsgArgu
{
	MonsterType MonsterId;
	int MonsterSerialId;
	int Damage;
};
struct PlayerMoveStateMsg : StateMsgArgu
{
	int PlayerId;
	PlayerMove pMove;
};
struct UseCardStateMsg : StateMsgArgu
{
	int PlayerId;
	CardType card;
};
struct CastleHpStateMsg : StateMsgArgu
{
	int Hp;
};

struct StateMsgInfo
{
	StateMsgByte StateMsg;
	StateMsgArgu* pStateMsgArgu;
};