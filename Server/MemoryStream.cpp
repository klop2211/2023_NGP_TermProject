#include "Common.h"
#include "MemoryStream.h"

void MemoryStream::Send()
{
	// TODO: 메세지 전송


	m_iNowWriteIndex = 0;
	memset(buf, 0, SENDBUFFERSIZE);
}
