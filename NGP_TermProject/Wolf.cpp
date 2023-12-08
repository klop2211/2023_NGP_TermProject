#include "stdafx.h"
#include "Wolf.h"
#include "CastleInteraction.h"

CImage Wolf::m_cImg;

Wolf::Wolf()
{
	if (m_cImg.IsNull())
	{
		m_cImg.Load(TEXT("적관련\\늑대.png"));
	}
	//start = {0,1}
	m_Size = { 86 * 2, 58 * 2 };
	//m_pPoint = { 86 * 2, 58 * 2 };
	m_pOffset = { 86, 58 };
	// m_rRect = { WINWIDTH - 200, 634 - m_pPoint.y, WINWIDTH + m_pPoint.x - 200, 634 };
	// m_Location = { (float)(WINWIDTH - 200), (float)(634 - m_pPoint.y) };

	status = MonsterState::Move;
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
	HpDraw(memdc);
}

void Wolf::ImgDraw(HDC& memdc)
{
	if (status != MonsterState::Die)
		m_cImg.Draw(memdc, m_rRect.left, m_rRect.top, m_Size.x, m_Size.y,
			0 + m_pOffset.x * (m_iCount % m_iFrame), 1 + m_pOffset.y * (int)(status), m_pOffset.x - 2, m_pOffset.y - 2);
	else
		m_cImg.AlphaBlend(memdc, m_rRect.left, m_rRect.top, m_Size.x, m_Size.y,
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

void Wolf::SetStatus(MonsterState MS)
{
	bool IsChanged = status != MS;

	switch (MS)
	{
	case MonsterState::Move:
		m_iFrame = 6;
		break;
	case MonsterState::Dead:
		m_iFrame = 8;
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
		break;
	}

	status = MS;
}

void Wolf::Update(float elapsed)
{
	m_fWait += elapsed;
	if (m_fWait > .05f)
	{
		m_fWait = 0.f;
		m_iCount++;

		switch (status)
		{
		case MonsterState::Move:
			break;
		case MonsterState::Dead:
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
			break;
		default:
			break;
		}
	}
	SyncLocationAtRect();

	// 60프레임 기준 초당 20번 if 문 통과 및 m_iCount 증가
	// TODO: 타이머 적용
	//if (m_eSE == StatusEffect::Ice_s)
	//{
	//	static float IceTimer = 0.f;
	//	IceTimer += elapsed;
	//	if (IceTimer > 3.f) {
	//		status = MonsterStatus::Move;
	//		m_eSE = StatusEffect::NULL_S;
	//		IceTimer = 0.f;
	//	}
	//}
	//else
	//{
	//	if (m_eSE == StatusEffect::Fire_s)
	//	{
	//		static float FireTimer = 0.f;
	//		static float TickTimer = 0.f;
	//		FireTimer += elapsed;
	//		TickTimer += elapsed;
	//		if (TickTimer > 1.f)
	//		{
	//			Hit(1);
	//			TickTimer = 0.f;
	//		}
	//		if (FireTimer > 3.f) {
	//			status = MonsterStatus::Move;
	//			m_eSE = StatusEffect::NULL_S;
	//			FireTimer = 0.f;
	//		}
	//	}

	//	m_iCount++;
	//	switch (status)
	//	{
	//	case MonsterStatus::Move:
	//		//Hit(1);
	//		MoveXY(-m_iSpeed, 0, elapsed);
	//		//if (m_rRect.left < CASTLEXPOINT - 50) {
	//		//	status = MonsterStatus::Attack;
	//		//	m_iCount = 0, m_fWait = 0;
	//		//}
	//		break;
	//	case MonsterStatus::Dead:
	//		if (m_iCount == 8) {
	//			status = MonsterStatus::Die;
	//			m_iCount = 0, m_fWait = 0;
	//		}
	//		break;
	//	case MonsterStatus::Attack:
	//		if (m_iCount % 10 == 6) {
	//			// TODO: 소켓 보내기?
	//			if (m_pCastleInteraction)
	//			{
	//				m_pCastleInteraction->HitCastle(m_iDamage);
	//			}
	//		}
	//		break;
	//	case MonsterStatus::Hit:
	//		if (m_iCount == 6) {
	//			status = MonsterStatus::Move;
	//			m_iCount = 0, m_fWait = 0;
	//		}
	//		break;
	//	case MonsterStatus::Die:
	//		m_iCount += 6;
	//		if (m_iCount > 249) {
	//			m_bCanDie = true;

	//		}
	//		break;
	//	default:
	//		break;
	//	}
	//}
}

bool Wolf::Hit(int att)
{
	status = MonsterState::Hit;
	m_iCurrentHp -= att;
	if (m_iCurrentHp <= 0) {
		m_iCurrentHp = 0;
		status = MonsterState::Dead;
		return true;
	}
	return false;
}