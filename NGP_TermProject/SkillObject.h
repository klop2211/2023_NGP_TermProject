#pragma once
#include "Object.h"

#define SKILLOBJECT_SIZE 100
#define SKILLOBEJCT_FRAMESPEED 6

enum ObjectType {
	Drop_Spear = 100, Meteor_Spear, Explosion, Wall, Hurricane, None, Ice, Fire, Knockdown, SowrdLight,
	Rotation_Spear, Airborne_Spear, Red_Spear, Earthquake, Flame_Zone, Drop_Red_Spear, Yellow_Spear, Purple_Spear
};


class SkillObject : public Object
{
public:
	SkillObject(const ObjectType& objectType, const FPOINT& location, const int& speed,
		const int& damage, const int& stunDamage, const int& destruction);
	~SkillObject();

	virtual void Update(float elapsed);

	//Render
public:
	virtual void Draw(HDC& memDc);

	//Gettor, Settor
public:
	CImage GetImg() const { return *m_pImg; }
	int GetStunDamage() const { return m_iStunDamage; }
	int GetDamage() const { return m_iDamage; }
	int GetDestruction() const { return m_iDestruction; }

	void SetImg(const TCHAR* str);
	void SetSpeed(const int speed) { m_iSpeed = speed; }
	void SetDamage(const int damege) { m_iDamage = damege; }
	void SetStunDamage(const int stunDamage) { m_iStunDamage = stunDamage; }
	void SetDestruction(const int destruction) { m_iDestruction = destruction; }
	void SetRectByLocation() {
		m_rRect.left = (int)m_Location.x;
		m_rRect.top = (int)m_Location.y;
		m_rRect.right = (int)m_Location.x + m_iRectSize;
		m_rRect.bottom = (int)m_Location.y + m_iRectSize;
	}

private:
	int			m_iSpeed;		// �̵��ӵ�
	int			m_iDamage;		// ���ݷ�(�浹�� ���ϴ� ������)
	int			m_iStunDamage;	// ����ȭ ��ġ(�������� Neutralization�̶� ǥ�������� ������ ���ܾ�ٴ� ���ذ� ���ϰ� �ٲ�
	int			m_iDestruction;	// �����ı� ��ġ
	ObjectType	m_ObjectType;	

	CImage*		m_pImg;			// �׸� �̹���
	int			m_iRectSize;	// ������Ʈ ũ��

	int			m_iFrameMax;	// ��������Ʈ �̹����� ������ ��
	int			m_iFrameIdx;	// ���� ��������Ʈ �̹����� ������ ��ȣ
	float		m_fFrameTime;	// ���� ��������Ʈ�� ���� �ð�
	int			m_iFrameSpeed;

};

