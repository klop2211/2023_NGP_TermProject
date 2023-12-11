#include "Common.h"
#include "PlayerInfo.h"

PlayerInfo::PlayerInfo(int num) :
    m_iPlayerNum(num),
    m_iDamage(0),
    m_iStunDamage(0),
    m_iDestuction(0),
    m_iNamedDamage(0),
    m_iType(0)
{
    for (auto& k : m_KillCount)
    {
        k = 0;
    }
}

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
