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
	// ���ſ� ����
	char buf[STREAMBUFFERSIZE];

	// ��Ʈ�� Write�� ���� �ε��� ��ġ
	int m_iNowReadIndex;

	// buf�� ��� ����Ʈ ��
	int m_iBufSize;

	// ����
	SOCKET m_Socket;
};

template<typename Type>
inline void MemoryReadStream::Read(Type* data, int bytes)
{
	int retval;
	// 0�̶�� ������ ���� ����
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
