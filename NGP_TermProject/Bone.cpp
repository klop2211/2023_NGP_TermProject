#include "stdafx.h"

#include "Bone.h"
#include <windef.h>

#include "Random.h"

CImage Bone::m_cImg;

Bone::Bone(MonsterType MT, int x, int y)
{
	if (m_cImg.IsNull())
	{
		m_cImg.Load(TEXT("적관련\\파피루스.png"));
	}

	switch (MT)
	{
	case MonsterType::UBBone:
		m_iNum = 0;
		break;
	case MonsterType::BBone1:
		m_iNum = 1;
		break;
	case MonsterType::BBone2:
		m_iNum = 2;
		break;
	default:
		break;
	}

	m_Location = { (float)x, (float)y };
	m_iCount = 0;

	if (m_iNum == 0) {
		m_pOffset = { 49, 54 }; 
		m_pStart = POINT{ 99, 109 };
		m_Size = { m_pOffset.x * 4, m_pOffset.y * 4 };
		m_fLifeTimer = 1.5f;
	}
	else if (m_iNum == 1) {
		m_pOffset = { 33, 8 }; 
		m_pStart = { 246, 371 };
		m_iRandValue = 7;
		m_Size = { m_iRandValue * m_iRandValue * m_iRandValue, m_pOffset.y * m_iRandValue };
	}
	else if (m_iNum == 2) {
		m_pOffset = { 11, 11 }; 
		m_pStart = { 246, 325 };
		m_Size = { m_pOffset.x * 3, m_pOffset.y * 3 };
		m_iCount = RandomGen::GetRand(4);
	}

	m_fWait = 0;
	m_iCurrentHp = m_iMaxHp = 0;

	m_bCanDie = false;
}

void Bone::Draw(HDC& memdc)
{
	switch (m_iNum)
	{
	case 0:
		m_cImg.Draw(memdc, m_Location.x, m_Location.y, m_Size.x, m_Size.y,
			m_pStart.x, m_pStart.y, m_pOffset.x - 1, m_pOffset.y - 1);
		break;
	case 1:
		m_cImg.Draw(memdc, m_Location.x, m_Location.y, m_Size.x, m_Size.y,
			m_pStart.x, m_pStart.y, m_pOffset.x - 1, m_pOffset.y - 1);
		break;
	case 2:
		m_cImg.Draw(memdc, m_Location.x, m_Location.y, m_Size.x, m_Size.y,
			m_pStart.x + m_pOffset.x * (m_iCount % 4), m_pStart.y, m_pOffset.x - 1, m_pOffset.y - 1);
		break;
	default:
		break;
	}
}

void Bone::Update(float elapsed)
{
	m_fWait += elapsed;
	if(m_fWait > 0.25f)
	{
		m_fWait = 0.f;
		switch (m_iNum)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			m_iCount++;
			break;
		default:
			break;
		}
	}

	//m_fWait += elapsed;
	//switch (m_iNum)
	//{
	//case 0:
	//	if (m_fWait > MAX_FRAMERATE * 2) {
	//		++m_iCount;
	//		if (m_iCount == 50)
	//			m_bCanDie = true;
	//		else
	//		{
	//			MoveXY(-m_iSpeed, 0, elapsed);
	//		}
	//		m_fWait = 0.f;
	//	}
	//	break;
	//case 1:
	//	if (m_fWait > MAX_FRAMERATE * 5) {
	//		if (m_bCanDown) {
	//			MoveXY(0, m_iSpeed, elapsed);
	//			if (m_rRect.bottom > GROUNDYPOINT) {
	//				m_bCanDie = true;
	//			}
	//		}
	//		else {
	//			m_rRect.left -= 20;
	//			m_pOffset.x += 20;
	//			if (m_rRect.right - m_rRect.left > m_pPoint.x * m_iRandValue * 2) {
	//				m_bCanDown = true;
	//			}
	//		}
	//	}
	//	break;
	//case 2:
	//	if (m_fWait > MAX_FRAMERATE * 5) {
	//		m_fWait = 0.f;
	//		++m_iCount;
	//		if (m_bCanDown) {
	//			MoveXY(0, m_iSpeed, elapsed);
	//			if (m_rRect.bottom > GROUNDYPOINT) {
	//				m_rRect.bottom = GROUNDYPOINT;
	//				m_rRect.top = GROUNDYPOINT - m_pOffset.x;
	//				--m_iCount;

	//				if (m_fWait == 450) {
	//					m_bCanDie = true;
	//				}
	//			}
	//		}
	//		else {
	//			MoveXY(0, 70, elapsed);
	//			if (m_rRect.bottom < 0) {
	//				int temp = RandomGen::GetRand(m_rRect.left - 100) + 100;
	//				m_iCount = RandomGen::GetRand(4);
	//				m_rRect = { temp,-m_pOffset.y,temp + m_pOffset.x,0 };
	//				m_bCanDown = true;
	//				m_fWait = 0;
	//			}
	//		}
	//	}
	//	break;
	//default:
	//	break;
	//}
	SyncLocationAtRect();
}