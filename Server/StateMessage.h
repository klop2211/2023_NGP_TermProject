#pragma once
enum class MonsterType : BYTE { Wolf, Bat, Papyrus };
enum class PlayerMove : BYTE {};
enum class CardType : BYTE {};
enum class StateMsgType : BYTE {MonsterSpawn, MonsterHp, MonsterState, PlayerLocation, CastleHp, UseCard, GameStart};
enum class MonsterStateType : BYTE {Move, Attack, Ice, Fire};
enum class PStateName { Move, Stay, Stun, Skill };

// 메세지의 헤더 역할, 이거보고 다음에 뭐가 올지 알 수 있음
typedef BYTE StateMsgByte;

// StateMsg 로직 처리
struct StateMsgArgu
{
	// dynamic cast를 위해
	virtual void Func() {};
};

// 수신 구현 : *
// 송신 구현 : /

// 서버 -> 클라 /
struct MonsterSpawnStateMsg : StateMsgArgu
{
	MonsterType Type;
	BYTE SerialId;
};

// 서버 -> 클라 (충돌처리 후 전송)
struct MonsterHpStateMsg : StateMsgArgu
{
	MonsterType Type;
	BYTE SerialId;
	BYTE Damage;
};

// 서버 -> 클라 /
struct MonsterStateMsg : StateMsgArgu
{
	MonsterType Type;
	BYTE SerialId;
	MonsterStateType State;
};

// 서버 <-> 클라 /*
struct PlayerLocationMsg : StateMsgArgu
{
	BYTE PlayerId;
	POINT Location;
	PStateName State;
	BYTE Direction;
};

// 서버 <-> 클라
struct UseCardStateMsg : StateMsgArgu
{
	BYTE PlayerId;
	CardType card;
	//int Tripord[][4];
	//BYTE damage;
};

// 서버 -> 클라 /
struct CastleHpStateMsg : StateMsgArgu
{
	int Hp;
};

// 서버에서 배열로 관리하기위해
struct StateMsgInfo
{
	StateMsgByte StateMsg;
	StateMsgArgu* pStateMsgArgu;
};