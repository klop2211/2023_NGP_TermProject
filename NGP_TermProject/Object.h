#pragma once

// 스크린에 그려질 오브젝트를 정의
class Object
{
public:
	Object() {}
	~Object() {}

	virtual void Update(float elapsed) = 0;

	//Render
public:
	virtual void Draw(HDC& memdc) = 0;
	//Gettor, Settor
public:
	CImage* GetImg() const { return m_cImg; }
	RECT GetRect() const { return m_rRect; }

protected:
	// 메인 이미지
	CImage* m_cImg;

	//충돌 처리 사각형
	RECT m_rRect;

	// 위치 크기
	POINT m_pPoint, m_pOffset;
};

