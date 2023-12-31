#include "stdafx.h"
#include "Papyrus.h"
#include "Bone.h"
#include "Random.h"
#include "CastleInteraction.h"

CImage Papyrus::m_cBoneImg;

Papyrus::Papyrus()
{
	if (m_cImg.IsNull())
	{
		m_cImg.Load(TEXT("적관련\\파피루스.png"));
		m_cBossHpBar.Load(TEXT("윈플 텀프 이미지\\보스체력바빈통.png"));
	}

	//start 1,1
	//m_pPoint = m_pOffset = { 49, 54 };
	//m_iSize = 5;

	m_pOffset = { 49, 54 };
	m_Size = { m_pOffset.x * 5, m_pOffset.y * 5 };

	// m_Location = { float(WINWIDTH - 300), float(634 - m_Size.y) };
	// m_rRect = { WINWIDTH - 300, 634 - m_Size.y * m_pOffset.x, WINWIDTH + m_Size.y * m_pOffset.y - 300, 634 };
	//img = papyrusImg;
	//this->m_cBossHpBar = m_cBossHpBar;
	m_iCount = 0, m_fWait = 0, m_iSpeed = 10;
	m_Status = UP_Move;

	m_iCurrentHp = 60;
	m_iMaxHp = 60;
	m_iBreakCount = 10, m_bBreaked = false;
	m_iKnockDown = 100, m_bCanDown = true;
	m_fBreakTimer = 0.f;

	lstrcpy(m_sName, L"파피루스");
	m_rNameRect = { 350 + 134, 0, 1250, 50 + 50 };
	m_rHpRect = { 350 + 134, 50 + 54, 1250 , 50 + 87 };

	m_bCanDie = false;

	m_iFrame = 4;
}

void Papyrus::Update(float elapsed)
{
	m_fWait += elapsed;
	if (m_fWait > .15f)
	{
		m_iCount++;

		if (m_bBreaked)
		{
			switch (m_Status)
			{
			case P_Move:
				break;
			case P_Down:
			{
				// 목 떨어지는거 2초 대기 2초 목 붙는거 2초
				static float Timer = 0.f;
				if (m_bCanDown)
				{
					Timer += m_fWait;
					m_iCount = (float)m_iFrame * Timer / 2.f;
					if (Timer > 2.f)
					{
						m_iCount = 10;
						// 2+2 초
						if (Timer > 4.f)
						{
							m_bCanDown = false;
							Timer = 4.f;
						}
					}
				}
				else
				{
					Timer += m_fWait;
					m_iCount = (float)m_iFrame * (6.f - Timer) / 2.f;
					if (Timer < 0.f)
					{
						Timer = 0.f;
						m_Status = P_Move;
						m_iKnockDown = 100;
					}
				}
			}
				break;
			case P_Pattern1:
				break;
			case P_Pattern2:
				break;
			case P_Die:
				break;
			default:
				break;
			}
		}
		else
		{
			switch (m_Status)
			{
			case UP_Breaking:
				break;
			case UP_Move:
				break;
			case UP_Pattern:
				break;
			default:
				break;
			}
		}

		m_fWait = 0.f;
	}
	SyncLocationAtRect();

	//static float Timer = .0f;
	//Timer += elapsed;
	//m_fAttackTimer += elapsed;
	//if (Timer > 0.166 * 5)
	//{
	//	m_iCount++;
	//	Timer = 0.f;
	//}

	//if (m_bBreaked)
	//{
	//	BreakingUpdate(elapsed);
	//}
	//else
	//{
	//	UnBreakingUpdate(elapsed);
	//}
}

void Papyrus::BreakingUpdate(float elapsed)
{
	//switch (m_Status) {
	//case P_Move:
	//{
	//	RECT temp, check = { m_rRect.left - 100,m_rRect.top,m_rRect.right - 100,m_rRect.bottom };
	//	// TODO: 플레이어 생기면 수정
	//	if (false/*IntersectRect(&temp, &check, m_pPlayer->GetRect(1))*/)
	//	{
	//		if (m_fAttackTimer > 7.5f)
	//		{
	//			m_Status = P_Pattern1;
	//			m_fAttackTimer = 0;
	//			//m_fWait = 0, m_iCount = 0;
	//		}
	//	}
	//	else
	//	{
	//		int randInt = RandomGen::GetRand(100);
	//		if (randInt < 3)
	//		{
	//			m_Status = P_Pattern2;
	//			m_fWait = 0, m_iCount = 0;
	//		}
	//		MoveXY(-m_iSpeed, 0, elapsed);
	//	}
	//}
	//break;
	//case P_Down:
	//	if (m_bCanDown) {
	//		if (++m_iCount == 11) {
	//			--m_iCount;
	//			if (m_fWait > 90) {
	//				m_bCanDown = false;
	//				m_fWait = 0;
	//			}
	//			if (m_iCurrentHp <= 0) {
	//				m_Status = P_Die;
	//				m_fWait = m_iCount = 0;
	//			}
	//		}
	//	}
	//	else {
	//		if (--m_iCount < 0) {
	//			m_Status = P_Move;
	//			m_iKnockDown = 100;
	//			m_fWait = m_iCount = 0;
	//		}
	//	}
	//	break;
	//case P_Pattern1:
	//	m_iCount++;
	//	if (m_fWait == 5) {
	//		for (int i = 0; i < 2; i++)
	//		{
	//			if (m_pBone[i] == nullptr) {
	//				m_pBone[i] = new Bone(1, m_rRect.left, m_rRect.top);
	//				break;
	//			}
	//		}
	//	}
	//	break;
	//case P_Pattern2:
	//	m_iCount++;
	//	if (m_iCount % 5 == 4) {
	//		for (int i = 0; i < 15; i++)
	//		{
	//			if (m_pMiniBone[i] == nullptr) {
	//				m_pMiniBone[i] = new Bone(2, m_rRect.left + 25 * 5, m_rRect.top + 20 * 5);
	//				break;
	//			}
	//		}
	//	}
	//	if (m_iCount == 75) {
	//		m_Status = P_Move;
	//		m_fWait = m_iCount = 0;
	//	}
	//	break;
	//case P_Die:
	//	if (m_iCount < 245)
	//		m_iCount += 10;
	//	break;
	//default:
	//	break;
	//}
}

void Papyrus::UnBreakingUpdate(float elapsed)
{
	//switch (m_Status)
	//{
	//case UP_Breaking:
	//{
	//	if (m_iCount >= 7)
	//	{
	// 
	//		m_Status = P_Move;
	//		m_fWait = m_iCount = 0;
	//		m_bBreaked = true;
	//	}
	//	break;
	//}
	//case UP_Move:
	//{
	//	RECT temp, check = { m_rRect.left - 100,m_rRect.top,m_rRect.right - 100,m_rRect.bottom };
	//	// TODO: 플레이어 생기면 수정
	//	if (false/*IntersectRect(&temp, &check, m_pPlayer->GetRect(1))*/)
	//	{
	//		if (m_fAttackTimer > 7.5f)
	//		{
	//			m_Status = UP_Pattern;
	//			m_fAttackTimer = 0;
	//		}
	//	}
	//	m_Location.x -= m_iSpeed * 20 * elapsed;
	//	SyncLocationAtRect();
	//	break;
	//}
	//case UP_Pattern:
	//{			
	//	for (int i = 0; i < 2; i++)
	//	{
	//		if (m_pBone[i] == nullptr) {
	//			m_pBone[i] = new Bone(0, m_rRect.left, m_rRect.bottom);
	//			break;
	//		}
	//	}
	//	break;
	//}
	//default:
	//	break;
	//}
}

void Papyrus::Draw(HDC& memdc)
{
	ImgDraw(memdc);
	HpDraw(memdc);
}

void Papyrus::ImgDraw(HDC& memdc)
{
	if (!m_bBreaked)
		m_cImg.Draw(memdc, m_rRect.left, m_rRect.top, m_Size.x, m_Size.y,
			1 + m_pOffset.x * (m_iCount % m_iFrame), 1 + m_pOffset.y * (int)m_Status, m_pOffset.x - 1, m_pOffset.y - 1);
	else {
		if (m_Status == P_Die) {
			m_cImg.AlphaBlend(memdc, m_rRect.left, m_rRect.top, m_Size.x, m_Size.y,
				1 + m_pOffset.x * 10, 163 + m_pOffset.y * 1, m_pOffset.x - 1, m_pOffset.y - 1, 255 - m_iCount, AC_SRC_OVER);
		}
		else {
			m_cImg.Draw(memdc, m_rRect.left, m_rRect.top, m_Size.x, m_Size.y,
				1 + m_pOffset.x * (m_iCount % m_iFrame), 163 + m_pOffset.y * (int)m_Status, m_pOffset.x - 1, m_pOffset.y - 1);
		}
	}
}

void Papyrus::HpDraw(HDC& memdc)
{
	HBRUSH hBrush, oldBrush;
	HFONT hFont, oldFont;

	//보스 체력바 붉은색
	hBrush = CreateSolidBrush(RGB(128, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, 350 + 134, 50 + 54, 1250, 50 + 90);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, 350 + 134, 50 + 54, 350 + 134 + (766 * m_iCurrentHp / m_iMaxHp), 50 + 90);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);

	//보스 체력바 통
	m_cBossHpBar.Draw(memdc, 350, 50, 900, 118,
		0, 0, 883, 116);

	SetBkMode(memdc, TRANSPARENT);
	//보스 이름
	hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"바탕체");
	oldFont = (HFONT)SelectObject(memdc, hFont);
	DrawText(memdc, m_sName, lstrlen(m_sName), &m_rNameRect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
	SelectObject(memdc, oldFont); DeleteObject(hFont);

	//보스 체력
	swprintf_s(m_sHpStr, 10, L"%d / %d", m_iCurrentHp, m_iMaxHp);//HANGEUL_CHARSET
	hFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Papyrus");
	oldFont = (HFONT)SelectObject(memdc, hFont);
	DrawText(memdc, m_sHpStr, lstrlen(m_sHpStr), &m_rHpRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(memdc, oldFont); DeleteObject(hFont);

	//무력화 수치
	if (m_bBreaked) {
		hBrush = CreateSolidBrush(RGB(163, 73, 164));
		oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
		Rectangle(memdc, m_rNameRect.left + 5, m_rHpRect.bottom, m_rNameRect.left + 5 + ((m_rNameRect.right - m_rNameRect.left + 5 - 40) * m_iKnockDown / 100), m_rHpRect.bottom + 5);
	}
}

void Papyrus::SetStatus(BossStateType BST)
{
	m_iCount = 0;
	switch (BST)
	{
	case BossStateType::Move:
		if (m_Status == PapyrusState::UP_Breaking)
		{
			m_bBreaked = true;
		}
		if (m_bBreaked)
		{
			m_Status = PapyrusState::P_Move;
		}
		else
		{
			m_Status = PapyrusState::UP_Move;
		}
		break;
	case BossStateType::UBPattern:
		m_Status = PapyrusState::UP_Pattern;
		break;
	case BossStateType::BPattern1:
		m_Status = PapyrusState::P_Pattern1;
		break;
	case BossStateType::BPattern2:
		m_Status = PapyrusState::P_Pattern2;
		break;
	case BossStateType::Breaking:
		m_Status = PapyrusState::UP_Breaking;
		break;
	case BossStateType::Stunning:
		m_Status = PapyrusState::P_Down;
		break;
	case BossStateType::CantMove:
		m_Status = PapyrusState::P_Down;
		break;
	default:
		break;
	}

	if (!m_bBreaked)
	{
		switch (m_Status)
		{
		case UP_Breaking:
			m_iFrame = 8;
			break;
		case UP_Move:
			m_iFrame = 4;
			break;
		case UP_Pattern:
			m_iFrame = 2;
			break;
		}
	}
	else
	{
		switch (m_Status)
		{
		case P_Move:
			m_iFrame = 4;
			break;
		case P_Down:
			m_iFrame = 11;
			break;
		case P_Pattern1:
			m_iFrame = 5;
			break;
		case P_Pattern2:
			m_iFrame = 5;
			break;
		case P_Die:
			m_iFrame = 1;
			break;
		default:
			m_iFrame = 1;
			break;
		}
	}
}

bool Papyrus::Hit(int Att, int AmmorBreak, int KnockDown)
{
	if (!m_bBreaked) {
		int temp = Att * 0.6;
		if (temp == 0)
		{
			temp = 1;
		}

		m_iCurrentHp -= Att * 0.6;
		if (m_iCurrentHp <= 0)
		{
			m_iCurrentHp = 0;
			m_Status = P_Down;
			m_bBreaked = true;
			m_fWait = m_iCount = 0;
		}

		m_iBreakCount -= AmmorBreak;
		if (m_iBreakCount <= 0) {
			m_Status = UP_Breaking;
			m_fWait = m_iCount = 0;
		}

	}
	else
	{
		m_iCurrentHp -= Att;
		if (m_iCurrentHp <= 0)
		{
			m_iCurrentHp = 0;
			m_Status = P_Down;
			m_fWait = m_iCount = 0;
			return true;
		}

		this->m_iKnockDown -= KnockDown;
		if (this->m_iKnockDown <= 0)
		{
			m_Status = P_Down;
			m_fWait = m_iCount = 0;
		}
	}
	return false;
}