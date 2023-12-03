#pragma once

#include "../MemStream/StreamGlobal.h"

class MemoryWriteStream
{
public:
	MemoryWriteStream(array<SOCKET, MAX_CLIENTS>& sockets)
		: m_Sockets(sockets),
		m_iNowWriteIndex(0)
	{
		Init();
	};

	template<typename Type>
	void Write(const Type&, int bytes = -1);

	void Send();
	void Init();
private:
	// ���� �ڷ������� Ȯ��
	template<typename Type>
	void CheckArithmetic(const Type&);

	// �۽ſ� ����
	char buf[STREAMBUFFERSIZE];

	// ��Ʈ�� Write�� ���� �ε��� ��ġ
	int m_iNowWriteIndex;

	// ���ϵ�
	array<SOCKET, MAX_CLIENTS> m_Sockets;
};

template<typename Type>
void MemoryWriteStream::Write(const Type& data, int bytes)
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
 
template<typename Type>
void MemoryWriteStream::CheckArithmetic(const Type& data)
{
	static_assert(
		std::is_arithmetic<Type>::value ||
		std::is_enum<Type>::value,
		"���� �ڷ����� �ƴ� ���� ���Խ��ϴ�.");
}