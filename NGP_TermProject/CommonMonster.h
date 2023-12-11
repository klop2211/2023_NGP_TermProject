#pragma once
#include "Monster.h"

class CommonMonster : public Monster
{
public:
	CommonMonster() {}
	~CommonMonster() {}

	virtual void Update(float elapsed) override {};
	virtual bool Hit(int damage) { return 0; };

	//Render
public:
	virtual void Draw(HDC& memdc) {};
	virtual void ImgDraw(HDC& memdc) {};
	virtual void HpDraw(HDC& memdc) {};

	//Gettor, Settor
public:
	virtual CImage GetImg() const = 0;

	virtual void SetStatus(MonsterState MS) = 0;

protected:
	MonsterState m_Status;

	// 공격 상태 메세지가 넘어올때 키고, 공격 모션 한 번 출력후 끔
	bool m_bCanAttack;
};

