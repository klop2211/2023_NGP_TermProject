#include "Common.h"
#include "MemoryReadStream.h"




StateMsgArgu* MemoryReadStream::GetStateMsg(StateMsgType smt, int* size)
{
	switch (smt)
	{
	case StateMsgType::MonsterSpawn:
		*size = sizeof(MonsterSpawnStateMsg);
		return new MonsterSpawnStateMsg();

	case StateMsgType::MonsterHp:
		*size = sizeof(MonsterHpStateMsg);
		return new MonsterHpStateMsg();

	case StateMsgType::MonsterState:
		*size = sizeof(MonsterStateMsg);
		return new MonsterStateMsg();

	case StateMsgType::PlayerLocation:
		*size = sizeof(PlayerLocationMsg);
		return new PlayerLocationMsg();

	case StateMsgType::CastleHp:
		*size = sizeof(CastleHpStateMsg);
		return new CastleHpStateMsg();

	case StateMsgType::UseCard:
		*size = sizeof(UseCardStateMsg);
		return new UseCardStateMsg();
	default:
		std::cout << "MemoryReadStream::GetStateMsg Err\n";
		return nullptr;
	}
}

void MemoryReadStream::Init()
{
	m_iNowReadIndex = 0;
	memset(buf, 0, STREAMBUFFERSIZE);
}
