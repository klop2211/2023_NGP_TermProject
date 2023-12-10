#include "SkillObject.h"

SkillObjectInfo::SkillObjectInfo(BYTE ClientNum, ObjectType ObjectType, POINT location, int size) :
	m_iOwnerClientNum(ClientNum),
	m_ObjectType(ObjectType),
	Monster(0)
{
	m_Location = location;
	m_Size = { size, size };

	//m_CollisionList.reserve(3);
	//for (int i = 0; i < 3; i++)
	//{
	//	std::vector<int> temp;
	//	m_CollisionList.push_back(temp);
	//}
}

SkillObjectInfo::~SkillObjectInfo()
{
}

void SkillObjectInfo::Update(float ElaspedTime)
{
}

void SkillObjectInfo::AddSerialNum(MonsterType MT, int SerialNum)
{
	m_CollisionList[(int)MT].push_back(SerialNum);
}
