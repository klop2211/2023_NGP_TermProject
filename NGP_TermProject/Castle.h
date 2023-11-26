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
	// �� ���� �޾��� �� ��鸲 ȿ��
	int m_iCastleMovement;
	// �� ü��
	int m_iCastleHp;

	// �� �̹���
	CImage m_cImg;
};

