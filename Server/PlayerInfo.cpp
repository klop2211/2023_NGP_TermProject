#include "Common.h"
#include "PlayerInfo.h"

RECT PlayerInfo::GetBB()
{
    RECT ReturnBB {
        m_PlayerLocation.x,
        m_PlayerLocation.y,
        m_PlayerLocation.x + PLAYERDEFAULTSIZE,
        m_PlayerLocation.y + PLAYERDEFAULTSIZE };

    return ReturnBB;
}