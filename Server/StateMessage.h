#pragma once
enum class MonsterType : BYTE { Wolf, Bat, Papyrus };
enum class PlayerMove : BYTE {};
enum class CardType : BYTE {};
enum class StateMsgType : BYTE {MonsterSpawn, MonsterHp, MonsterState, PlayerMove, CastleHp, UseCard, GameStart};
enum class MonsterStateType : BYTE {Move, Attack, Ice, Fire};

// �޼����� ��� ����, �̰ź��� ������ ���� ���� �� �� ����
typedef BYTE StateMsgByte;

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
	MonsterType Type;
	BYTE SerialId;
	BYTE Damage;
};

// ���� -> Ŭ��
struct MonsterStateMsg : StateMsgArgu
{
	MonsterType Type;
	BYTE SerialId;
	MonsterStateType State;
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