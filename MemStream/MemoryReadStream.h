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

	template<typename Type>
	void Read(Type*, int bytes = -1);

	void Read(std::queue<StateMsgInfo>& q, bool&);
	StateMsgType GetMsgType();

	StateMsgArgu* GetStateMsg(StateMsgType);

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

template<typename Type>
inline void MemoryReadStream::Read(Type* data, int bytes)
{
	int retval;
	// 0이라면 통으로 읽을 차례
	if (m_iNowReadIndex == -1)
	{
		retval = recv(m_Socket, (char*)&m_iBufSize, sizeof(int), MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			err_quit("MemoryReadStream::Read bufsize Err");
		}

		retval = recv(m_Socket, (char*)buf, m_iBufSize, MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			err_quit("MemoryReadStream::Read buf Err");
		}
	}
	else
	{
		StateMsgType SMT;
		int Size;

		memcpy(&SMT, buf + m_iNowReadIndex, sizeof(StateMsgType));
		data = GetStateMsg(SMT, &Size);

		m_iNowReadIndex += sizeof(Size);

		if (m_iNowReadIndex >= m_iBufSize)
		{
			m_iNowReadIndex = -1;
		}
	}
}
