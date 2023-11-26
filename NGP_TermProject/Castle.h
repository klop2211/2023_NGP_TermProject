#pragma once
#include "Object.h"

class Castle : public Object
{
public:
	Castle();
	~Castle();

	void Update(float elapsed);

// Render
public:
	void Draw(HDC& memdc);
	void DrawCastle(HDC& memdc);

//Gettor Settor
public:
	virtual CImage GetImg() const;

private:
	// 성 공격 받았을 떄 흔들림 효과
	int m_iCastleMovement;
	// 성 체력
	int m_iCastleHp;

	// 성 이미지
	CImage m_cImg;
};

