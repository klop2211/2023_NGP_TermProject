#include "Common.h"
#include "PlayerInfo.h"

RECT PlayerInfo::GetBB() const
{
    RECT ReturnBB {
        m_PlayerLocation.x,
        m_PlayerLocation.y,
        m_PlayerLocation.x + PLAYERDEFAULTSIZE,
        m_PlayerLocation.y + PLAYERDEFAULTSIZE };

    return ReturnBB;
}

void PlayerInfo::AddSerialNum(MonsterType MT, int SerialNum)
{
    m_CollisionList[(int)MT].push_back(SerialNum);
}

void PlayerInfo::InitCollisionList()
{
    for (auto& cList : m_CollisionList)
    {
        cList.clear();
    }
}

void PlayerInfo::SetAllCardProperty(int Damage, int StunDamage, int Destuction, int NamedDamage, int Type)
{
    m_iDamage = Damage;
    m_iStunDamage = StunDamage;
    m_iDestuction = Destuction;
    m_iNamedDamage = NamedDamage;
    m_iType = Type;
}
