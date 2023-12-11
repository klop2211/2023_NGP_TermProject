#include "stdafx.h"
#include "Wolf.h"
#include "CastleInteraction.h"

CImage Wolf::m_cImg;

Wolf::Wolf()
{
	if (m_cImg.IsNull())
	{
		m_cImg.Load(TEXT("Àû°ü·Ã\\´Á´ë.png"));
	}
	//start = {0,1}
	m_Size = { 86 * 2, 58 * 2 };
	//m_pPoint = { 86 * 2, 58 * 2 };
	m_pOffset = { 86, 58 };
	// m_rRect = { WINWIDTH - 200, 634 - m_pPoint.y, WINWIDTH + m_pPoint.x - 200, 634 };
	// m_Location = { (float)(WINWIDTH - 200), (float)(634 - m_pPoint.y) };

	m_Status = MonsterState::Move;
	m_iSpeed = 6;
	m_iCurrentHp = 20;
	m_iMaxHp = 20;
	m_iDamage = 20, m_iExperi = 20, m_iCount = 0, m_fWait = 0, m_iMoney = 3;
	m_bCanDie = false;

	m_iFrame = 6;
}

void Wolf::Draw(HDC& memdc)
{
	ImgDraw(memdc);
	if (m_Status != MonsterState::Die && m_Status != MonsterState::Dead)
	{
		HpDraw(memdc);
	}
}

void Wolf::ImgDraw(HDC& memdc)
{
	if (m_Status != MonsterState::Die)
		m_cImg.Draw(memdc, m_rRect.left, m_rRect.top, m_Size.x, m_Size.y,
			0 + m_pOffset.x * (m_iCount % m_iFrame), 1 + m_pOffset.y * (int)(m_Status), m_pOffset.x - 2, m_pOffset.y - 2);
	else
		m_cImg.AlphaBlend(memdc, m_rRect.left, m_rRect.top, m_Size.x, m_Size.y,
			0 + m_pOffset.x * (7), 1 + m_pOffset.y * (1), m_pOffset.x - 2, m_pOffset.y - 2, 255 - m_iCount * 8, AC_SRC_OVER);
}

void Wolf::HpDraw(HDC& memdc)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(255, 64, 64));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, m_rRect.left + 20, m_rRect.bottom, m_rRect.left + 20 + ((m_rRect.right - m_rRect.left - 20) * m_iCurrentHp / m_iMaxHp), m_rRect.bottom + 10);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);
}

void Wolf::SetStatus(MonsterState MS)
{
	bool IsChanged = m_Status != MS;

	switch (MS)
	{
	case MonsterState::Move:
		m_iFrame = 6;
		break;
	case MonsterState::Dead:
		m_iFrame = 8;
		m_iCount = 0;
		break;
	case MonsterState::Attack:
		m_iCount = 0;
		m_iFrame = 10;
		m_bCanAttack = true;
		break;
	case MonsterState::Hit:
		m_iFrame = 6;
		break;
	default:
		m_iFrame = 1;
		m_iCount = 0;
		break;
	}

	m_Status = MS;
}

void Wolf::Update(float elapsed)
{
	m_fWait += elapsed;
	if (m_fWait > .05f)
	{
		m_fWait = 0.f;
		m_iCount++;

		switch (m_Status)
		{
		case MonsterState::Move:
			break;
		case MonsterState::Dead:
			if (m_iCount > m_iFrame)
			{
				SetStatus(MonsterState::Die);
			}
			break;
		case MonsterState::Attack:
			if (!m_bCanAttack)
			{
				m_iCount = 0;
			}
			if (m_iCount > m_iFrame)
			{
				m_iCount = 0;
				m_bCanAttack = false;
			}
			break;
		case MonsterState::Hit:
			break;
		case MonsterState::Die:
			if (m_iCount > 16)
			{
				m_bCanDie = true;
			}
			break;
		default:
			break;
		}
	}
	SyncLocationAtRect();
}

bool Wolf::Hit(int att)
{
	m_Status = MonsterState::Hit;
	m_iCurrentHp -= att;
	if (m_iCurrentHp <= 0) {
		m_iCurrentHp = 0;
		m_Status = MonsterState::Dead;
		return true;
	}
	return false;
}