#include "Common.h"
#include "MemoryStream.h"

void MemoryStream::Send()
{
	// TODO: �޼��� ����


	m_iNowWriteIndex = 0;
	memset(buf, 0, SENDBUFFERSIZE);
}
