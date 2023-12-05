#pragma once

#include "stdafx.h"

//struct FPOINT
//{
//	float x;
//	float y;
//};

// ��ũ���� �׷��� ������Ʈ�� ����
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
	RECT GetRect() const { return m_rRect; }
	void SetRect(RECT rect) { m_rRect = rect; }
	void SetRect(LONG l, LONG t, LONG r, LONG b) { m_rRect = RECT{ l,t,r,b }; }
	FPOINT GetLocation() { return m_Location; }

protected:
	// ���� �̹���
	// CImage* m_cImg;

	//�浹 ó�� �簢��, ��ġ
	RECT m_rRect;

	// �ؽ��� ��ġ
	POINT m_pPoint;

	// �ؽ��� ������
	POINT m_pOffset;

	// ������Ʈ ��ġ
	FPOINT m_Location;
};

