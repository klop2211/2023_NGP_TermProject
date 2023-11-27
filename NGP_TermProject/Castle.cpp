#include "Castle.h"

Castle::Castle()
{
	m_cImg.Load(TEXT("윈플 텀프 이미지\\성.png"));
	m_iCastleMovement = 0;
	m_iCastleHp = 1000;
}

Castle::~Castle()
{
	m_cImg.Destroy();
}

void Castle::Update(float elapsed)
{
	if (m_iCastleMovement >= 1)
	{
		++m_iCastleMovement;
	}
}

void Castle::HitCastle(int damage)
{
	m_iCastleMovement = 1;
	m_iCastleHp -= damage;
}

void Castle::Draw(HDC& memdc)
{
	HBRUSH hBrush, oldBrush;
	// 성 그리기
	if (m_iCastleMovement >= 1) {
		int move = 4;
		move *= m_iCastleMovement % 2 ? 1 : -1;
		m_cImg.Draw(memdc, 0 + move, 0, 259 + move, 635,
			0, 0, m_cImg.GetWidth(), m_cImg.GetHeight());
		if (m_iCastleMovement == 6)
		{
			m_iCastleMovement = 0;
		}
	}
	else
	{
		DrawCastle(memdc);
	}

	//성체력 출력
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, 0, 650, 0 + ((double)m_iCastleHp / 1000) * 260, 670);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);
}

void Castle::DrawCastle(HDC& memdc)
{
	m_cImg.Draw(memdc, 0, 0, 259, 635,
		0, 0, m_cImg.GetWidth(), m_cImg.GetHeight());
}

CImage Castle::GetImg() const
{
	return m_cImg;
}
