#pragma once

#include "stdafx.h"

struct FPOINT
{
	float x;
	float y;
};

// 스크린에 그려질 오브젝트를 정의
class Object
{
public:
	Object() {}
	~Object() {}

	virtual void Update(float elapsed) {};

	//Render
public:
	virtual void Draw(HDC& memdc) {};

	//Gettor, Settor
public:
	virtual CImage GetImg() const = 0;
	RECT GetRect() const { return m_rRect; }

protected:
	// 메인 이미지
	// CImage* m_cImg;

	//충돌 처리 사각형
	RECT m_rRect;

	// 텍스쳐 위치
	POINT m_pPoint;

	// 텍스쳐 오프셋
	POINT m_pOffset;

	// 오브젝트 위치
	FPOINT m_Location;
};

