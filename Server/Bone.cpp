#include "Common.h"
#include "Bone.h"
#include "Random.h"

#define GROUNDYPOINT 634

Bone::Bone(int SN, BoneType BT, FPOINT point) : Monster(SN)
{
	m_bCanDown = false;
	m_iCurrentHp = m_iMaxHp = 0;
	m_bCanDie = false;
	m_BoneType = BT;
	m_fXLocation = 0.f;

	switch (BT)
	{
	case 0:
	{
		m_Size = { 49 * 4, 54 * 4 };
		m_Location = { (point.x - m_Size.x), (point.y - m_Size.y) };
		m_iSpeed = 8;
		m_fLifeTimer = 1.5f;
	}
		break;
	case 1:
	{
		m_iRandValue = 7;
		m_Size = { 1, 8 * m_iRandValue };
		m_Location = { (point.x - m_Size.x), (point.y - m_Size.y - 100) };
		m_iSpeed = 15;
		m_fXLocation = m_Location.x;
		m_fXSize = m_Size.x;
	}
		break;
	case 2:
	{
		m_Size = { 11 * 3, 11 * 3};
		m_Location = { point.x, point.y };
		m_iSpeed = 20;
	}
		break;
	default:
		break;
	}
}

Bone::~Bone()
{
}

void Bone::Update(float ElapsedTime)
{
	switch (m_BoneType)
	{
	case Bone::UnBreak:
		UbPatternUpdate(ElapsedTime);
		break;
	case Bone::Break1:
		BPattern1Update(ElapsedTime);
		break;
	case Bone::Break2:
		BPattern2Update(ElapsedTime);
		break;
	default:
		break;
	}
}

void Bone::UbPatternUpdate(float ElapsedTime)
{
	m_fLifeTimer -= ElapsedTime;
	if (m_fLifeTimer < 0.f)
	{
		m_bCanDie = true;
	}

	m_Location.x -= (m_iSpeed * 20 * ElapsedTime);
}

void Bone::BPattern1Update(float ElapsedTime)
{
	if (m_bCanDown)
	{
		m_Location.y += (m_iSpeed * 20 * ElapsedTime);

		if (m_Location.y + m_Size.y > GROUNDYPOINT)
		{
			m_bCanDie = true;
		}
	}
	else
	{
		m_fXSize += 20 * m_iSpeed * ElapsedTime;
		m_fXLocation -= 20 * m_iSpeed * ElapsedTime;

		m_Size.x = m_fXSize;
		m_Location.x = m_fXLocation;

		if (m_Size.x > /*m_Location.x **/ m_iRandValue * m_iRandValue * m_iRandValue)
		{
			m_bCanDown = true;
		}
	}
}

void Bone::BPattern2Update(float ElapsedTime)
{
	if (m_bCanDown)
	{
		m_Location.y += (m_iSpeed * 20 * ElapsedTime);

		if (m_Location.y + m_Size.y > GROUNDYPOINT)
		{
			m_bCanDie = true;
		}
	}
	else
	{
		m_Location.y -= (m_iSpeed * 20 * ElapsedTime);
		if (m_Location.y + m_Size.y < 0)
		{
			int temp = Random::GetRand(m_Location.x - 100) + 100;
			m_iRandValue = Random::GetRand(4);
			m_Location = { (float)temp, m_Location.y };
			m_bCanDown = true;
		}
	}
}
