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

#define TEST_CARDNAME CardName::N_dmsgkdbtjdxks

void PSkill::Enter(Player* player)
{
	int tripordNum = 0;
	int dx, dy;
	CardName test = TEST_CARDNAME;
	// switch(player->GetCurrentCardName())
	switch (test)
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
			player->SetRect(player->GetRect().left, player->GetRect().top, player->GetRect().right, player->GetRect().bottom);
		
		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydwls, 1); // 청룡진 2트포 체크
		if (tripordNum == 1) {
			if (player->GetDir() == Left)
				player->SetImg(L"->/\\윈플 텀프 이미지\\창술사_청룡진창사라지는_이펙트(left)->png");
			else
				player->SetImg(L"->/\\윈플 텀프 이미지\\창술사_청룡진창사라지는_이펙트->png");
		}
		else if (tripordNum == 2) {
			player->SetRect(player->GetRect().left, player->GetRect().top, player->GetRect().right, player->GetRect().bottom);
			player->SetDamage(player->GetDamage() + 2);
		}
		else if (tripordNum == 3) {
			dx = player->GetDir() == Left ? -100 : 200;
			dy = 0;
			player->AddSkillObject(SkillObject{ Wall, player });
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

		player->SetSpeed(320);
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
			player->SetSpeed(400);
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

		player->SetSpeed(250);
		player->SetDamage(10);
		player->SetStunDamage(15);
		player->SetDestruction(0);

		tripordNum = player->ActivatedTripordNumber(CardName::N_aodfyddufvk, 0);
		if (tripordNum == 1) {
			player->SetRect(player->GetRect().left, player->GetRect().top, player->GetRect().right, player->GetRect().bottom);
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
	case CardName::N_dusghkstja:  //연환섬
		if (player->GetDir() == Left)
			player->SetImg(L"./\\윈플 텀프 이미지\\창술사_연환섬_이펙트_돌진추가(left).png");
		else
			player->SetImg(L"./\\윈플 텀프 이미지\\창술사_연환섬_이펙트_돌진추가.png");
		player->SetSpeed(200);
		player->SetDamage(6);
		player->SetStunDamage(5);
		player->SetDestruction(1);

		tripordNum = player->ActivatedTripordNumber(CardName::N_dusghkstja, 0);
		if (tripordNum == 1) {
			if (player->GetDir() == Left)
				player->SetImg(L"./\\윈플 텀프 이미지\\창술사_연환섬_이펙트(left).png");
			else
				player->SetImg(L"./\\윈플 텀프 이미지\\창술사_연환섬_이펙트.png");
			player->SetDamage(player->GetDamage() + 4);
			player->SetSpeed(0);
		}
		else if (tripordNum == 2) {
			player->SetSpeed(300);
		}
		else if (tripordNum == 3) {
			player->PlusUltimate();
		}

		tripordNum = player->ActivatedTripordNumber(CardName::N_dusghkstja, 1);
		if (tripordNum == 1) {
			if (player->GetDir() == Left)
				player->SetImg(L"./\\윈플 텀프 이미지\\창술사_연환섬_이펙트(left).png");
			else
				player->SetImg(L"./\\윈플 텀프 이미지\\창술사_연환섬_이펙트.png");
			player->SetSpeed(300);
		}
		else if (tripordNum == 2) {
			player->SetStunDamage(player->GetStunDamage() + 3);
		}
		else if (tripordNum == 3) {
			player->SetDamage(player->GetDamage() + 4);
		}

		tripordNum = player->ActivatedTripordNumber(CardName::N_dusghkstja, 2);
		if (tripordNum == 1) {
			player->DrawCard();
		}
		break;
		case CardName::N_cjdfydcnftn: // 청룡출수

		if (player->GetDir() == Left)
			player->SetImg(L"./\\윈플 텀프 이미지\\창술사_청룡출수_이펙트(left).png");
		else
			player->SetImg(L"./\\윈플 텀프 이미지\\창술사_청룡출수_이펙트.png");

		player->SetSpeed(150);
		player->SetDamage(5);
		player->SetStunDamage(15);
		player->SetDestruction(0);

		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydcnftn, 0);
		if (tripordNum == 1) {
			player->SetDamage(player->GetDamage() + 1);

		}
		else if (tripordNum == 2) {
			player->SetSpeed(0);
			player->SetFrameIndex(4);
			player->SetDamage(player->GetDamage() + 2);

		}
		else if (tripordNum == 3) {
			player->SetSpeed(230);
		}

		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydcnftn, 1);
		if (tripordNum == 1) {
			player->SetType(Hurricane);
		}
		else if (tripordNum == 2) {
			//TODO:각성게이지 추가회복
		}
		else if (tripordNum == 3) {
			player->SetDamage(player->GetDamage() + 2);
		}
	case CardName::N_dmsgkdbtjdxks: // 은하유성탄
		if (player->GetDir() == Left)
			player->SetImg(L"./\\윈플 텀프 이미지\\창술사_은하유성탄_이펙트(left).png");
		else
			player->SetImg(L"./\\윈플 텀프 이미지\\창술사_은하유성탄_이펙트.png");

		player->SetDamage(20);
		player->SetStunDamage(40);
		player->SetDestruction(2);
	break;
	case CardName::N_wjrfydvh: // 적룡포
	if (player->GetDir() == Left)
		player->SetImg(L"./\\윈플 텀프 이미지\\창술사_적룡포_이펙트(left).png");
	else
		player->SetImg(L"./\\윈플 텀프 이미지\\창술사_적룡포_이펙트.png");
	player->SetSpeed(0);
	player->SetDamage(15);
	player->SetStunDamage(5);
	player->SetDestruction(1);

	tripordNum = player->ActivatedTripordNumber(CardName::N_wjrfydvh, 0);
	if (tripordNum == 1) {
		// 공속증가
	}
	else if (tripordNum == 2) {
		// 사거리증가는 Insert_Object에서 처리합니다
	}
	else if (tripordNum == 3) {
		player->SetDamage(player->GetDamage() + 3);
	}

	tripordNum = player->ActivatedTripordNumber(CardName::N_wjrfydvh, 1);
	if (tripordNum == 1) {
		//TODO:마나감소
	}
	else if (tripordNum == 2) {
		player->DrawCard(false);
	}
	else if (tripordNum == 3) {
		player->SetDestruction(player->GetDestruction() + 1);
	}

	tripordNum = player->ActivatedTripordNumber(CardName::N_wjrfydvh, 2);
	if (tripordNum == 1) {
		// 2층에 추가 창생성 Insert_Object에서 처리합니다
	}
	else if (tripordNum == 2) {
		player->SetNamedDamage(player->GetNamedDamage() + 15);
	}
	break;



	default:
		break;
	}



}

void PSkill::Execute(Player* player, float elapsed)
{
	CardName test = TEST_CARDNAME;
	if (test == CardName::N_dmsgkdbtjdxks) {
		if (player->GetFrameIndex() < 4) {
			player->SetLocation(POINT{ (int)player->GetLocation().x, (int)(player->GetLocation().y + -300 * elapsed) });
		}
		if (9 <= player->GetFrameIndex()) {
			player->SetLocation(POINT{ (int)player->GetLocation().x, (int)(player->GetLocation().y + 430 * elapsed) });
		}
	}
}

void PSkill::Exit(Player* player)
{
	int tripordNum;
	int dx, dy;
	int speed;
	CardName test = TEST_CARDNAME;
	switch (test)
	{
	case CardName::N_cjdfydwls:
		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydwls, 1); // 청룡진 2트포 체크
		if (tripordNum == 1) {
			player->AddSkillObject(SkillObject{ Drop_Spear, player });
		}
		break;
	case CardName::N_qksdnjftja:
		tripordNum = player->ActivatedTripordNumber(CardName::N_qksdnjftja, 2);
		if (tripordNum == 1) {
			player->AddSkillObject(SkillObject{ Hurricane, player });
		}
		else if (tripordNum == 2) {
			player->AddSkillObject(SkillObject{ Hurricane, player });
		}
		break;
	case CardName::N_aodfyddufvk:
		tripordNum = player->ActivatedTripordNumber(CardName::N_aodfyddufvk, 2);
		if (tripordNum == 1 && m_bOnemore) {
			m_bOnemore = false;
			player->ChangeState(PStateName::Skill);
		}
		break;
	case CardName::N_dusghkstja:
		tripordNum = player->ActivatedTripordNumber(CardName::N_dusghkstja, 2);
		if (tripordNum == 2) {
			player->AddSkillObject(SkillObject{ SowrdLight, player });
		}
		break;
	case CardName::N_cjdfydcnftn:
		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydcnftn, 2);
		if (tripordNum == 1) {
			player->AddSkillObject(SkillObject{ Rotation_Spear, player });
		}
		else if (tripordNum == 2) {
			player->AddSkillObject(SkillObject{ Airborne_Spear1, player });

			player->AddSkillObject(SkillObject{ Airborne_Spear2, player });

			player->AddSkillObject(SkillObject{ Airborne_Spear3, player });
		}
	case CardName::N_dmsgkdbtjdxks:
		player->SetLocation(POINT{ (int)player->GetLocation().x, GROUNDYPOINT - 100 });
		break;
	case CardName::N_wjrfydvh: // 적룡포
		player->AddSkillObject(SkillObject{ Red_Spear, player });
		break;
	default:
		break;
	}
	//player->SetSpeed(0);
	//player->SetDamage(0);
	//player->SetStunDamage(0);
	//player->SetDestruction(0);

}
