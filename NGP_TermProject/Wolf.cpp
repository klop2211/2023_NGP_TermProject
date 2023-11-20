#include "stdafx.h"
#include "Wolf.h"

Wolf::Wolf()
{
	if (m_cImg.IsNull())
	{
		m_cImg.Load(TEXT("적관련\\늑대.png"));
	}
	//start = {0,1}
	m_pPoint = { 86 * 2, 58 * 2 };
	m_pOffset = { 86, 58 };
	m_rRect = { WINWIDTH - 200, 634 - m_pPoint.y, WINWIDTH + m_pPoint.x - 200, 634 };

	status = MonsterStatus::Move;
	m_iSpeed = 6;
	m_iCurrentHp = 20;
	m_iMaxHp = 20;
	m_iDamage = 20, m_iExperi = 20, m_iCount = 0, m_fWait = 0;
	m_bCanDie = false;
}

void Wolf::Draw(HDC& memdc)
{
	ImgDraw(memdc);
	HpDraw(memdc);
}

void Wolf::ImgDraw(HDC& memdc)
{
	int frame;

	switch (status)
	{
	case MonsterStatus::Move:
		frame = 6;
		break;
	case MonsterStatus::Dead:
		frame = 8;
		break;
	case MonsterStatus::Attack:
		frame = 10;
		break;
	case MonsterStatus::Hit:
		frame = 6;
		break;
	default:
		frame = 1;
		break;
	}

	if (status != MonsterStatus::Die)
		m_cImg.Draw(memdc, m_rRect.left, m_rRect.top, m_pPoint.x, m_pPoint.y,
			0 + m_pOffset.x * (m_iCount % frame), 1 + m_pOffset.y * (int)(status), m_pOffset.x - 2, m_pOffset.y - 2);
	else
		m_cImg.AlphaBlend(memdc, m_rRect.left, m_rRect.top, m_pPoint.x, m_pPoint.y,
			0 + m_pOffset.x * (7), 1 + m_pOffset.y * (1), m_pOffset.x - 2, m_pOffset.y - 2, 255 - m_iCount, AC_SRC_OVER);
}

void Wolf::HpDraw(HDC& memdc)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(255, 64, 64));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, m_rRect.left + 20, m_rRect.bottom, m_rRect.left + 20 + ((m_rRect.right - m_rRect.left - 20) * m_iCurrentHp / m_iMaxHp), m_rRect.bottom + 10);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);
}

void Wolf::Update(float elapsed)
{
	// 60프레임 기준 초당 20번 if 문 통과 및 m_iCount 증가
	// TODO: 타이머 적용
	m_fWait += elapsed;
	if (m_eSE == StatusEffect::Ice_s)
	{
		static float IceTimer = 0.f;
		IceTimer += elapsed;
		if (IceTimer > 3.f) {
			status = MonsterStatus::Move;
			m_eSE = StatusEffect::NULL_S;
			IceTimer = 0.f;
		}
	}
	else
	{
		if (m_eSE == StatusEffect::Fire_s)
		{
			static float FireTimer = 0.f;
			static float TickTimer = 0.f;
			FireTimer += elapsed;
			TickTimer += elapsed;
			if (TickTimer > 1.f)
			{
				Hit(1);
				TickTimer = 0.f;
			}
			if (FireTimer > 3.f) {
				status = MonsterStatus::Move;
				m_eSE = StatusEffect::NULL_S;
				FireTimer = 0.f;
			}
		}

		switch (status)
		{
		case MonsterStatus::Move:
			//Hit(1);
			MoveXY(-m_iSpeed, 0, elapsed);
			if (m_rRect.left < CASTLEXPOINT - 50) {
				status = MonsterStatus::Attack;
				m_iCount = 0, m_fWait = 0;
			}
			break;
		case MonsterStatus::Dead:
			if (m_iCount == 8) {
				status = MonsterStatus::Die;
				m_iCount = 0, m_fWait = 0;
			}
			break;
		case MonsterStatus::Attack:
			if (m_iCount % 10 == 6) {
				// TODO: 소켓 보내기?
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
			m_iCount += 6;
			if (m_iCount > 249) {
				m_bCanDie = true;

			}
			break;
		default:
			break;
		}
	}
}

bool Wolf::Hit(int att)
{
	status = MonsterStatus::Hit;
	m_iCurrentHp -= att;
	if (m_iCurrentHp <= 0) {
		m_iCurrentHp = 0;
		status = MonsterStatus::Dead;
		return true;
	}
	return false;
}