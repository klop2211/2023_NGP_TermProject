#pragma once
enum class MonsterType { Wolf, Bat, Papyrus };
enum class PlayerMove {};
enum class CardType {};

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
	int Hp;
};
struct PlayerMoveStateMsg : StateMsgArgu
{
	int PlayerId;
	PlayerMove pMove;
};
struct MonsterUseCardStateMsg : StateMsgArgu
{
	int PlayerId;
	CardType card;
};
struct CastleHpStateMsg : StateMsgArgu
{
	int Hp;
};
