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
	player->SetStateTime(0.f);

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
	player->SetStateTime(0.f);

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
	player->SetStateTime(0.f);

	if (player->GetDir() == Right) {
		player->SetImg(L"./���� ���� �̹���/â����_����.png");
	}
	else {
		player->SetImg(L"./���� ���� �̹���/â����_����(left).png");
	}
	player->SetSpeed(0);
	m_fDurationTime = 0.f;
}

void PStun::Execute(Player* player, float elapsed)
{
	m_fDurationTime += elapsed;
	if (m_fDurationTime > 2.0f) {
		player->ChangeState(PStateName::Stay);
	}
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

#define TEST_CARDNAME CardName::N_rhlddufvk

void PSkill::Enter(Player* player)
{
	player->SetStateTime(0.f);

	int tripordNum = 0;
	int dx, dy;
	CardName test = TEST_CARDNAME;
	switch(player->GetCurrentCardName())
	//switch (test)
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
			player->AddSkillObject(Wall);
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
	case CardName::N_dmsgkdbtjdxks: // ��������ź
		if (player->GetDir() == Left)
			player->SetImg(L"./\\���� ���� �̹���\\â����_��������ź_����Ʈ(left).png");
		else
			player->SetImg(L"./\\���� ���� �̹���\\â����_��������ź_����Ʈ.png");
		m_bUlti = true;
		player->SetDamage(20);
		player->SetStunDamage(40);
		player->SetDestruction(2);
	break;
	case CardName::N_wjrfydvh: // ������
	if (player->GetDir() == Left)
		player->SetImg(L"./\\���� ���� �̹���\\â����_������_����Ʈ(left).png");
	else
		player->SetImg(L"./\\���� ���� �̹���\\â����_������_����Ʈ.png");
	player->SetSpeed(0);
	player->SetDamage(15);
	player->SetStunDamage(5);
	player->SetDestruction(1);

	tripordNum = player->ActivatedTripordNumber(CardName::N_wjrfydvh, 0);
	if (tripordNum == 1) {
		// ��������
	}
	else if (tripordNum == 2) {
		// ��Ÿ������� Insert_Object���� ó���մϴ�
	}
	else if (tripordNum == 3) {
		player->SetDamage(player->GetDamage() + 3);
	}

	tripordNum = player->ActivatedTripordNumber(CardName::N_wjrfydvh, 1);
	if (tripordNum == 1) {
		//TODO:��������
	}
	else if (tripordNum == 2) {
		player->DrawCard(false);
	}
	else if (tripordNum == 3) {
		player->SetDestruction(player->GetDestruction() + 1);
	}

	tripordNum = player->ActivatedTripordNumber(CardName::N_wjrfydvh, 2);
	if (tripordNum == 1) {
		// 2���� �߰� â���� Insert_Object���� ó���մϴ�
	}
	else if (tripordNum == 2) {
		player->SetNamedDamage(player->GetNamedDamage() + 15);
	}
	break;
	case CardName::N_dbtjdrkdcjs: // ������õ
	if (player->GetDir() == Left)
		player->SetImg(L"./\\���� ���� �̹���\\â����_������õ_����Ʈ(left).png");
	else
		player->SetImg(L"./\\���� ���� �̹���\\â����_������õ_����Ʈ.png");

	player->SetSpeed(0);
	player->SetDamage(12);
	player->SetStunDamage(5);
	player->SetDestruction(0);

	tripordNum = player->ActivatedTripordNumber(CardName::N_dbtjdrkdcjs, 0);
	if (tripordNum == 1) {
		//player.SetBaseDelay(4);
	}
	else if (tripordNum == 2) {
		player->SetDamage(player->GetDamage() + 2);

	}
	else if (tripordNum == 3) {
		player->SetNamedDamage(player->GetNamedDamage() + 4);
	}

	tripordNum = player->ActivatedTripordNumber(CardName::N_dbtjdrkdcjs, 2);
	if (tripordNum == 2) {
		player->SetSpeed(0);
		if (player->GetDir() == Left)
			player->SetImg(L"./\\���� ���� �̹���\\â����_������õâ�������_����Ʈ(left).png");
		else
			player->SetImg(L"./\\���� ���� �̹���\\â����_������õâ�������_����Ʈ.png");
	}
	break;
	case CardName::N_rhlddufvk: // ������
	if (player->GetDir() == Left)
		player->SetImg(L"./\\���� ���� �̹���\\â����_������_����Ʈ(left).png");
	else
		player->SetImg(L"./\\���� ���� �̹���\\â����_������_����Ʈ.png");
	player->SetSpeed(0);
	player->SetDamage(10);
	player->SetStunDamage(5);
	player->SetDestruction(1);

	tripordNum = player->ActivatedTripordNumber(CardName::N_rhlddufvk, 0);
	if (tripordNum == 1) {
		player->SetDestruction(player->GetDestruction() + 1);
	}
	else if (tripordNum == 2) {
		//player.SetBaseDelay(3);
	}
	else if (tripordNum == 3) {
		//player.SetRuncount(100);
	}

	tripordNum = player->ActivatedTripordNumber(CardName::N_rhlddufvk, 1);
	if (tripordNum == 1) {
		if (player->GetDir() == Left)
			player->SetImg(L"./\\���� ���� �̹���\\â����_������_ȭ������Ʈ(left).png");
		else
			player->SetImg(L"./\\���� ���� �̹���\\â����_������_ȭ������Ʈ.png");
		player->SetType(Fire);
	}
	else if (tripordNum == 2) {
		//���� â������ ���ĳ�
	}
	else if (tripordNum == 3) {
		player->SetNamedDamage(player->GetNamedDamage() + 3);
	}

	tripordNum = player->ActivatedTripordNumber(CardName::N_rhlddufvk, 2);
	if (tripordNum == 1) {
		player->SetDamage(player->GetDamage() + 4);
	}
	else if (tripordNum == 2) {
		//TODO:��������
	}

	break;
	case CardName::N_sktjsckd: // ����â
	if (player->GetDir() == Left)
		player->SetImg(L"./\\���� ���� �̹���\\â����_����â_����Ʈ(left).png");
	else
		player->SetImg(L"./\\���� ���� �̹���\\â����_����â_����Ʈ.png");
	player->SetSpeed(0);
	player->SetDamage(7);
	player->SetStunDamage(5);
	player->SetDestruction(0);

	tripordNum = player->ActivatedTripordNumber(CardName::N_sktjsckd, 0);
	if (tripordNum == 1) {
		player->SetDamage(player->GetDamage() + 1);
	}
	else if (tripordNum == 2) {
		//player.SetRuncount(100);
	}
	else if (tripordNum == 3) {
		//PlusUltimate();
	}

	tripordNum = player->ActivatedTripordNumber(CardName::N_sktjsckd, 1);
	if (tripordNum == 1) {
		m_bOnemore = true;
	}
	else if (tripordNum == 2) {
		player->SetNamedDamage(player->GetNamedDamage() + 2);
	}
	else if (tripordNum == 3) {
		player->DrawCard(false);
	}

	tripordNum = player->ActivatedTripordNumber(CardName::N_sktjsckd, 2);
	if (tripordNum == 1) {
		//��Ÿ�����
	}
	break;
	default:
		break;
	}



}

void PSkill::Execute(Player* player, float elapsed)
{

	CardName test = player->GetCurrentCardName();
	int tripordNum = 0;
	if (test == CardName::N_dmsgkdbtjdxks) {
		if (player->GetFrameIndex() < 4) {
			player->SetLocation(POINT{ (int)player->GetLocation().x, (int)(player->GetLocation().y + -300 * elapsed) });
		}
		if (player->GetFrameIndex() == 7 && m_bUlti) {
			m_bUlti = false;
			player->AddSkillObject(Ulti_Spear);
		}
		if (9 <= player->GetFrameIndex()) {
			player->SetLocation(POINT{ (int)player->GetLocation().x, (int)(player->GetLocation().y + 430 * elapsed) });
		}
	}

	tripordNum = player->ActivatedTripordNumber(CardName::N_dbtjdrkdcjs, 2);
	if (test == CardName::N_dbtjdrkdcjs && tripordNum != 2) {
		if (player->GetDir() == Left) {
			if (player->GetFrameIndex() < 3) {
				POINT temp = { player->GetLocation().x, player->GetLocation().y - 600 * elapsed };
				player->SetLocation(temp);
			}
			else if (player->GetFrameIndex() < 8 && player->GetLocation().y < GROUNDYPOINT - 100) {
				POINT temp = { player->GetLocation().x - 600 * elapsed, player->GetLocation().y + 400 * elapsed };
				player->SetLocation(temp);
			}
		}
		else {
			if (player->GetFrameIndex() < 3) {
				POINT temp = { player->GetLocation().x, player->GetLocation().y - 600 * elapsed };
				player->SetLocation(temp);
			}
			else if (player->GetFrameIndex() < 8 && player->GetLocation().y < GROUNDYPOINT - 100) {
				POINT temp = { player->GetLocation().x + 600 * elapsed, player->GetLocation().y + 450 * elapsed };
				player->SetLocation(temp);
			}
		}

		if (player->GetLocation().y > GROUNDYPOINT - 100) {
			player->SetLocation(POINT{ (int)player->GetLocation().x, GROUNDYPOINT - 100 });
		}

	}

}

void PSkill::Exit(Player* player)
{
	int tripordNum;
	int dx, dy;
	int speed;
	CardName test = TEST_CARDNAME;
	switch (player->GetCurrentCardName())
	//switch (test)
	{
	case CardName::N_cjdfydwls:
		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydwls, 1); // û���� 2Ʈ�� üũ
		if (tripordNum == 1) {
			player->AddSkillObject(Drop_Spear);
		}
		break;
	case CardName::N_qksdnjftja:
		tripordNum = player->ActivatedTripordNumber(CardName::N_qksdnjftja, 2);
		if (tripordNum == 1) {
			player->AddSkillObject(Hurricane);
		}
		else if (tripordNum == 2) {
			player->AddSkillObject(Hurricane);
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
			player->AddSkillObject(SowrdLight);
		}
		break;
	case CardName::N_cjdfydcnftn:
		tripordNum = player->ActivatedTripordNumber(CardName::N_cjdfydcnftn, 2);
		if (tripordNum == 1) {
			player->AddSkillObject(Rotation_Spear);
		}
		else if (tripordNum == 2) {
			player->AddSkillObject(Airborne_Spear1);

			player->AddSkillObject(Airborne_Spear2);

			player->AddSkillObject(Airborne_Spear3);
		}
	case CardName::N_dmsgkdbtjdxks: // ��������ź
		player->SetLocation(POINT{ (int)player->GetLocation().x, GROUNDYPOINT - 100 });
		break;
	case CardName::N_wjrfydvh: // ������
		player->AddSkillObject(Red_Spear);
		break;
	case CardName::N_dbtjdrkdcjs: // ������õ
		tripordNum = player->ActivatedTripordNumber(CardName::N_dbtjdrkdcjs, 1);
		if (tripordNum == 1) {
			player->AddSkillObject(Earthquake);
		}
		else if (tripordNum == 2) {
			player->AddSkillObject(Flame_Zone);
		}
		else if (tripordNum == 3) {
			player->AddSkillObject(Wall);
		}

		tripordNum = player->ActivatedTripordNumber(CardName::N_dbtjdrkdcjs, 2);
		if (tripordNum == 1) {
			player->AddSkillObject(Drop_Red_Spear1);
		}
		else if (tripordNum == 2) {
			player->AddSkillObject(Drop_Red_Spear2);

		}

		player->SetLocation(POINT{(int)player->GetLocation().x, GROUNDYPOINT - 100});
		break;
	case CardName::N_rhlddufvk: // ������
		player->AddSkillObject(Yellow_Spear);
		break;
	case CardName::N_sktjsckd: // ����â
		player->AddSkillObject(Purple_Spear);
		break;
	default:
		break;
	}
	//player->SetSpeed(0);
	//player->SetDamage(0);
	//player->SetStunDamage(0);
	//player->SetDestruction(0);

}
