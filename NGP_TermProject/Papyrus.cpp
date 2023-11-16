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
	m_pSize = { m_pPoint.x * 5, m_pPoint.y * 5 };
	m_Location = { float(WINWIDTH - 300), float(634 - m_pSize.y) };
	m_rRect = { WINWIDTH - 300, 634 - m_pSize.y, WINWIDTH + m_pSize.x - 300, 634 };
	//img = papyrusImg;
	//this->m_cBossHpBar = m_cBossHpBar;
	m_iCount = 0, m_fWait = 0, m_iSpeed = 10;
	status = PapyrusStatus::UP_Move;

	m_iCurrentHp = 60;
	m_iMaxHp = 60;
	m_iBreakCount = 10, m_bBreaked = false;
	m_iKnockDown = 100, m_bCanDown = true;
	m_fBreakTimer = 0.f;

	lstrcpy(m_sName, L"���Ƿ罺");
	m_rNameRect = { 350 + 134, 0, 1250, 50 + 50 };
	m_rHpRect = { 350 + 134, 50 + 54, 1250 , 50 + 87 };

	m_bCanDie = false;
}

void Papyrus::Update(float elapsed)
{
	static float Timer = .0f;
	Timer += elapsed;
	m_fAttackTimer += elapsed;
	if (Timer > 0.166 * 5)
	{
		m_iCount++;
		Timer = 0.f;
	}

	if (m_bBreaked)
	{
		BreakingUpdate(elapsed);
	}
	else
	{
		UnBreakingUpdate(elapsed);
	}
}

void Papyrus::BreakingUpdate(float elapsed)
{
	switch (status) {
	case PapyrusStatus::P_Move:
	{
		RECT temp, check = { m_rRect.left - 100,m_rRect.top,m_rRect.right - 100,m_rRect.bottom };
		if (IntersectRect(&temp, &check, m_pPlayer->GetRect(1)))
		{
			if (m_fAttackTimer > 7.5f)
			{
				status = PapyrusStatus::P_Pattern1;
				m_fAttackTimer = 0;
				//m_fWait = 0, m_iCount = 0;
			}
		}
		else
		{
			int randInt = GetRand(100);
			if (randInt < 3)
			{
				status = PapyrusStatus::P_Pattern2;
				m_fWait = 0, m_iCount = 0;
			}
			m_Location.x -= m_iSpeed * 20 * elapsed;
			SyncLocationAtRect();
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
				if (m_pBone[i] == nullptr) {
					m_pBone[i] = new Bone(1, m_rRect.left, m_rRect.top);
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
				if (m_pMiniBone[i] == nullptr) {
					m_pMiniBone[i] = new Bone(2, m_rRect.left + 25 * 5, m_rRect.top + 20 * 5);
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

void Papyrus::UnBreakingUpdate(float elapsed)
{
	switch (status)
	{
	case PapyrusStatus::UP_Breaking:
	{
		if (m_iCount >= 7)
		{
			status = PapyrusStatus::P_Move;
			m_fWait = m_iCount = 0;
			m_bBreaked = true;
		}
	}
	break;
	case PapyrusStatus::UP_Move:
	{
		RECT temp, check = { m_rRect.left - 100,m_rRect.top,m_rRect.right - 100,m_rRect.bottom };
		if (IntersectRect(&temp, &check, m_pPlayer->GetRect(1)))
		{
			if (m_fAttackTimer > 7.5f)
			{
				status = PapyrusStatus::UP_Pattern;
				m_fAttackTimer = 0;
			}
		}
		m_Location.x -= m_iSpeed * 20 * elapsed;
		SyncLocationAtRect();
	}
	break;
	case PapyrusStatus::UP_Pattern:
	{			
		for (int i = 0; i < 2; i++)
		{
			if (m_pBone[i] == nullptr) {
				m_pBone[i] = new Bone(0, m_rRect.left, m_rRect.bottom);
				break;
			}
		}		
	}
	break;
	default:
		break;
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
			1 + m_pPoint.x * (m_iCount % frame), 1 + m_pPoint.y * (int)status, m_pPoint.x - 1, m_pPoint.y - 1);
	else {
		if (status == PapyrusStatus::P_Die) {
			m_cImg.AlphaBlend(memdc, m_rRect.left, m_rRect.top, m_pPoint.x, m_pPoint.y,
				1 + m_pPoint.x * 10, 163 + m_pPoint.y * 1, m_pPoint.x - 1, m_pPoint.y - 1, 255 - m_iCount, AC_SRC_OVER);
		}
		else {
			m_cImg.Draw(memdc, m_rRect.left, m_rRect.top, m_pPoint.x, m_pPoint.y,
				1 + m_pPoint.x * (m_iCount % frame), 163 + m_pPoint.y * (int)status, m_pPoint.x - 1, m_pPoint.y - 1);
		}
	}
}

void Papyrus::HpDraw(HDC& memdc)
{
	HBRUSH hBrush, oldBrush;
	HFONT hFont, oldFont;

	//���� ü�¹� ������
	hBrush = CreateSolidBrush(RGB(128, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, 350 + 134, 50 + 54, 1250, 50 + 90);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, 350 + 134, 50 + 54, 350 + 134 + (766 * m_iCurrentHp / m_iMaxHp), 50 + 90);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);

	//���� ü�¹� ��
	m_cBossHpBar.Draw(memdc, 350, 50, 900, 118,
		0, 0, 883, 116);

	SetBkMode(memdc, TRANSPARENT);
	//���� �̸�
	hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"����ü");
	oldFont = (HFONT)SelectObject(memdc, hFont);
	DrawText(memdc, m_sName, lstrlen(m_sName), &m_rNameRect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
	SelectObject(memdc, oldFont); DeleteObject(hFont);

	//���� ü��
	swprintf_s(m_sHpStr, 10, L"%d / %d", m_iCurrentHp, m_iMaxHp);//HANGEUL_CHARSET
	hFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Papyrus");
	oldFont = (HFONT)SelectObject(memdc, hFont);
	DrawText(memdc, m_sHpStr, lstrlen(m_sHpStr), &m_rHpRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(memdc, oldFont); DeleteObject(hFont);

	//����ȭ ��ġ
	if (m_bBreaked) {
		hBrush = CreateSolidBrush(RGB(163, 73, 164));
		oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
		Rectangle(memdc, m_rNameRect.left + 5, m_rHpRect.bottom, m_rNameRect.left + 5 + ((m_rNameRect.right - m_rNameRect.left + 5 - 40) * m_iKnockDown / 100), m_rHpRect.bottom + 5);
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
			status = PapyrusStatus::P_Down;
			m_bBreaked = true;
			m_fWait = m_iCount = 0;
		}

		m_iBreakCount -= AmmorBreak;
		if (m_iBreakCount <= 0) {
			status = PapyrusStatus::UP_Breaking;
			m_fWait = m_iCount = 0;
		}

	}
	else
	{
		m_iCurrentHp -= Att;
		if (m_iCurrentHp <= 0)
		{
			m_iCurrentHp = 0;
			status = PapyrusStatus::P_Down;
			m_fWait = m_iCount = 0;
		}

		this->m_iKnockDown -= KnockDown;
		if (this->m_iKnockDown <= 0)
		{
			status = PapyrusStatus::P_Down;
			m_fWait = m_iCount = 0;
		}
	}
}

void Papyrus::SyncLocationAtRect()
{
	m_rRect.left = int(m_Location.x);
	m_rRect.top = int(m_Location.y);
	m_rRect.right = m_rRect.left + m_pSize.x;
	m_rRect.bottom = m_rRect.top + m_pSize.y;
}