#include "../Server/Common.h"
#include "MemoryReadStream.h"



void MemoryReadStream::Read(std::queue<StateMsgInfo>& q, bool& OverCheck)
{
	int retval;
	int BufSize;
	retval = recv(m_Socket, (char*)&BufSize, sizeof(int), MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		err_quit("MemoryReadStream::Read bufsize Err");
	}
	retval = recv(m_Socket, (char*)buf, BufSize, MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		err_quit("MemoryReadStream::Read buf Err");
	}

	while (m_iNowReadIndex < BufSize)
	{
		StateMsgType SMT = GetMsgType();
		StateMsgArgu* pSMA = GetStateMsg(SMT);

		q.push(StateMsgInfo( SMT, pSMA ));
	}
}

StateMsgType MemoryReadStream::GetMsgType()
{
	StateMsgType SMT;
	memcpy(&SMT, buf + m_iNowReadIndex, sizeof(StateMsgType));
	m_iNowReadIndex += sizeof(StateMsgType);

	return SMT;
}

StateMsgArgu* MemoryReadStream::GetStateMsg(StateMsgType smt)
{
	switch (smt)
	{
	case StateMsgType::MonsterSpawn:
		m_iNowReadIndex += sizeof(MonsterSpawnStateMsg);
		return new MonsterSpawnStateMsg();

	case StateMsgType::MonsterHp:
		m_iNowReadIndex += sizeof(MonsterHpStateMsg);
		return new MonsterHpStateMsg();

	case StateMsgType::MonsterState:
		m_iNowReadIndex += sizeof(MonsterStateMsg);
		return new MonsterStateMsg();

	case StateMsgType::PlayerLocation:
		m_iNowReadIndex += sizeof(PlayerLocationMsg);
		return new PlayerLocationMsg();

	case StateMsgType::CastleHp:
		m_iNowReadIndex += sizeof(CastleHpStateMsg);
		return new CastleHpStateMsg();

	case StateMsgType::UseCard:
		m_iNowReadIndex += sizeof(UseCardStateMsg);
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
