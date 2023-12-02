#include "Common.h"
#include "MemoryReadStream.h"




void MemoryReadStream::Init()
{
	m_iNowReadIndex = 0;
	memset(buf, 0, STREAMBUFFERSIZE);
}
