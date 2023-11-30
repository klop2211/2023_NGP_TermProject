#pragma once

#define SENDBUFFERSIZE 1024

class MemoryStream
{
public:
	// Mem Stream
	template<typename Type>
	void Write(const Type&, int i = -1);
	void Send();

private:
	// 원시 자료형인지 확인
	template<typename Type>
	void CheckArithmetic(const Type&);

	// 송신용 버퍼
	char buf[SENDBUFFERSIZE];

	// 스트림 Write에 적을 인덱스 위치
	int m_iNowWriteIndex;
};
