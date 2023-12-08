#include "Player.h"
#include "SkillObject.h"


SkillObject::SkillObject(const ObjectType objectType, Player* owner)
{
	m_ObjectType = objectType;

	m_pOwner = owner;

	m_Location = m_pOwner->GetLocation();

	m_bLife = true;

	m_iDamage = m_pOwner->GetDamage();
	m_iStunDamage = m_pOwner->GetStunDamage();
	m_iDestruction = m_pOwner->GetDestruction();
	m_iNamedDamage = m_pOwner->GetNamedDamage();

	// 생성시 위치 보정 값
	int dx = 0, dy = 0;

	// player 위치 기반 스킬 오브젝트 생성
	switch (m_ObjectType)
	{
	case Drop_Spear:
		SetImg(L"./윈플 텀프 이미지/창술사_청룡진_창떨구기.png");
		dx = m_pOwner->GetDir() == Left ? -100 : 200;
		dy = 400;
		m_Location = owner->GetLocation();
		m_Location.x += dx;
		m_Location.y -= dy;
		m_iRectSize = 150;
		m_Speed = POINT{ 0,-70 };
		break;
	case Meteor_Spear:
		break;
	case Explosion:
		break;
	case Wall:
		SetImg(L"./\\윈플 텀프 이미지\\벽.png");
		dx = m_pOwner->GetDir() == Left ? -100 : 200;
		dy = 0;
		m_iRectSize = 150;
		m_Speed = POINT{ 0,0 };
		break;
	case Hurricane:
		SetImg(L"./\\윈플 텀프 이미지\\회오리.png");
		dx = m_pOwner->GetDir() == Left ? -150 : 250;
		dy = 0;
		m_iRectSize = 200;
		m_Speed = POINT{ 0,0 };
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
		if (m_pOwner->GetDir() == Left) {
			SetImg(L"./\\윈플 텀프 이미지\\검기(left).png");
			dx = -100;
			m_Speed = POINT{ -500,0 };
		}
		else {
			SetImg(L"./\\윈플 텀프 이미지\\검기.png");
			dx = 200;
			m_Speed = POINT{ 500,0 };
		}
		dy = 0;
		m_iRectSize = 200;
		break;
	case Rotation_Spear:
		SetImg(L"./\\윈플 텀프 이미지\\회전하는창.png");
		dx = 0;
		dy = 0;
		m_iRectSize = 100;
		m_Speed = POINT{ 0,0 };
		break;
	case Airborne_Spear1:
		SetImg(L"./\\윈플 텀프 이미지\\회전하는창.png");
		dx = 25;
		dy = -75;
		m_iRectSize = 50;
		m_Speed = POINT{ 0,0 };
		break;
	case Airborne_Spear2:
		SetImg(L"./\\윈플 텀프 이미지\\회전하는창.png");
		dx = -75;
		dy = 25;
		m_iRectSize = 50;
		m_Speed = POINT{ 0,0 };

		break;
	case Airborne_Spear3:
		SetImg(L"./\\윈플 텀프 이미지\\회전하는창.png");
		dx = 125;
		dy = 25;
		m_iRectSize = 50;
		m_Speed = POINT{ 0,0 };

		break;
	case Red_Spear:
		if (m_pOwner->GetDir() == Left) {
			SetImg(L"./\\윈플 텀프 이미지\\적룡포 막타(left).png");
			m_Speed = POINT{ -400,0 };

		}
		else {
			SetImg(L"./\\윈플 텀프 이미지\\적룡포 막타.png");
			m_Speed = POINT{ 400,0 };
		}
		m_iRectSize = 200;
		dx = 0;
		dy = 0;
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

	m_Location = owner->GetLocation();
	m_Location.x += dx;
	m_Location.y -= dy;


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
	m_fFrameTime += m_iFrameSpeed * elapsed;
	m_iFrameIdx = (int)m_fFrameTime;

	m_Location.x += elapsed * m_Speed.x;
	m_Location.y += elapsed * m_Speed.y;

	switch (m_ObjectType)
	{
	case Drop_Spear:
		// 마지막 프레임으로 고정
		if (m_fFrameTime > m_iFrameMax) {
			m_fFrameTime = m_iFrameMax - 1;
			m_iFrameIdx = m_iFrameMax - 1;
		}
		// 마지막 프레임 까지 위치 고정
		if (m_iFrameIdx < m_iFrameMax - 1) {
			m_Location.x -= elapsed * m_Speed.x;
			m_Location.y -= elapsed * m_Speed.y;
		}
		// 객체가 땅에 닿으면 소멸
		if (m_Location.y < GROUNDYPOINT)
			m_bLife = false;
		break;
	case Meteor_Spear:
		break;
	case Explosion:
		break;
	case Wall:
		if (m_fLiveTime > 3.0f)
			m_bLife = false;
		break;
	case Hurricane:
		if (m_fLiveTime > 3.0f)
			m_bLife = false;
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
		// 마지막 프레임으로 고정
		if (m_fFrameTime > m_iFrameMax) {
			m_fFrameTime = m_iFrameMax - 1;
			m_iFrameIdx = m_iFrameMax - 1;
		}
		if (m_fLiveTime > 1.5f)
			m_bLife = false;

		break;
	case Rotation_Spear:
		if (m_fLiveTime > 5.f)
			m_bLife = false;
		break;
	case Airborne_Spear1:
		if (m_fLiveTime > 5.f)
			m_bLife = false;
		break;
	case Airborne_Spear2:
		if (m_fLiveTime > 5.f)
			m_bLife = false;
		break;
	case Airborne_Spear3:
		if (m_fLiveTime > 5.f)
			m_bLife = false;
		break;
	case Red_Spear:
		if (m_fLiveTime > 1.5f)
			m_bLife = false;
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
