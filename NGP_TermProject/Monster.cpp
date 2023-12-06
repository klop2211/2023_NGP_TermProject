#include "stdafx.h"

#include "Monster.h"
#include "CastleInteraction.h"

void Monster::SyncLocationAtRect()
{
	m_rRect.left = int(m_Location.x);
	m_rRect.top = int(m_Location.y);
	m_rRect.right = m_rRect.left + m_Size.x;
	m_rRect.bottom = m_rRect.top + m_Size.y;
}

void Monster::MoveXY(float x, float y, float elapsed)
{
	m_Location.x += x * 20 * elapsed;
	m_Location.y += y * 20 * elapsed;
	SyncLocationAtRect();
}

void Monster::SetCastleInteraction(CastleInteraction* castleIntercation)
{
	m_pCastleInteraction = castleIntercation;
}

//void Monster::Update(float elapsed)
//{
//}
//
//bool Monster::Hit(int damage)
//{
//	return false;
//}
//
//void Monster::Draw(HDC& memdc)
//{
//	ImgDraw(memdc);
//	HpDraw(memdc);
//}
//
//void Monster::ImgDraw(HDC& memdc)
//{
//}
//
//void Monster::HpDraw(HDC& memdc)
//{
//}
