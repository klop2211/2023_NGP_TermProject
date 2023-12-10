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
	Player*		m_pOwner;		// 이 오브젝트를 가진 플레이어
	POINT		m_Speed;		// 이동속도
	ObjectType	m_ObjectType;	
	int			m_iDamage;		// 공격력(충돌시 가하는 데미지)
	int			m_iStunDamage;	// 무력화 수치(기존에는 Neutralization이라 표기했지만 생소한 영단어보다는 이해가 편하게 바꿈
	int			m_iDestruction;	// 부위파괴 수치
	int			m_iNamedDamage; // 네임드 추가데미지 기존 데미지에 이 수치를 + 하여 계산

	bool		m_bLife;		// 이 객체를 밖에서 확인하고 지우기 위한 bool 값


	CImage*		m_pImg;			// 그릴 이미지
	int			m_iRectSize;	// 오브젝트 크기

	int			m_iFrameMax;	// 스프라이트 이미지의 프레임 수
	int			m_iFrameIdx;	// 현재 스프라이트 이미지의 프레임 번호
	float		m_fFrameTime;	// 현재 스프라이트가 사용된 시간
	int			m_iFrameSpeed;

	float		m_fLiveTime;	// 오브젝트의 생존 시간

};

