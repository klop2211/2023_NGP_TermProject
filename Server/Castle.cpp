#include "Common.h"
#include "Castle.h"

Castle::Castle()
{
	m_iMaxHp = m_iCurrentHp = 1000;
	m_pBoundingBox = new RECT();
}

Castle::~Castle()
{
	delete m_pBoundingBox;
}
