#include "Common.h"
#include "MemoryStream.h"

void MemoryStream::Send()
{
	int retval;
	for (const auto& s : m_Sockets)
	{
		retval = send(s, buf, m_iNowWriteIndex, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
		}
	}

	m_iNowWriteIndex = 0;
	memset(buf, 0, SENDBUFFERSIZE);
}