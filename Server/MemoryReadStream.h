#pragma once
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
	void Read(const Type&, int bytes = -1);

	void Init();
private:
	// 수신용 버퍼
	char buf[STREAMBUFFERSIZE];

	// 스트림 Write에 적을 인덱스 위치
	int m_iNowReadIndex;

	// 소켓
	SOCKET m_Socket;
};

template<typename Type>
inline void MemoryReadStream::Read(const Type&, int bytes)
{
	int retval;
	// 0이라면 통으로 읽을 차례
	if (m_iNowReadIndex == 0)
	{
		retval = recv(socket, (char*)&m_iNowReadIndex, sizeof(int), MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			err_quit("MemoryReadStream::Read bufsize Err");
		}

		retval = recv(socket, (char*)buf, m_iNowReadIndex, MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			err_quit("MemoryReadStream::Read buf Err");
		}
	}
	else
	{
		int ReadSize = sizeof(Type);

	}
}
