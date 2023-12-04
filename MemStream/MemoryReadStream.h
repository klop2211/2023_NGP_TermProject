#pragma once
#include "../Server/StateMessage.h"
#include "../MemStream/StreamGlobal.h"

#include <queue>

class MemoryReadStream
{
public:
	MemoryReadStream()
		: m_iNowReadIndex(0)
	{
		Init();
	};

	void Read(const SOCKET& socket, std::queue<StateMsgInfo>& q, bool&);
	StateMsgType GetMsgType();

	StateMsgArgu* GetStateMsg(StateMsgType, int&);

	void Init();
private:
	// 수신용 버퍼
	char buf[STREAMBUFFERSIZE];

	// 스트림 Write에 적을 인덱스 위치
	int m_iNowReadIndex;
};
