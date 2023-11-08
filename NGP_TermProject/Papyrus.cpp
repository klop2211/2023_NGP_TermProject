#include "stdafx.h"
#include "Papyrus.h"
#include "Bone.h"

Papyrus::Papyrus()
{
	if (m_cImg.IsNull())
	{
		m_cImg.Load(TEXT(""));
		m_cBossHpBar.Load(TEXT(""));
	}

	//start 1,1
	m_pPoint = { 49, 54 };
	m_pPoint = { m_pPoint.x * 5, m_pPoint.y * 5 };
	m_rRect = { WINWIDTH - 300, 634 - m_pPoint.y, WINWIDTH + m_pPoint.x - 300, 634 };
	//img = papyrusImg;
	//this->m_cBossHpBar = m_cBossHpBar;
	m_iCount = 0, m_fWait = 0, m_iSpeed = 10;
	status = PapyrusStatus::UP_Move;

	m_iCurrentHp = 60;
	m_iMaxHp = 60;
	m_iBreakCount = 10, m_bBreaked = false;
	m_iKnockDown = 100, m_bCanDown = true;

	lstrcpy(m_sName, L"파피루스");
	m_rNameRect = { 350 + 134, 0, 1250, 50 + 50 };
	m_rHpRect = { 350 + 134, 50 + 54, 1250 , 50 + 87 };

	m_bCanDie = false;
}

void Papyrus::Update(float elapsed)
{
	if (++m_fWait % 5 == 0) {
		if (!m_bBreaked)
			switch (status)
			{
			case PapyrusStatus::UP_Breaking:
				if (m_fWait % 4) {
					m_iCount++;
					if (m_iCount == 7) {
						status = PapyrusStatus::P_Move;
						m_fWait = m_iCount = 0;
						m_bBreaked = true;
					}
				}
				break;
			case PapyrusStatus::UP_Move:
			{
				RECT temp, check = { m_rRect.left - 100,m_rRect.top,m_rRect.right - 100,m_rRect.bottom };
				if (IntersectRect(&temp, &check, player->GetRect(1))) {
					if (GetRand(50) < 1)
						status = PapyrusStatus::UP_Pattern;
				}
				if (m_fWait % 3 == 0) {
					m_rRect.left -= 10;
					m_rRect.right -= 10;
					m_iCount++;
					hit(0, 1, 0);
				}
			}
			break;
			case PapyrusStatus::UP_Pattern:
				if (++m_iCount % 20 == 0) {
					for (int i = 0; i < 2; i++)
					{
						if (bone[i] == nullptr) {
							bone[i] = new Bone(0, m_rRect.left, m_rRect.bottom, m_cBoneImg);
							break;
						}
					}
				}
				break;
			default:
				break;
			}
		else
			switch (status) {
			case PapyrusStatus::P_Move:
			{
				RECT temp, check = { m_rRect.left - 100,m_rRect.top,m_rRect.right - 100,m_rRect.bottom };
				if (IntersectRect(&temp, &check, player->GetRect(1))) {
					if (GetRand(50) < 3) {
						status = PapyrusStatus::P_Pattern1;
						m_fWait = 0, m_iCount = 0;
					}
				}
				if (m_fWait % 2 == 0) {
					int randInt = GetRand(50);
					if (randInt < 3) {
						status = PapyrusStatus::P_Pattern2;
						m_fWait = 0, m_iCount = 0;
					}
					m_rRect.left -= 10;
					m_rRect.right -= 10;
					m_iCount++;
					//hit(0, 0, 60);
				}
			}
			break;
			case PapyrusStatus::P_Down:
				if (m_bCanDown) {
					if (++m_iCount == 11) {
						--m_iCount;
						if (m_fWait > 90) {
							m_bCanDown = false;
							m_fWait = 0;
						}
						if (m_iCurrentHp <= 0) {
							status = PapyrusStatus::P_Die;
							m_fWait = m_iCount = 0;
						}
					}
				}
				else {
					if (--m_iCount < 0) {
						status = PapyrusStatus::P_Move;
						m_iKnockDown = 100;
						m_fWait = m_iCount = 0;
					}
				}
				break;
			case PapyrusStatus::P_Pattern1:
				m_iCount++;
				if (m_fWait == 5) {
					for (int i = 0; i < 2; i++)
					{
						if (bone[i] == nullptr) {
							bone[i] = new Bone(1, m_rRect.left, m_rRect.top, img);
							break;
						}
					}
				}
				break;
			case PapyrusStatus::P_Pattern2:
				m_iCount++;
				if (m_iCount % 5 == 4) {
					for (int i = 0; i < 15; i++)
					{
						if (miniBone[i] == nullptr) {
							miniBone[i] = new Bone(2, m_rRect.left + 25 * 5, m_rRect.top + 20 * 5, img);
							break;
						}
					}
				}
				if (m_iCount == 75) {
					status = PapyrusStatus::P_Move;
					m_fWait = m_iCount = 0;
				}
				break;
			case PapyrusStatus::P_Die:
				if (m_iCount < 245)
					m_iCount += 10;
				break;
			default:
				break;
			}
	}
}

void Papyrus::Draw(HDC& memdc)
{
	ImgDraw(memdc);
	HpDraw(memdc);
}

void Papyrus::ImgDraw(HDC& memdc)
{
	int frame = 1;

	if (!m_bBreaked)
		switch (status)
		{
		case PapyrusStatus::UP_Breaking:
			frame = 8;
			break;
		case PapyrusStatus::UP_Move:
			frame = 4;
			break;
		case PapyrusStatus::UP_Pattern:
			frame = 2;
			break;
		}
	else
		switch (status) {
		case PapyrusStatus::P_Move:
			frame = 4;
			break;
		case PapyrusStatus::P_Down:
			frame = 11;
			break;
		case PapyrusStatus::P_Pattern1:
			frame = 5;
			break;
		case PapyrusStatus::P_Pattern2:
			frame = 5;
			break;
		case PapyrusStatus::P_Die:
			frame = 1;
			break;
		default:
			frame = 1;
			break;
		}
	if (!m_bBreaked)
		m_cImg.Draw(memdc, m_rRect.left, m_rRect.top, m_pPoint.x, m_pPoint.y,
			1 + m_pPoint.x * (m_iCount % frame), 1 + m_pPoint.y * status, m_pPoint.x - 1, m_pPoint.y - 1);
	else {
		if (status == PapyrusStatus::P_Die) {
			m_cImg.AlphaBlend(memdc, m_rRect.left, m_rRect.top, m_pPoint.x, m_pPoint.y,
				1 + m_pPoint.x * 10, 163 + m_pPoint.y * 1, m_pPoint.x - 1, m_pPoint.y - 1, 255 - m_iCount, AC_SRC_OVER);
		}
		else {
			m_cImg.Draw(memdc, m_rRect.left, m_rRect.top, m_pPoint.x, m_pPoint.y,
				1 + m_pPoint.x * (m_iCount % frame), 163 + m_pPoint.y * status, m_pPoint.x - 1, m_pPoint.y - 1);
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
