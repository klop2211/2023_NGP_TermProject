#include "Player.h"
#include "PlayerOwnedStates.h"

PMove* PMove::Instance()
{
	static PMove instance;
	return &instance;
}

void PMove::Enter(Player* player)
{
	if (player->GetDir() == Right) {
		player->SetImg(L"./윈플 텀프 이미지/창술사_move.png");
	}
	else {
		player->SetImg(L"./윈플 텀프 이미지/창술사_move(left).png");
	}

}

void PMove::Execute(Player* player, float elapsed)
{
}

void PMove::Exit(Player* player)
{
}

PStay* PStay::Instance()
{
	static PStay instance;
	return &instance;
}

void PStay::Enter(Player* player)
{
}

void PStay::Execute(Player* player, float elapsed)
{
}

void PStay::Exit(Player* player)
{
}
