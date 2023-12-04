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
	// ���ſ� ����
	char buf[STREAMBUFFERSIZE];

	// ��Ʈ�� Write�� ���� �ε��� ��ġ
	int m_iNowReadIndex;
};
