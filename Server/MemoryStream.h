#pragma once

#define SENDBUFFERSIZE 1024

class MemoryStream
{
public:
	// Mem Stream
	template<typename Type>
	void Write(const Type&, int bytes = -1);
	void Send(const array<SOCKET, MAX_ROOMS>&);

private:
	// 원시 자료형인지 확인
	template<typename Type>
	void CheckArithmetic(const Type&);

	// 송신용 버퍼
	char buf[SENDBUFFERSIZE];

	// 스트림 Write에 적을 인덱스 위치
	int m_iNowWriteIndex;

	// 보낼 소켓들
	array<SOCKET, MAX_ROOMS> m_Sockets;
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

	if (m_iNowWriteIndex + size > SENDBUFFERSIZE)
	{
		//TODO: 고쳐야함
		//Send();
	}

	memcpy_s(buf + m_iNowWriteIndex, SENDBUFFERSIZE - (m_iNowWriteIndex + size), &data, size);
	m_iNowWriteIndex += size;
}
 
template<typename Type>
void MemoryStream::CheckArithmetic(const Type& data)
{
	static_assert(
		std::is_arithmetic<Type>::value ||
		std::is_enum<Type>::value,
		"원시 자료형이 아닌 값이 들어왔습니다.");
}