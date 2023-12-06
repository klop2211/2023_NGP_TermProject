#include "stdafx.h"
#include <atlimage.h>
#include <windef.h>

#include "Card.h"

CImage Card::m_cManaImg[2];

Card::Card()
{
	//m_rRect = new RECT[4];
	m_rRect[(int)CardRect::R_main] = { 30,160,277,245 };
	m_rRect[(int)CardRect::R_tier1] = { 60,265,300,305 };//240/40
	m_rRect[(int)CardRect::R_tier2] = { 60,355,300,395 };//240/40
	m_rRect[(int)CardRect::R_tier3] = { 60,440,300,480 };//240/40
	m_bIsValid = true, m_bCheep = false;

	if (m_cManaImg[0].IsNull())
	{
		m_cManaImg[0].Load(TEXT("윈플 텀프 이미지\\마나.png"));
		m_cManaImg[1].Load(TEXT("윈플 텀프 이미지\\빈마나.png"));
	}
}

Card::~Card()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_cImg[i] != nullptr)
			m_cImg[i].Destroy();
	}
	if (m_cSkill != nullptr)
		m_cSkill.Destroy();
	if (m_cEffect != nullptr)
		m_cEffect.Destroy();
}

void Card::Draw(HDC& memdc)
{
}

void Card::handDraw(HDC& memdc)
{
	HBRUSH hBrush, oldBrush;
	RECT rect = { m_pPoint.x, m_pPoint.y, m_pPoint.x + 187, m_pPoint.y + 35 };
	TCHAR manaStr[3];

	hBrush = CreateSolidBrush(RGB(14, 15, 16));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, m_pPoint.x, m_pPoint.y, m_pPoint.x + 187, m_pPoint.y + 300);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);

	hBrush = CreateSolidBrush(RGB(25, 28, 33));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, m_pPoint.x, m_pPoint.y, m_pPoint.x + 187, m_pPoint.y + 35);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);

	SetBkMode(memdc, TRANSPARENT);
	SetTextColor(memdc, RGB(255, 255, 255));
	DrawText(memdc, m_tNameStr, lstrlen(m_tNameStr), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	//SetTextColor(memdc, RGB(0, 0, 0));
	m_cSkill.Draw(memdc, m_pPoint.x + 96 - 40, m_pPoint.y + 40, 80, 80, 0, 0, 100, 100);
	m_cManaImg[0].Draw(memdc, m_pPoint.x + 160, m_pPoint.y, 27, 30, 0, 0, 102, 115);
	rect = { m_pPoint.x + 160, m_pPoint.y, m_pPoint.x + 160 + 27, m_pPoint.y + 30 };
	swprintf_s(manaStr, 3, L"%d", m_iMana);
	DrawText(memdc, manaStr, lstrlen(manaStr), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}

void Card::closeDraw(HDC& memdc)
{
	int tempX = m_pPoint.x - (CARDWIDTH - CARDMINIWIDTH) / 2;
	int tempY = m_pPoint.y - CARDHEIGHT;
	mainDraw(memdc, tempX, tempY);
}

void Card::dragDraw(HDC& memdc)
{
	int tempX = m_pPoint.x - (CARDWIDTH - CARDMINIWIDTH) / 2;
	int tempY = m_pPoint.y;
	mainDraw(memdc, tempX, tempY);
}

void Card::mainDraw(HDC& memdc, int tempX, int tempY)
{
	SetTextColor(memdc, RGB(205, 205, 205));
	RECT temp;
	HFONT hFont, oldFont;
	RECT manaRect;
	TCHAR manaStr[3];

	m_cImg[0].Draw(memdc, tempX, tempY, CARDWIDTH, CARDHEIGHT,
		0, 0, CARDWIDTH, CARDHEIGHT);
	temp = { m_rRect[(int)CardRect::R_main].left + tempX, m_rRect[(int)CardRect::R_main].top + tempY, m_rRect[(int)CardRect::R_main].right + tempX, m_rRect[(int)CardRect::R_main].bottom + tempY };
	DrawText(memdc, m_tStr[(int)CardRect::R_main], lstrlen(m_tStr[(int)CardRect::R_main]), &temp, DT_LEFT | DT_WORDBREAK);

	hFont = CreateFont(13, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"");
	oldFont = (HFONT)SelectObject(memdc, hFont);

	if (m_cImg[(int)CardRect::R_tier1] != nullptr) {
		m_cImg[(int)CardRect::R_tier1].Draw(memdc, tempX + 7, tempY + 264, 44, 44,
			0, 0, 56, 56);
		temp = { m_rRect[(int)CardRect::R_tier1].left + tempX, m_rRect[(int)CardRect::R_tier1].top + tempY, m_rRect[(int)CardRect::R_tier1].right + tempX, m_rRect[(int)CardRect::R_tier1].bottom + tempY };
		DrawText(memdc, m_tStr[(int)CardRect::R_tier1], lstrlen(m_tStr[(int)CardRect::R_tier1]), &temp, DT_LEFT | DT_WORDBREAK);

	}
	if (m_cImg[(int)CardRect::R_tier2] != nullptr) {
		m_cImg[(int)CardRect::R_tier2].Draw(memdc, tempX + 8, tempY + 351, 45, 45,
			0, 0, 56, 56);
		temp = { m_rRect[(int)CardRect::R_tier2].left + tempX, m_rRect[(int)CardRect::R_tier2].top + tempY, m_rRect[(int)CardRect::R_tier2].right + tempX, m_rRect[(int)CardRect::R_tier2].bottom + tempY };
		DrawText(memdc, m_tStr[(int)CardRect::R_tier2], lstrlen(m_tStr[(int)CardRect::R_tier2]), &temp, DT_LEFT | DT_WORDBREAK);

	}
	if (m_cImg[(int)CardRect::R_tier3] != nullptr) {
		m_cImg[(int)CardRect::R_tier3].Draw(memdc, tempX + 8, tempY + 435, 45, 45,
			0, 0, 56, 56);
		temp = { m_rRect[(int)CardRect::R_tier3].left + tempX, m_rRect[(int)CardRect::R_tier3].top + tempY, m_rRect[(int)CardRect::R_tier3].right + tempX, m_rRect[(int)CardRect::R_tier3].bottom + tempY };
		DrawText(memdc, m_tStr[(int)CardRect::R_tier3], lstrlen(m_tStr[(int)CardRect::R_tier3]), &temp, DT_LEFT | DT_WORDBREAK);
	}

	SetTextColor(memdc, RGB(255, 255, 255));
	manaRect = { tempX + CARDWIDTH - 43, tempY , tempX + CARDWIDTH,  tempY + 49 };
	swprintf_s(manaStr, 3, L"%d", m_iMana);
	m_cManaImg[0].Draw(memdc, manaRect);
	DrawText(memdc, manaStr, lstrlen(manaStr), &manaRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	SelectObject(memdc, oldFont); DeleteObject(hFont);
}

void Card::SetTripord(int* tripord)
{
	for (int i = 0; i < 4; i++)
	{
		m_iTripord[i] = tripord[i];
	}
}
