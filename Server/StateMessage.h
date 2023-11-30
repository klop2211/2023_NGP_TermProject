#pragma once
enum class MonsterType : BYTE { Wolf, Bat, Papyrus };
enum class PlayerMove : BYTE {};
enum class CardType : BYTE {};
enum class StateMsgType : BYTE {MonsterSpawn, MonsterHp, PlayerMove, CastleHp, UseCard};

// StateMsg 로직 처리
struct StateMsgArgu {};

// 서버 -> 클라
struct MonsterSpawnStateMsg : StateMsgArgu
{
	MonsterType MonsterId;
	int MonsterSerialId;
};

// 서버 -> 클라 (충돌처리 후 전송)
struct MonsterHpStateMsg : StateMsgArgu
{
	MonsterType MonsterId;
	int MonsterSerialId;
	int Damage;
};

// 서버 <-> 클라
struct PlayerMoveStateMsg : StateMsgArgu
{
	int PlayerId;
	PlayerMove pMove;
};

// 서버 <-> 클라
struct UseCardStateMsg : StateMsgArgu
{
	int PlayerId;
	CardType card;
};

// 서버 -> 클라
struct CastleHpStateMsg : StateMsgArgu
{
	int Hp;
};

struct StateMsgInfo
{
	StateMsgByte StateMsg;
	StateMsgArgu* pStateMsgArgu;
};