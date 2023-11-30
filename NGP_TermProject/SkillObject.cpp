#include "SkillObject.h"

SkillObject::SkillObject(const ObjectType& objectType, const FPOINT& location, const int& speed,
	const int& damage, const int& stunDamage, const int& destruction)
{
	m_ObjectType = objectType;

	m_Location = location;

	m_iSpeed = speed;		// 이동속도
	m_iDamage = damage;		// 공격력(충돌시 가하는 데미지)
	m_iStunDamage = stunDamage;	// 무력화 수치(기존에는 Neutralization이라 표기했지만 생소한 영단어보다는 이해가 편하게 바꿈
	m_iDestruction = destruction;	// 부위파괴 수치

	switch (m_ObjectType)
	{
	case Drop_Spear:
		SetImg(L"./윈플 텀프 이미지/창술사_청룡진_창떨구기.png");
		m_iRectSize = 150;
		break;
	case Meteor_Spear:
		break;
	case Explosion:
		break;
	case Wall:
		break;
	case Hurricane:
		break;
	case None:
		break;
	case Ice:
		break;
	case Fire:
		break;
	case Knockdown:
		break;
	case SowrdLight:
		break;
	case Rotation_Spear:
		break;
	case Airborne_Spear:
		break;
	case Red_Spear:
		break;
	case Earthquake:
		break;
	case Flame_Zone:
		break;
	case Drop_Red_Spear:
		break;
	case Yellow_Spear:
		break;
	case Purple_Spear:
		break;
	default:
		break;
	}

	m_iRectSize = SKILLOBJECT_SIZE;	// 오브젝트 크기

	m_iFrameSpeed = SKILLOBEJCT_FRAMESPEED;

	SetRectByLocation();
}

SkillObject::~SkillObject()
{
	if (m_pImg != NULL) {
		m_pImg->Destroy();
		delete m_pImg;
		m_pImg = NULL;
	}

}

void SkillObject::Update(float elapsed)
{
	switch (m_ObjectType)
	{
	case Drop_Spear:

		break;
	case Meteor_Spear:
		break;
	case Explosion:
		break;
	case Wall:
		break;
	case Hurricane:
		break;
	case None:
		break;
	case Ice:
		break;
	case Fire:
		break;
	case Knockdown:
		break;
	case SowrdLight:
		break;
	case Rotation_Spear:
		break;
	case Airborne_Spear:
		break;
	case Red_Spear:
		break;
	case Earthquake:
		break;
	case Flame_Zone:
		break;
	case Drop_Red_Spear:
		break;
	case Yellow_Spear:
		break;
	case Purple_Spear:
		break;
	default:
		break;
	}
	SetRectByLocation();
	// 스프라이트 프레임 조정
	m_fFrameTime += m_iFrameSpeed * elapsed;
	m_iFrameIdx = (int)m_fFrameTime;
	if (m_fFrameTime > m_iFrameMax) {
		m_fFrameTime = 0.f;
		m_iFrameIdx = 0;
	}

}

void SkillObject::Draw(HDC& memDc)
{
	m_pImg->Draw(memDc, m_rRect.left, m_rRect.top, m_rRect.right - m_rRect.left, m_rRect.bottom - m_rRect.top, 0, m_pImg->GetHeight() / m_iFrameMax * m_iFrameIdx, m_pImg->GetWidth(), m_pImg->GetHeight() / m_iFrameMax);
}

void SkillObject::SetImg(const TCHAR* str)
{
	m_pImg->Destroy();
	m_pImg->Load(str);
	m_iFrameMax = m_pImg->GetHeight() / 32;
	m_iFrameIdx = 0;
	m_fFrameTime = 0;
}
