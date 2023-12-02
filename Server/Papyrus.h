#pragma once
#include "Monster.h"

class Papyrus : public Monster
{
public:
	Papyrus();
	~Papyrus();


private:
	// �����ı��� ���� �Ǿ�����
	bool m_bBreaked;
	// �����ı��� ����ȭ�� �����ִ���?
	bool m_bCanDown;

	// �����ı��� ���� ������
	int m_iBreakCount;
	// ����ȭ�� ���� ��ġ?
	int m_iKnockDown;

	// �Ѿ����ִ� �ð�
	float m_fBreakTimer;
};


