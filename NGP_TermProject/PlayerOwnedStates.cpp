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

//-----------------------------------------------------------------------
// PSkill
//-----------------------------------------------------------------------
PSkill* PSkill::Instance()
{
	static PSkill instance;
	return &instance;
}

void PSkill::Enter(Player* player)
{
	int tripordNum = 0;
	int dx, dy;
	switch (player->GetUseCardName())
	{
	case CardName::N_cjdfydwls: // 청룡진
		if (player->GetDir() == Left)
			player->SetImg(L"./\\윈플 텀프 이미지\\창술사_청룡진_이펙트(left).png");
		else
			player->SetImg(L"./\\윈플 텀프 이미지\\창술사_청룡진_이펙트.png");

		player->SetSpeed(0);
		player->SetDamage(5);
		player->SetStunDamage(5);
		player->SetDestruction(1);

		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydwls, 0); // 청룡진 1트포 체크
		if(tripordNum == 1)
			player->SetStunDamage(player->GetStunDamage() + 2);
		else if(tripordNum == 2)
			player->SetDamage(player->GetDamage() + 1);
		else if(tripordNum == 3)
			player->SetRect(player->GetRect().left - 30, player->GetRect().top - 30, player->GetRect().right, player->GetRect().bottom);
		
		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydwls, 1); // 청룡진 2트포 체크
		if (tripordNum == 1) {
			if (player->GetDir() == Left)
				player->SetImg(L"->/\\윈플 텀프 이미지\\창술사_청룡진창사라지는_이펙트(left)->png");
			else
				player->SetImg(L"->/\\윈플 텀프 이미지\\창술사_청룡진창사라지는_이펙트->png");
		}
		else if (tripordNum == 2) {
			player->SetRect(player->GetRect().left - 30, player->GetRect().top - 30, player->GetRect().right, player->GetRect().bottom);
			player->SetDamage(player->GetDamage() + 2);
		}
		else if (tripordNum == 3) {
			dx = player->GetDir() == Left ? -100 : 200;
			dy = 0;
			player->AddSkillObject(SkillObject{ Wall,
				FPOINT{player->GetLocation().x + dx, player->GetLocation().y - dy}, 0,
				0, 0, 0 });
		}

		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydwls, 2); // 청룡진 3트포 체크
		if (tripordNum == 1) {
			player->DrawCard();
			player->SetCardPoint();
		}
		else if (tripordNum == 2) {
			//TODO:마나감소 
		}
		break;
	case CardName::N_qksdnjftja: // 반월섬
		if (player->GetDir() == Left)
			player->SetImg(L"./\\윈플 텀프 이미지\\창술사_반월섬_이펙트(left).png");
		else
			player->SetImg(L"./\\윈플 텀프 이미지\\창술사_반월섬_이펙트.png");

		player->SetSpeed(10);
		player->SetDamage(12);
		player->SetStunDamage(20);
		player->SetDestruction(2);

		tripordNum = player->ActivatedTripordNumber(CardName::N_qksdnjftja, 0);
		if (tripordNum == 1) {
			player->SetDestruction(player->GetDestruction() + 1);
		}
		else if (tripordNum == 2) {
			player->SetDamage(player->GetDamage() + 2);
		}
		else if (tripordNum == 3) {
			player->SetSpeed(30);
		}

		tripordNum = player->ActivatedTripordNumber(CardName::N_qksdnjftja, 1);
		if (tripordNum == 1) {
			player->SetStunDamage(player->GetStunDamage() + 10);
		}
		else if (tripordNum == 2) {
			player->SetNamedDamage(player->GetNamedDamage() + 2);
		}
		else if (tripordNum == 3) {
			//TODO:마나감소 
		}
		break;
	case CardName::N_aodfyddufvk: // 맹룡열파
		if (player->GetDir() == Left)
			player->SetImg(L"./\\윈플 텀프 이미지\\창술사_맹룡열파2_이펙트(left).png");
		else
			player->SetImg(L"./\\윈플 텀프 이미지\\창술사_맹룡열파2_이펙트.png");

		player->SetSpeed(70);
		player->SetDamage(10);
		player->SetStunDamage(15);
		player->SetDestruction(0);

		tripordNum = player->ActivatedTripordNumber(CardName::N_aodfyddufvk, 0);
		if (tripordNum == 1) {
			player->SetRect(player->GetRect().left - 30, player->GetRect().top - 30, player->GetRect().right, player->GetRect().bottom);
		}
		else if (tripordNum == 2) {
			player->SetStunDamage(player->GetStunDamage() + 5);
		}
		else if (tripordNum == 3) {
			player->SetDamage(player->GetDamage() + 2);
		}

		tripordNum = player->ActivatedTripordNumber(CardName::N_aodfyddufvk, 1);
		if (tripordNum == 1) {
			player->SetDamage(40);
		}
		else if (tripordNum == 2) {
			if (player->GetDir() == Left)
				player->SetImg(L"./\\윈플 텀프 이미지\\창술사_맹룡열파2_빙결이펙트(left).png");
			else
				player->SetImg(L"./\\윈플 텀프 이미지\\창술사_맹룡열파2_빙결이펙트.png");
			player->SetType(Ice);
		}
		else if (tripordNum == 3) {
			if (player->GetDir() == Left)
				player->SetImg(L"./\\윈플 텀프 이미지\\창술사_맹룡열파2_화염이펙트(left).png");
			else
				player->SetImg(L"./\\윈플 텀프 이미지\\창술사_맹룡열파2_화염이펙트.png");
			player->SetType(Fire);
		}

		tripordNum = player->ActivatedTripordNumber(CardName::N_aodfyddufvk, 2);
		if (tripordNum == 1) {
			m_bOnemore = true;
		}
		else if (tripordNum == 2) {
			//TODO:마나감소
		}
		break;



	default:
		break;
	}
}

void PSkill::Execute(Player* player, float elapsed)
{
}

void PSkill::Exit(Player* player)
{
	int tripordNum;
	int dx, dy;
	int speed;
	switch (player->GetUseCardName())
	{
	case CardName::N_cjdfydwls:
		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydwls, 1); // 청룡진 2트포 체크
		if (tripordNum == 1) {
			dx = player->GetDir() == Left ? -100 : 200;
			dy = 400;
			player->AddSkillObject(SkillObject{ Drop_Spear,
				FPOINT{player->GetLocation().x + dx, player->GetLocation().y - dy}, 70,
				player->GetDamage(), player->GetStunDamage(), player->GetDestruction() });
		}
		break;
	case CardName::N_qksdnjftja:
		tripordNum = player->ActivatedTripordNumber(CardName::N_qksdnjftja, 2);
		if (tripordNum == 1) {
			dx = player->GetDir() == Left ? -100 : 200;
			dy = 0;
			player->AddSkillObject(SkillObject{ Hurricane,
				FPOINT{player->GetLocation().x + dx, player->GetLocation().y - dy}, 0,
				player->GetDamage(), player->GetStunDamage(), player->GetDestruction() });
		}
		else if (tripordNum == 2) {
			dx = player->GetDir() == Left ? -100 : 200;
			dy = 0;
			speed = player->GetDir() == Left ? -30 : 30;
			player->AddSkillObject(SkillObject{ Hurricane,
				FPOINT{player->GetLocation().x + dx, player->GetLocation().y - dy}, speed,
				player->GetDamage(), player->GetStunDamage(), player->GetDestruction() });
		}
		break;

	default:
		break;
	}
	player->SetSpeed(0);
	player->SetDamage(0);
	player->SetStunDamage(0);
	player->SetDestruction(0);

}
