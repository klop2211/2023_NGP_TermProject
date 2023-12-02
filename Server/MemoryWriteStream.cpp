#include "Common.h"
#include "MemoryWriteStream.h"
#include "StateMessage.h"

void MemoryWriteStream::Send()
{
	int retval;
	for (const auto& s : m_Sockets)
	{
		retval = send(s, buf, m_iNowWriteIndex, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
		}
	}
	Init();
}

void MemoryWriteStream::Init()
{
	m_iNowWriteIndex = 0;
	memset(buf, 0, SENDBUFFERSIZE);
}
