#pragma once
#include "Monster.h"

class Papyrus : public Monster
{
public:
	Papyrus();
	~Papyrus();


private:
	// 부위파괴가 진행 되었는지
	bool m_bBreaked;
	// 부위파괴나 무력화로 누워있는지?
	bool m_bCanDown;

	// 부위파괴를 넣은 수ㅊㅣ
	int m_iBreakCount;
	// 무력화를 넣은 수치?
	int m_iKnockDown;

	// 넘어져있는 시간
	float m_fBreakTimer;
};


