#include "stdafx.h"

#include "Bone.h"
#include <windef.h>

Bone::Bone(int m_iNum, int x, int y)
{
	if (m_cImg.IsNull())
	{
		m_cImg.Load(TEXT(""));
	}

	this->m_iNum = m_iNum;
	if (m_iNum == 0) {
		m_pPoint = { 49, 54 };
		m_pStart = POINT{ 99, 109 };
		m_pOffset = { m_pPoint.x * 4, m_pPoint.y * 4 };
		m_rRect = { x - m_pOffset.x, y - m_pOffset.y, x , y };
		m_iSpeed = 16;
		m_bCanDown = false;
	}
	else if (m_iNum == 1) {
		m_pPoint = { 33, 8 };
		m_pStart = { 246, 371 };
		m_iRandValue = GetRand(5) + 5;
		m_pOffset = { 1, m_pPoint.y * m_iRandValue };
		m_rRect = { x - m_pOffset.x, y - m_pOffset.y - 100, x , y - 100 };
		m_iSpeed = 40;
		m_bCanDown = false;
	}
	else if (m_iNum == 2) {
		m_pPoint = { 11, 11 };
		m_pStart = { 246, 325 };
		m_pOffset = { m_pPoint.x * 3, m_pPoint.y * 3 };
		m_rRect = { x , y , x + m_pOffset.x , y + m_pOffset.y };
		m_iSpeed = 40;
		m_bCanDown = false;
	}

	m_iCount = 0, m_fWait = 0;
	m_iCurrentHp = m_iMaxHp = 0;

	m_bCanDie = false;
}

void Bone::Draw(HDC& memdc)
{
	POINT abc = { 1,1 };
	switch (m_iNum)
	{
	case 0:
		m_cImg.Draw(memdc, m_rRect.left, m_rRect.top, m_pOffset.x, m_pOffset.y,
			m_pStart.x, m_pStart.y, m_pPoint.x - 1, m_pPoint.y - 1);
		break;
	case 1:
		m_cImg.Draw(memdc, m_rRect.left, m_rRect.top, m_pOffset.x, m_pOffset.y,
			m_pStart.x, m_pStart.y, m_pPoint.x - 1, m_pPoint.y - 1);
		break;
	case 2:
		m_cImg.Draw(memdc, m_rRect.left, m_rRect.top, m_pOffset.x, m_pOffset.y,
			m_pStart.x + m_pPoint.x * (m_iCount % 4), m_pStart.y, m_pPoint.x - 1, m_pPoint.y - 1);
		break;
	default:
		break;
	}
}

void Bone::Update(float elapsed)
{
	m_fWait += elapsed;
	switch (m_iNum)
	{
	case 0:
		if (m_fWait > MAX_FRAMERATE * 2) {
			++m_iCount;
			if (m_iCount == 50)
				m_bCanDie = true;
			else
			{
				MoveXY(-m_iSpeed, 0, elapsed);
			}
			m_fWait = 0.f;
		}
		break;
	case 1:
		if (m_fWait > MAX_FRAMERATE * 5) {
			if (m_bCanDown) {
				MoveXY(0, m_iSpeed, elapsed);
				if (m_rRect.bottom > GROUNDYPOINT) {
					m_bCanDie = true;
				}
			}
			else {
				m_rRect.left -= 20;
				m_pOffset.x += 20;
				if (m_rRect.right - m_rRect.left > m_pPoint.x * m_iRandValue * 2) {
					m_bCanDown = true;
				}
			}
		}
		break;
	case 2:
		if (m_fWait > MAX_FRAMERATE * 5) {
			m_fWait = 0.f;
			++m_iCount;
			if (m_bCanDown) {
				MoveXY(0, m_iSpeed, elapsed);
				if (m_rRect.bottom > GROUNDYPOINT) {
					m_rRect.bottom = GROUNDYPOINT;
					m_rRect.top = GROUNDYPOINT - m_pOffset.x;
					--m_iCount;

					if (m_fWait == 450) {
						m_bCanDie = true;
					}
				}
			}
			else {
				MoveXY(0, 70, elapsed);
				if (m_rRect.bottom < 0) {
					int temp = GetRand(m_rRect.left - 100) + 100;
					m_iCount = GetRand(4);
					m_rRect = { temp,-m_pOffset.y,temp + m_pOffset.x,0 };
					m_bCanDown = true;
					m_fWait = 0;
				}
			}
		}
		break;
	default:
		break;
	}
}