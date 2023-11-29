#include "Player.h"
#include "PlayerOwnedStates.h"


//-----------------------------------------------------------------------
// PMove
//-----------------------------------------------------------------------

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

	player->SetSpeed(PLAYER_MOVE_SPEED);
}

void PMove::Execute(Player* player, float elapsed)
{
}

void PMove::Exit(Player* player)
{
}

//-----------------------------------------------------------------------
// PStay
//-----------------------------------------------------------------------

PStay* PStay::Instance()
{
	static PStay instance;
	return &instance;
}

void PStay::Enter(Player* player)
{
	if (player->GetDir() == Right) {
		player->SetImg(L"./윈플 텀프 이미지/창술사.png");
	}
	else {
		player->SetImg(L"./윈플 텀프 이미지/창술사(left).png");
	}
	player->SetSpeed(0);
}

void PStay::Execute(Player* player, float elapsed)
{
}

void PStay::Exit(Player* player)
{
}

//-----------------------------------------------------------------------
// PStun
//-----------------------------------------------------------------------
PStun* PStun::Instance()
{
	static PStun instance;
	return &instance;
}

void PStun::Enter(Player* player)
{
	if (player->GetDir() == Right) {
		player->SetImg(L"./윈플 텀프 이미지/창술사_스턴.png");
	}
	else {
		player->SetImg(L"./윈플 텀프 이미지/창술사_스턴(left).png");
	}
	player->SetSpeed(0);
}

void PStun::Execute(Player* player, float elapsed)
{
}

void PStun::Exit(Player* player)
{
}

PSkill* PSkill::Instance()
{
	return nullptr;
}

void PSkill::Enter(Player* player)
{
	player->SetSpeed(0);
}

void PSkill::Execute(Player* player, float elapsed)
{
}

void PSkill::Exit(Player* player)
{
}
