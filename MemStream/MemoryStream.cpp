#include "../Server/Common.h"
#include "MemoryStream.h"


void MemoryStream::Read(const SOCKET& s, std::queue<StateMsgInfo>& q, bool& isOver)
{
	int retval;
	int BufSize;
	int NowReadIndex = 0;

	retval = recv(s, (char*)&BufSize, sizeof(int), MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		err_quit("MemoryReadStream::Read bufsize Err");
	}
	retval = recv(s, (char*)buf, BufSize, MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		err_quit("MemoryReadStream::Read buf Err");
	}

	while (NowReadIndex < BufSize)
	{
		int Size = 0;
		StateMsgType SMT = GetMsgType(NowReadIndex);
		NowReadIndex += sizeof(StateMsgType);

		StateMsgArgu* pSMA = GetStateMsg(SMT, Size);
		memcpy(pSMA, buf + NowReadIndex, Size);
		NowReadIndex += Size;

		q.push(StateMsgInfo(SMT, pSMA));
	}
	Init();
}

void MemoryStream::Send(const SOCKET& s)
{
	SendData(s);
	Init();
}

void MemoryStream::Send(array<SOCKET, MAX_CLIENTS>& sockets)
{
	for (const auto& s : sockets)
	{
		SendData(s);
	}
	Init();
}

void MemoryStream::SendData(const SOCKET& s)
{
	int retval;
	memmove(buf + sizeof(int), buf, m_iNowWriteIndex);
	memcpy(buf, &m_iNowWriteIndex, sizeof(int));
	for (const auto& s : m_Sockets)
	{
		retval = send(s, buf, m_iNowWriteIndex + sizeof(int), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
		}
	}
}

StateMsgType MemoryStream::GetMsgType(const int& index)
{
	StateMsgType SMT;
	memcpy(&SMT, buf + index, sizeof(StateMsgType));

	return SMT;
}

StateMsgArgu* MemoryStream::GetStateMsg(StateMsgType smt, int& size)
{
	switch (smt)
	{
	case StateMsgType::MonsterSpawn:
		size = sizeof(MonsterSpawnStateMsg);
		return new MonsterSpawnStateMsg();

	case StateMsgType::MonsterHp:
		size = sizeof(MonsterHpStateMsg);
		return new MonsterHpStateMsg();

	case StateMsgType::MonsterState:
		size = sizeof(MonsterStateMsg);
		return new MonsterStateMsg();

	case StateMsgType::PlayerLocation:
		size = sizeof(PlayerLocationMsg);
		return new PlayerLocationMsg();

	case StateMsgType::CastleHp:
		size = sizeof(CastleHpStateMsg);
		return new CastleHpStateMsg();

	case StateMsgType::UseCard:
		size = sizeof(UseCardStateMsg);
		return new UseCardStateMsg();
	default:
		std::cout << "MemoryReadStream::GetStateMsg Err\n";
		return nullptr;
	}
}

void MemoryStream::Init()
{
	m_iNowWriteIndex = 0;
	memset(buf, 0, STREAMBUFFERSIZE);
}
