#pragma once
#include "Monster.h"

class Bone : public Monster {
public:
	int m_iNum, m_iRandValue;
	POINT m_pStart;
	float m_fLifeTimer;

	Bone() {}
	Bone(MonsterType MT, int x, int y);

	void Draw(HDC& memdc);
	void Update(float elapsed);

	virtual CImage GetImg() const { return m_cImg; }

public:
	static CImage m_cImg;
};

