#include "stdafx.h"
#include "Bat.h"

Bat::Bat()
{
	if (m_cImg.IsNull())
	{
		m_cImg.Load(TEXT(""));
	}
	m_pPoint = { 67 * 2,49 * 2 };
	m_pOffset = { 67,49 };
	m_rRect = { WINWIDTH - 200, 400 - m_pPoint.y, WINWIDTH - 200 + m_pPoint.x, 400 };
	//m_cImg = BatImg;
	status = MonsterStatus::Move;
	m_iMaxHp = 10;
	m_iCurrentHp = 10;
	m_iDamage = 15, m_iExperi = 15;

	m_iCount = 0, m_fWait = 0, m_iSpeed = 5;
	m_bCanDie = false;
}

void Bat::Draw(HDC& memdc)
{
	ImgDraw(memdc);
	HpDraw(memdc);
}

void Bat::ImgDraw(HDC& memdc)
{
	int frame = 6;

	if (status != MonsterStatus::Die)
		m_cImg.Draw(memdc, m_rRect.left, m_rRect.top, m_pPoint.x, m_pPoint.y,
			0 + m_pOffset.x * (m_iCount % frame), 0 + m_pOffset.y * (int)status, m_pOffset.x - 2, m_pOffset.y - 2);
	else
		m_cImg.AlphaBlend(memdc, m_rRect.left, m_rRect.top, m_pPoint.x, m_pPoint.y,
			0 + m_pOffset.x * 5, 0 + m_pOffset.y * 1, m_pOffset.x - 2, m_pOffset.y - 2, 255 - m_iCount, AC_SRC_OVER);
}

void Bat::HpDraw(HDC& memdc)
{
	HBRUSH hBrush, oldBrush;

	hBrush = CreateSolidBrush(RGB(255, 64, 64));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, m_rRect.left + 20, m_rRect.bottom, m_rRect.left + 20 + ((m_rRect.right - m_rRect.left - 20) * m_iCurrentHp / m_iMaxHp), m_rRect.bottom + 10);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);
}

void Bat::Update(float elapsed)
{
	// 60프레임 기준 초당 20번 if 문 통과 및 m_iCount 증가
	// TODO: 타이머 적용
	m_fWait += elapsed;
	if (m_fWait) {
		m_iCount++;

		switch (status)
		{
		case MonsterStatus::Move:
			//hit(1);
			m_rRect.left -= m_iSpeed;
			m_rRect.right -= m_iSpeed;
			if (m_rRect.left < CASTLEXPOINT - 50) {
				status = MonsterStatus::Attack;
				m_iCount = 0, m_fWait = 0;
			}
			break;
		case MonsterStatus::Dead:
			m_rRect.top += 15;
			m_rRect.bottom += 15;
			if (m_iCount == 5)
				--m_iCount;
			if (m_rRect.bottom > GROUNDYPOINT) {
				m_rRect.bottom = GROUNDYPOINT;
				m_rRect.top = GROUNDYPOINT - m_pPoint.y;
				status = MonsterStatus::Die;
				m_iCount = 0, m_fWait = 0;
			}
			break;
		case MonsterStatus::Attack:
			if (m_iCount % 6 == 3) {
				hitCastle(m_iDamage);
			}
			break;
		case MonsterStatus::Hit:
			if (m_iCount == 6) {
				status = MonsterStatus::Move;
				m_iCount = 0, m_fWait = 0;
			}
			break;
		case MonsterStatus::Die:
			m_iCount += 10;
			if (m_iCount > 245)
				m_bCanDie = true;
			break;
		default:
			break;
		}
	}
}

bool Bat::Hit(int att)
{
	status = MonsterStatus::Hit;
	m_iCount = 0, m_fWait = 0;
	m_iCurrentHp -= att;
	if (m_iCurrentHp <= 0) {
		m_iCurrentHp = 0;
		status = MonsterStatus::Dead;
		m_iCount = 0, m_fWait = 0;
		return true;
	}
	return false;
}