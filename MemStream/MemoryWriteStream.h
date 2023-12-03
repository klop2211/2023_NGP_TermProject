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
	// 원시 자료형인지 확인
	template<typename Type>
	void CheckArithmetic(const Type&);

	// 송신용 버퍼
	char buf[STREAMBUFFERSIZE];

	// 스트림 Write에 적을 인덱스 위치
	int m_iNowWriteIndex;

	// 소켓들
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

	// 보낼 데이터의 맨 앞에 크기를 나타낼 int가 들어가야하니
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
		"원시 자료형이 아닌 값이 들어왔습니다.");
}