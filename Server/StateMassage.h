#pragma once
enum class MonsterType : BYTE { Wolf, Bat, Papyrus };
enum class PlayerMove : BYTE {};
enum class CardType : BYTE {};

// StateMsg ���� ó��
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
