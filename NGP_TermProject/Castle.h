#pragma once
#include "Object.h"
#include "CastleInteraction.h"

class Castle : public Object, public CastleInteraction
{
public:
	Castle();
	~Castle();

	void Update(float elapsed);
	void HitCastle(int damage);

// Render
public:
	void Draw(HDC& memdc);
	void DrawCastle(HDC& memdc);

//Gettor Settor
public:
	virtual CImage GetImg() const;

	void SetCurrentHp(int hp) { m_iCastleHp = hp; m_iCastleMovement = 1; }

private:
	// �� ���� �޾��� �� ��鸲 ȿ��
	int m_iCastleMovement;
	// �� ü��
	int m_iCastleHp;

	// �� �̹���
	CImage m_cImg;
};

