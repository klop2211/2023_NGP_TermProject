#pragma once
#include "../Server/StateMessage.h"
#include "../MemStream/StreamGlobal.h"

#include <queue>

class MemoryReadStream
{
public:
	MemoryReadStream(const SOCKET& socket)
		: m_Socket(socket),
		m_iNowReadIndex(0)
	{
		Init();
	};

	void Read(std::queue<StateMsgInfo>& q, bool&);
	StateMsgType GetMsgType();

	StateMsgArgu* GetStateMsg(StateMsgType, int&);

	void Init();
private:
	// 수신용 버퍼
	char buf[STREAMBUFFERSIZE];

	// 스트림 Write에 적을 인덱스 위치
	int m_iNowReadIndex;

	// buf에 담긴 바이트 수
	int m_iBufSize;

	// 소켓
	SOCKET m_Socket;
};
