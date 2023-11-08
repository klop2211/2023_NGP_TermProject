#pragma once
#include "Monster.h"

class Bone : public Monster {
public:
	int m_iNum, m_iRandValue;
	POINT m_pStart;
	bool m_bCanDown;

	Bone() {}
	Bone(int num, int x, int y, CImage* boneImg);

	void Draw(HDC& memdc);
	void Update(float elapsed);

public:
	static CImage m_cImg;
};

