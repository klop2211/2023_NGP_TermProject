#include "../Server/Common.h"
#include "MemoryReadStream.h"



void MemoryReadStream::Read(const SOCKET& socket, 
	std::queue<StateMsgInfo>& q, bool& OverCheck)
{
	int retval;
	int BufSize;
	retval = recv(socket, (char*)&BufSize, sizeof(int), MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		err_quit("MemoryReadStream::Read bufsize Err");
	}
	retval = recv(socket, (char*)buf, BufSize, MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		err_quit("MemoryReadStream::Read buf Err");
	}

	while (m_iNowReadIndex < BufSize)
	{
		int Size = 0;
		StateMsgType SMT = GetMsgType();
		m_iNowReadIndex += sizeof(StateMsgType);

		StateMsgArgu* pSMA = GetStateMsg(SMT, Size);
		memcpy(pSMA, buf + m_iNowReadIndex, Size);
		m_iNowReadIndex += Size;

		q.push(StateMsgInfo( SMT, pSMA ));
	}

	Init();
}

StateMsgType MemoryReadStream::GetMsgType()
{
	StateMsgType SMT;
	memcpy(&SMT, buf + m_iNowReadIndex, sizeof(StateMsgType));

	return SMT;
}

StateMsgArgu* MemoryReadStream::GetStateMsg(StateMsgType smt, int& size)
{
	switch (smt)
	{
	case StateMsgType::MonsterLocation:
		size = sizeof(MonsterLocationMsg);
		return new MonsterLocationMsg();

	case StateMsgType::MonsterHp:
		size = sizeof(MonsterHpMsg);
		return new MonsterHpMsg();

	case StateMsgType::MonsterState:
		size= sizeof(MonsterStateMsg);
		return new MonsterStateMsg();

	case StateMsgType::PlayerLocation:
		size= sizeof(PlayerLocationMsg);
		return new PlayerLocationMsg();

	case StateMsgType::CastleHp:
		size= sizeof(CastleHpStateMsg);
		return new CastleHpStateMsg();

	case StateMsgType::UseCard:
		size= sizeof(UseCardStateMsg);
		return new UseCardStateMsg();

	case StateMsgType::BossState:
		size = sizeof(BossStateMsg);
		return new BossStateMsg();

	case StateMsgType::SkillObjectLocation:
		size = sizeof(SkillObjectLocationMsg);
		return new SkillObjectLocationMsg();
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
