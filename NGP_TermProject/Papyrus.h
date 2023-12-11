#pragma once
#include "Monster.h"

enum PapyrusState {
	UP_Breaking = 0, UP_Move, UP_Pattern,
	P_Move = 0, P_Down, P_Pattern1, P_Pattern2, P_Die
};

class Papyrus : public Monster
{
public:
	Papyrus();
	~Papyrus() {}

	virtual void Update(float elapsed) override;
	virtual void BreakingUpdate(float elapsed);
	virtual void UnBreakingUpdate(float elapsed);

	virtual bool Hit(int att, int ammorBreak, int knockDown);

	//Render
public:
	virtual void Draw(HDC& memdc) override;
	virtual void ImgDraw(HDC& memdc);
	virtual void HpDraw(HDC& memdc);

	//Gettor, Settor
public:
	virtual CImage GetImg() const { return m_cImg; }

	virtual void SetStatus(BossStateType MS);
	void SetBreakCount(int count) { m_iBreakCount = count; };
	void SetKnockDown(int count) { m_iKnockDown = count;};
private:
	CImage m_cImg, m_cBossHpBar;
	static CImage m_cBoneImg;

	bool m_bBreaked, m_bCanDown;
	int m_iBreakCount, m_iKnockDown;

	float m_fBreakTimer;
	float m_fAttackTimer;

	PapyrusState m_Status;

	TCHAR m_sName[9], m_sHpStr[10];
	RECT m_rNameRect;
	RECT m_rHpRect;

	class Player* m_pPlayer;
	class Bone* m_pBone[2] = { nullptr, };
	Bone* m_pMiniBone[15] = { nullptr, };
};