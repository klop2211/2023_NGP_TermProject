#pragma once

#include "Monster.h"
#include "../NGP_TermProject/SkillObject.h"

#include <vector>

class SkillObjectInfo : public Monster
{
public:
	SkillObjectInfo(BYTE, ObjectType, POINT, int);
	~SkillObjectInfo();

	virtual void Update(float ElaspedTime);

	// �浹�� ��ü �߰�
	void AddSerialNum(MonsterType MT, int SerialNum);

public:
	ObjectType GetObjectType() { return m_ObjectType; }

	int GetOwnedClientNum() { return m_iOwnerClientNum; }

	std::vector<int>& GetCollisionList(int n) { return m_CollisionList[n]; }
	void AddCollisionList(MonsterType MT, int n) { m_CollisionList[(int)MT].push_back(n); }

private:
	int m_iOwnerClientNum;
	ObjectType m_ObjectType;

	// �� �� �浹 �����ʰ�
	array<std::vector<int>, 3> m_CollisionList;
};
