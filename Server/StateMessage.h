#pragma once
enum class MonsterType : BYTE { Wolf, Bat, Papyrus };
enum class PlayerMove : BYTE {};
enum class CardType : BYTE {};
enum class StateMsgType : BYTE {MonsterSpawn, MonsterHp, MonsterState, PlayerMove, CastleHp, UseCard, GameStart};
enum class MonsterStateType : BYTE {Move, Attack, Ice, Fire};

// StateMsg 로직 처리
struct StateMsgArgu {};

// 서버 -> 클라
struct MonsterSpawnStateMsg : StateMsgArgu
{
	MonsterType MonsterId;
	BYTE MonsterSerialId;
};

// 서버 -> 클라 (충돌처리 후 전송)
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

// 서버 <-> 클라
struct PlayerMoveStateMsg : StateMsgArgu
{
	BYTE PlayerId;
	PlayerMove pMove;
};

// 서버 <-> 클라
struct UseCardStateMsg : StateMsgArgu
{
	BYTE PlayerId;
	CardType card;
};

// 서버 -> 클라
struct CastleHpStateMsg : StateMsgArgu
{
	BYTE Hp;
};

struct StateMsgInfo
{
	StateMsgByte StateMsg;
	StateMsgArgu* pStateMsgArgu;
};