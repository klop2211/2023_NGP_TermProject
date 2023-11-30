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
	// ���� �ڷ������� Ȯ��
	template<typename Type>
	void CheckArithmetic(const Type&);

	// �۽ſ� ����
	char buf[SENDBUFFERSIZE];

	// ��Ʈ�� Write�� ���� �ε��� ��ġ
	int m_iNowWriteIndex;

	// ���� ���ϵ�
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
		//TODO: ���ľ���
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
		"���� �ڷ����� �ƴ� ���� ���Խ��ϴ�.");
}