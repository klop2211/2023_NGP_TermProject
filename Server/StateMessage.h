#pragma once
enum class MonsterType : BYTE { Wolf, Bat, Papyrus };
enum class PlayerMove : BYTE {};
enum class CardType : BYTE {};
enum class StateMsgType : BYTE {MonsterSpawn, MonsterHp, MonsterState, PlayerLocation, CastleHp, UseCard, GameStart};
enum class MonsterStateType : BYTE {Move, Attack, Ice, Fire};
enum class PStateName { Move, Stay, Stun, Skill };

// �޼����� ��� ����, �̰ź��� ������ ���� ���� �� �� ����
typedef BYTE StateMsgByte;

// StateMsg ���� ó��
struct StateMsgArgu
{
	// dynamic cast�� ����
	virtual void Func() {};
};

// ���� ���� : *
// �۽� ���� : /

// ���� -> Ŭ�� /
struct MonsterSpawnStateMsg : StateMsgArgu
{
	MonsterType Type;
	BYTE SerialId;
};

// ���� -> Ŭ�� (�浹ó�� �� ����)
struct MonsterHpStateMsg : StateMsgArgu
{
	MonsterType Type;
	BYTE SerialId;
	BYTE Damage;
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
struct UseCardStateMsg : StateMsgArgu
{
	BYTE PlayerId;
	CardType card;
	//int Tripord[][4];
	//BYTE damage;
};

// ���� -> Ŭ�� /
struct CastleHpStateMsg : StateMsgArgu
{
	int Hp;
};

// �������� �迭�� �����ϱ�����
struct StateMsgInfo
{
	StateMsgByte StateMsg;
	StateMsgArgu* pStateMsgArgu;
};