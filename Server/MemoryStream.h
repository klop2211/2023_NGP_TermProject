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
	// ���� �ڷ������� Ȯ��
	template<typename Type>
	void CheckArithmetic(const Type&);

	// �۽ſ� ����
	char buf[SENDBUFFERSIZE];

	// ��Ʈ�� Write�� ���� �ε��� ��ġ
	int m_iNowWriteIndex;
};
