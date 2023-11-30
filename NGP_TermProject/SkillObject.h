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
	int			m_iSpeed;		// 이동속도
	int			m_iDamage;		// 공격력(충돌시 가하는 데미지)
	int			m_iStunDamage;	// 무력화 수치(기존에는 Neutralization이라 표기했지만 생소한 영단어보다는 이해가 편하게 바꿈
	int			m_iDestruction;	// 부위파괴 수치
	ObjectType	m_ObjectType;	

	CImage*		m_pImg;			// 그릴 이미지
	int			m_iRectSize;	// 오브젝트 크기

	int			m_iFrameMax;	// 스프라이트 이미지의 프레임 수
	int			m_iFrameIdx;	// 현재 스프라이트 이미지의 프레임 번호
	float		m_fFrameTime;	// 현재 스프라이트가 사용된 시간
	int			m_iFrameSpeed;

};

