#pragma once

#include "../Server/StateMessage.h"
#include "../MemStream/StreamGlobal.h"

#include <array>
#include <vector>
#include <queue>

class MemoryStream
{
public:
	MemoryStream() :
		m_iNowWriteIndex(0),
		m_iBufSize(0)
	{

	}
	~MemoryStream() {}

public:
	template<typename Type>
	void Write(const Type&, int bytes = -1);
	void Read(const SOCKET& s, std::queue<StateMsgInfo>& q, bool&);

	void Send(const SOCKET& s);
	void Send(array<SOCKET, MAX_CLIENTS>& sockets);
	void SendData(const SOCKET& s);

	StateMsgType GetMsgType(const int& index);
	StateMsgArgu* GetStateMsg(StateMsgType, int&);

	void Init();

private:
	// ���ſ� ����
	char buf[STREAMBUFFERSIZE];

	// ��Ʈ�� Write�� ���� �ε��� ��ġ
	int m_iNowWriteIndex;

	// buf�� ��� ����Ʈ ��
	int m_iBufSize;

	// ���ϵ�
	vector<SOCKET> m_Sockets;
};

template<typename Type>
void MemoryStream::Write(const Type& data, int bytes)
{
	//CheckArithmetic(data);

	int size;
	if (bytes == -1)
	{
		size = sizeof(Type);
	}
	else
	{
		size = bytes;
	}

	// ���� �������� �� �տ� ũ�⸦ ��Ÿ�� int�� �����ϴ�
	if (m_iNowWriteIndex + size + sizeof(int) > STREAMBUFFERSIZE)
	{
		Send();
	}

	memcpy_s(buf + m_iNowWriteIndex, STREAMBUFFERSIZE - (m_iNowWriteIndex + size), &data, size);
	m_iNowWriteIndex += size;
	buf[m_iNowWriteIndex] = '\0';
}