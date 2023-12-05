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
		player->SetImg(L"./���� ���� �̹���/â����_move.png");
	}
	else {
		player->SetImg(L"./���� ���� �̹���/â����_move(left).png");
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
		player->SetImg(L"./���� ���� �̹���/â����.png");
	}
	else {
		player->SetImg(L"./���� ���� �̹���/â����(left).png");
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
		player->SetImg(L"./���� ���� �̹���/â����_����.png");
	}
	else {
		player->SetImg(L"./���� ���� �̹���/â����_����(left).png");
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

#define TEST_CARDNAME CardName::N_dusghkstja

void PSkill::Enter(Player* player)
{
	int tripordNum = 0;
	int dx, dy;
	CardName test = TEST_CARDNAME;
	switch (test)
	{
	case CardName::N_cjdfydwls: // û����
		if (player->GetDir() == Left)
			player->SetImg(L"./\\���� ���� �̹���\\â����_û����_����Ʈ(left).png");
		else
			player->SetImg(L"./\\���� ���� �̹���\\â����_û����_����Ʈ.png");

		player->SetSpeed(0);
		player->SetDamage(5);
		player->SetStunDamage(5);
		player->SetDestruction(1);

		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydwls, 0); // û���� 1Ʈ�� üũ
		if(tripordNum == 1)
			player->SetStunDamage(player->GetStunDamage() + 2);
		else if(tripordNum == 2)
			player->SetDamage(player->GetDamage() + 1);
		else if(tripordNum == 3)
			player->SetRect(player->GetRect().left, player->GetRect().top, player->GetRect().right, player->GetRect().bottom);
		
		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydwls, 1); // û���� 2Ʈ�� üũ
		if (tripordNum == 1) {
			if (player->GetDir() == Left)
				player->SetImg(L"->/\\���� ���� �̹���\\â����_û����â�������_����Ʈ(left)->png");
			else
				player->SetImg(L"->/\\���� ���� �̹���\\â����_û����â�������_����Ʈ->png");
		}
		else if (tripordNum == 2) {
			player->SetRect(player->GetRect().left, player->GetRect().top, player->GetRect().right, player->GetRect().bottom);
			player->SetDamage(player->GetDamage() + 2);
		}
		else if (tripordNum == 3) {
			dx = player->GetDir() == Left ? -100 : 200;
			dy = 0;
			player->AddSkillObject(SkillObject{ Wall,
				FPOINT{player->GetLocation().x + dx, player->GetLocation().y - dy}, 0,
				0, 0, 0 });
		}

		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydwls, 2); // û���� 3Ʈ�� üũ
		if (tripordNum == 1) {
			player->DrawCard();
			player->SetCardPoint();
		}
		else if (tripordNum == 2) {
			//TODO:�������� 
		}
		break;
	case CardName::N_qksdnjftja: // �ݿ���
		if (player->GetDir() == Left)
			player->SetImg(L"./\\���� ���� �̹���\\â����_�ݿ���_����Ʈ(left).png");
		else
			player->SetImg(L"./\\���� ���� �̹���\\â����_�ݿ���_����Ʈ.png");

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
			//TODO:�������� 
		}
		break;
	case CardName::N_aodfyddufvk: // �ͷ濭��
		if (player->GetDir() == Left)
			player->SetImg(L"./\\���� ���� �̹���\\â����_�ͷ濭��2_����Ʈ(left).png");
		else
			player->SetImg(L"./\\���� ���� �̹���\\â����_�ͷ濭��2_����Ʈ.png");

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
				player->SetImg(L"./\\���� ���� �̹���\\â����_�ͷ濭��2_��������Ʈ(left).png");
			else
				player->SetImg(L"./\\���� ���� �̹���\\â����_�ͷ濭��2_��������Ʈ.png");
			player->SetType(Ice);
		}
		else if (tripordNum == 3) {
			if (player->GetDir() == Left)
				player->SetImg(L"./\\���� ���� �̹���\\â����_�ͷ濭��2_ȭ������Ʈ(left).png");
			else
				player->SetImg(L"./\\���� ���� �̹���\\â����_�ͷ濭��2_ȭ������Ʈ.png");
			player->SetType(Fire);
		}

		tripordNum = player->ActivatedTripordNumber(CardName::N_aodfyddufvk, 2);
		if (tripordNum == 1) {
			m_bOnemore = true;
		}
		else if (tripordNum == 2) {
			//TODO:��������
		}
		break;
	case CardName::N_dusghkstja:  //��ȯ��
		if (player->GetDir() == Left)
			player->SetImg(L"./\\���� ���� �̹���\\â����_��ȯ��_����Ʈ_�����߰�(left).png");
		else
			player->SetImg(L"./\\���� ���� �̹���\\â����_��ȯ��_����Ʈ_�����߰�.png");
		player->SetSpeed(200);
		player->SetDamage(6);
		player->SetStunDamage(5);
		player->SetDestruction(1);

		tripordNum = player->ActivatedTripordNumber(CardName::N_dusghkstja, 0);
		if (tripordNum == 1) {
			if (player->GetDir() == Left)
				player->SetImg(L"./\\���� ���� �̹���\\â����_��ȯ��_����Ʈ(left).png");
			else
				player->SetImg(L"./\\���� ���� �̹���\\â����_��ȯ��_����Ʈ.png");
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
				player->SetImg(L"./\\���� ���� �̹���\\â����_��ȯ��_����Ʈ(left).png");
			else
				player->SetImg(L"./\\���� ���� �̹���\\â����_��ȯ��_����Ʈ.png");
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
		case CardName::N_cjdfydcnftn: // û�����

		if (player->GetDir() == Left)
			player->SetImg(L"./\\���� ���� �̹���\\â����_û�����_����Ʈ(left).png");
		else
			player->SetImg(L"./\\���� ���� �̹���\\â����_û�����_����Ʈ.png");

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
			//TODO:���������� �߰�ȸ��
		}
		else if (tripordNum == 3) {
			player->SetDamage(player->GetDamage() + 2);
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
	CardName test = TEST_CARDNAME;
	switch (player->GetUseCardName())
	{
	case CardName::N_cjdfydwls:
		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydwls, 1); // û���� 2Ʈ�� üũ
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
			speed = player->GetDir() == Left ? -130 : 130;
			player->AddSkillObject(SkillObject{ Hurricane,
				FPOINT{player->GetLocation().x + dx, player->GetLocation().y - dy}, speed,
				player->GetDamage(), player->GetStunDamage(), player->GetDestruction() });
		}
		break;
	case CardName::N_aodfyddufvk:
		tripordNum = player->ActivatedTripordNumber(CardName::N_aodfyddufvk, 2);
		if (tripordNum == 1) {
			m_bOnemore = false;
			player->ChangeState(PStateName::Skill);
		}
		break;
	case CardName::N_dusghkstja:
		tripordNum = player->ActivatedTripordNumber(CardName::N_dusghkstja, 2);
		if (tripordNum == 2) {
			dx = player->GetDir() == Left ? -100 : 200;
			dy = 0;
			speed = 500;
			player->AddSkillObject(SkillObject{ SowrdLight,
				FPOINT{player->GetLocation().x + dx, player->GetLocation().y - dy}, speed,
				player->GetDamage(), player->GetStunDamage(), player->GetDestruction() });
		}
		break;
	case CardName::N_cjdfydcnftn:
		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydcnftn, 2);
		if (tripordNum == 1) {
			dx = 0;
			dy = 0;
			speed = 0;
			player->AddSkillObject(SkillObject{ Rotation_Spear,
				FPOINT{player->GetLocation().x + dx, player->GetLocation().y - dy}, speed,
				player->GetDamage(), player->GetStunDamage(), player->GetDestruction() });
		}
		else if (tripordNum == 2) {
			dx = 25;
			dy = -75;
			speed = 0;
			player->AddSkillObject(SkillObject{ Airborne_Spear,
				FPOINT{player->GetLocation().x + dx, player->GetLocation().y - dy}, speed,
				player->GetDamage(), player->GetStunDamage(), player->GetDestruction() });

			dx = -75;
			dy = 25;
			speed = 0;
			player->AddSkillObject(SkillObject{ Airborne_Spear,
				FPOINT{player->GetLocation().x + dx, player->GetLocation().y - dy}, speed,
				player->GetDamage(), player->GetStunDamage(), player->GetDestruction() });

			dx = 125;
			dy = 25;
			speed = 0;
			player->AddSkillObject(SkillObject{ Airborne_Spear,
				FPOINT{player->GetLocation().x + dx, player->GetLocation().y - dy}, speed,
				player->GetDamage(), player->GetStunDamage(), player->GetDestruction() });
		}

		break;
	default:
		break;
	}
	//player->SetSpeed(0);
	//player->SetDamage(0);
	//player->SetStunDamage(0);
	//player->SetDestruction(0);

}
