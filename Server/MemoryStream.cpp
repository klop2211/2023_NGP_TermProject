#include "Common.h"
#include "MemoryStream.h"

template<typename Type>
inline void MemoryStream::Write(const Type& data, int bytes)
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
		Send();
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

void MemoryStream::Send()
{
	// TODO: 메세지 전송


	m_iNowWriteIndex = 0;
	memset(buf, 0, SENDBUFFERSIZE);
}
