#include "SkillObject.h"

SkillObject::SkillObject(const ObjectType& objectType, const FPOINT& location, const int& speed,
	const int& damage, const int& stunDamage, const int& destruction)
{
	m_ObjectType = objectType;

	m_Location = location;

	m_iSpeed = speed;		// �̵��ӵ�
	m_iDamage = damage;		// ���ݷ�(�浹�� ���ϴ� ������)
	m_iStunDamage = stunDamage;	// ����ȭ ��ġ(�������� Neutralization�̶� ǥ�������� ������ ���ܾ�ٴ� ���ذ� ���ϰ� �ٲ�
	m_iDestruction = destruction;	// �����ı� ��ġ

	switch (m_ObjectType)
	{
	case Drop_Spear:
		SetImg(L"./���� ���� �̹���/â����_û����_â������.png");
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

	m_iRectSize = SKILLOBJECT_SIZE;	// ������Ʈ ũ��

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
	// ��������Ʈ ������ ����
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
