#pragma once
#include "CommonMonster.h"

class Bat : public CommonMonster
{
public:
	Bat();
	~Bat() {}

	virtual void Update(float elapsed) override;
	virtual bool Hit(int damage);

	//Render
public:
	virtual void Draw(HDC& memdc);
	virtual void ImgDraw(HDC& memdc);
	virtual void HpDraw(HDC& memdc);

	//Gettor, Settor
public:
	virtual CImage GetImg() const { return m_cImg; };
	
	virtual void SetStatus(MonsterState MS);

private:
	static CImage m_cImg;
};

