#include "Card.h"

#include "stdafx.h"
#include <windef.h>

Card::Card(CImage* manaImg)
{
	m_rRect = new RECT[4];
	m_rRect[R_main] = { 30,160,277,245 };
	m_rRect[R_tier1] = { 60,265,300,305 };//240/40
	m_rRect[R_tier2] = { 60,355,300,395 };//240/40
	m_rRect[R_tier3] = { 60,440,300,480 };//240/40
	m_bIsValid = true, m_bCheep = false;

	m_cManaImg = manaImg;
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

void Card::handDraw(HDC& memdc)
{
	HBRUSH hBrush, oldBrush;
	RECT rect = { m_pPoint->x, m_pPoint->y, m_pPoint->x + 187, m_pPoint->y + 35 };
	TCHAR manaStr[3];

	hBrush = CreateSolidBrush(RGB(14, 15, 16));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, point.x, point.y, point.x + 187, point.y + 300);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);

	hBrush = CreateSolidBrush(RGB(25, 28, 33));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, point.x, point.y, point.x + 187, point.y + 35);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);

	SetBkMode(memdc, TRANSPARENT);
	SetTextColor(memdc, RGB(255, 255, 255));
	DrawText(memdc, nameStr, lstrlen(nameStr), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	//SetTextColor(memdc, RGB(0, 0, 0));
	skill.Draw(memdc, point.x + 96 - 40, point.y + 40, 80, 80, 0, 0, 100, 100);
	manaImg[0].Draw(memdc, point.x + 160, point.y, 27, 30, 0, 0, 102, 115);
	rect = { point.x + 160, point.y, point.x + 160 + 27, point.y + 30 };
	swprintf_s(manaStr, 3, L"%d", Mana);
	DrawText(memdc, manaStr, lstrlen(manaStr), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}

void Card::closeDraw(HDC& memdc)
{
	int tempX = point.x - (CARDWIDTH - CARDMINIWIDTH) / 2;
	int tempY = point.y - CARDHEIGHT;
	mainDraw(memdc, tempX, tempY);
}

void Card::dragDraw(HDC& memdc)
{
	int tempX = point.x - (CARDWIDTH - CARDMINIWIDTH) / 2;
	int tempY = point.y;
	mainDraw(memdc, tempX, tempY);
}

void Card::mainDraw(HDC& memdc, int tempX, int tempY)
{
	SetTextColor(memdc, RGB(205, 205, 205));
	RECT temp;
	HFONT hFont, oldFont;
	RECT manaRect;
	TCHAR manaStr[3];

	img[0].Draw(memdc, tempX, tempY, CARDWIDTH, CARDHEIGHT,
		0, 0, CARDWIDTH, CARDHEIGHT);
	temp = { rect[R_main].left + tempX, rect[R_main].top + tempY, rect[R_main].right + tempX, rect[R_main].bottom + tempY };
	DrawText(memdc, str[R_main], lstrlen(str[R_main]), &temp, DT_LEFT | DT_WORDBREAK);

	hFont = CreateFont(13, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"");
	oldFont = (HFONT)SelectObject(memdc, hFont);

	if (img[R_tier1] != nullptr) {
		img[R_tier1].Draw(memdc, tempX + 7, tempY + 264, 44, 44,
			0, 0, 56, 56);
		temp = { rect[R_tier1].left + tempX, rect[R_tier1].top + tempY, rect[R_tier1].right + tempX, rect[R_tier1].bottom + tempY };
		DrawText(memdc, str[R_tier1], lstrlen(str[R_tier1]), &temp, DT_LEFT | DT_WORDBREAK);

	}
	if (img[R_tier2] != nullptr) {
		img[R_tier2].Draw(memdc, tempX + 8, tempY + 351, 45, 45,
			0, 0, 56, 56);
		temp = { rect[R_tier2].left + tempX, rect[R_tier2].top + tempY, rect[R_tier2].right + tempX, rect[R_tier2].bottom + tempY };
		DrawText(memdc, str[R_tier2], lstrlen(str[R_tier2]), &temp, DT_LEFT | DT_WORDBREAK);

	}
	if (img[R_tier3] != nullptr) {
		img[R_tier3].Draw(memdc, tempX + 8, tempY + 435, 45, 45,
			0, 0, 56, 56);
		temp = { rect[R_tier3].left + tempX, rect[R_tier3].top + tempY, rect[R_tier3].right + tempX, rect[R_tier3].bottom + tempY };
		DrawText(memdc, str[R_tier3], lstrlen(str[R_tier3]), &temp, DT_LEFT | DT_WORDBREAK);
	}

	SetTextColor(memdc, RGB(255, 255, 255));
	manaRect = { tempX + CARDWIDTH - 43, tempY , tempX + CARDWIDTH,  tempY + 49 };
	swprintf_s(manaStr, 3, L"%d", Mana);
	manaImg[0].Draw(memdc, manaRect);
	DrawText(memdc, manaStr, lstrlen(manaStr), &manaRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	SelectObject(memdc, oldFont); DeleteObject(hFont);
}