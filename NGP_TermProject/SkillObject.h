#pragma once
#include "Object.h"

#define SKILLOBJECT_SIZE 100
#define SKILLOBEJCT_FRAMESPEED 6

class Player;

enum ObjectType {
	Drop_Spear = 100, Meteor_Spear, Explosion, Wall, Hurricane, None, Ice, Fire, Knockdown, SowrdLight,
	Rotation_Spear, Airborne_Spear1, Airborne_Spear2, Airborne_Spear3, Red_Spear, Earthquake, Flame_Zone, Drop_Red_Spear1, Drop_Red_Spear2, Yellow_Spear, Purple_Spear
};


class SkillObject : public Object
{
public:
	SkillObject(const ObjectType objectType, Player* owner);
	~SkillObject();

	virtual void Update(float elapsed);

	//Render
public:
	virtual void Draw(HDC& memDc);

	//Gettor, Settor
public:
	CImage GetImg() const { return *m_pImg; }
	int GetDamage() const { return m_iDamage; }
	int GetStunDamage() const { return m_iStunDamage; }
	int GetDestruction() const { return m_iDestruction; }
	int GetNamedDamage() const { return m_iNamedDamage; }
	ObjectType GetObjectType() const { return m_ObjectType; }
	bool GetLife() const { return m_bLife; }


	void SetImg(const TCHAR* str);
	void SetSpeed(const POINT speed) { m_Speed = speed; }
	void SetRectByLocation() {
		m_rRect.left = (int)m_Location.x;
		m_rRect.top = (int)m_Location.y;
		m_rRect.right = (int)m_Location.x + m_iRectSize;
		m_rRect.bottom = (int)m_Location.y + m_iRectSize;
	}

private:
	Player*		m_pOwner;		// �� ������Ʈ�� ���� �÷��̾�
	POINT		m_Speed;		// �̵��ӵ�
	ObjectType	m_ObjectType;	
	int			m_iDamage;		// ���ݷ�(�浹�� ���ϴ� ������)
	int			m_iStunDamage;	// ����ȭ ��ġ(�������� Neutralization�̶� ǥ�������� ������ ���ܾ�ٴ� ���ذ� ���ϰ� �ٲ�
	int			m_iDestruction;	// �����ı� ��ġ
	int			m_iNamedDamage; // ���ӵ� �߰������� ���� �������� �� ��ġ�� + �Ͽ� ���

	bool		m_bLife;		// �� ��ü�� �ۿ��� Ȯ���ϰ� ����� ���� bool ��


	CImage*		m_pImg;			// �׸� �̹���
	int			m_iRectSize;	// ������Ʈ ũ��

	int			m_iFrameMax;	// ��������Ʈ �̹����� ������ ��
	int			m_iFrameIdx;	// ���� ��������Ʈ �̹����� ������ ��ȣ
	float		m_fFrameTime;	// ���� ��������Ʈ�� ���� �ð�
	int			m_iFrameSpeed;

	float		m_fLiveTime;	// ������Ʈ�� ���� �ð�

};

