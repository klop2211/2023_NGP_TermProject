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

	// 충돌된 객체 추가
	void AddSerialNum(MonsterType MT, int SerialNum);

public:
	ObjectType GetObjectType() { return m_ObjectType; }

	int GetOwnedClientNum() { return m_iOwnerClientNum; }

	std::vector<int>& GetCollisionList(int n) { return m_CollisionList[n]; }
	void AddCollisionList(MonsterType MT, int n) { m_CollisionList[(int)MT].push_back(n); }

private:
	int m_iOwnerClientNum;
	ObjectType m_ObjectType;

	// 두 번 충돌 되지않게
	array<std::vector<int>, 3> m_CollisionList;
};
