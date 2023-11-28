#include "Common.h"
#include "MsgInstence.h"
#include "StateMessage.h"
#include <memory>

StateMsgArgu* MsgInstence::GetStateMsgArguType(BYTE LowerBits)
{
	switch (LowerBits)
	{
	case	(int)StateMsgType::MonsterSpawn:	return new MonsterSpawnStateMsg;
	case	(int)StateMsgType::MonsterHp:		return new MonsterHpStateMsg;
	case	(int)StateMsgType::PlayerMove:		return new PlayerMoveStateMsg;
	case	(int)StateMsgType::UseCard:			return new UseCardStateMsg;
	case	(int)StateMsgType::CastleHp:		return new CastleHpStateMsg;
	default:
		printf("MsgInstence::GetStateMsgArguType¿¡ ¿À·ù");
		return nullptr;
	}
}
