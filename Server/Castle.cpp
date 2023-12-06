#include "Common.h"
#include "Castle.h"

Castle::Castle()
{
	m_iMaxHp = m_iCurrentHp = 1000;
	m_pBoundingBox = new RECT();
	m_pBoundingBox->left = 0;
	m_pBoundingBox->top = 0;
	m_pBoundingBox->right = 259;
	m_pBoundingBox->bottom = 635;
}

Castle::~Castle()
{
	delete m_pBoundingBox;
}

void Castle::GetDamage(int hp)
{
	m_iCurrentHp -= hp;
}