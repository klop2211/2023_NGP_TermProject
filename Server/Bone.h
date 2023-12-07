#pragma once
#include "Monster.h"


class Bone : public Monster
{
public:
	enum BoneType {UnBreak, Break1, Break2};

	Bone(int SN, BoneType Num, FPOINT point);
	~Bone();

public:
	void Update(float ElapsedTime);
	void UbPatternUpdate(float ElapsedTime);
	void BPattern1Update(float ElapsedTime);
	void BPattern2Update(float ElapsedTime);

	float GetLifeTimer() { return m_fLifeTimer; }
	float GetCanDie() { return m_bCanDie; }

private:
	BoneType m_BoneType;
	int m_iRandValue;
	bool m_bCanDown; 
	bool m_bCanDie;

	float m_fLifeTimer;
	float m_fXLocation;
	float m_fXSize;
};

