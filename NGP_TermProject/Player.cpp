#include "stdafx.h"
#include "PlayerOwnedStates.h"
#include "Player.h"
#include "Card.h"
#include "Random.h"
#include "OtherCard.h"

Player::Player()
{
	m_dDir = Right;
	m_pImg = new CImage;
	SetImg(L"./윈플 텀프 이미지/창술사.png");
	m_pStateMachine = new StateMachine<Player>(this);
	m_pStateMachine->SetCurrentState(PStay::Instance());
	m_Location.x = 100;
	m_Location.y = GROUNDYPOINT - PLAYER_SIZE;
	m_iSpeed = 0;
	m_fFrameTime = 0.f;
	SetRect(RECT{ 100, 100, 100 + PLAYER_SIZE, 100 + PLAYER_SIZE });

	m_pUltiImg = new CImage;	m_pUltiImg->Load(TEXT("카드관련//스킬초상화//각성기.png"));
	m_pDeck = new CImage;		m_pDeck->Load(TEXT("윈플 텀프 이미지//카드뒷면.png"));
	m_pManaImg[0] = new CImage;	m_pManaImg[0]->Load(TEXT("윈플 텀프 이미지//마나.png"));
	m_pManaImg[1] = new CImage;	m_pManaImg[1]->Load(TEXT("윈플 텀프 이미지//빈마나.png"));

	m_iUltimate = 0;
	m_iCardCount = 0;
	m_iHandCardCount = 0;
	m_iDeadCardCount = 0;
	m_iMaxMana = 0;
	m_iManaCount = 0;
	m_iLevel = 0;
	m_bOnemore = false;

	m_iExperience = 0;
	for (int i = 0; i < 10; i++)
	{
		m_iExperienceBar[i] = (i + 1) * (i + 1) * 2 + 30 / (i + 2);
	}

	m_bIsClick = false;
	m_iStartX, m_iStartY = 0;
	m_iClickSelect = -1;
	m_pPrevCardPoint = { -1,-1 };
}

Player::~Player()
{
	delete m_pStateMachine;
	m_pStateMachine = NULL;

	m_pImg->Destroy();
	delete m_pImg;
	m_pImg = NULL;


}

void Player::Update(float elapsed)
{
	m_pStateMachine->Update(elapsed);

	// 이동
	if (m_dDir == Right)
		m_Location.x += m_iSpeed * elapsed;
	else
		m_Location.x -= m_iSpeed * elapsed;

	// 위치기반 RECT 보정
	SetRectByLocation();

	// 스프라이트 프레임 조정
	m_fFrameTime += FRAME_SPEED * elapsed;
	m_iFrameIdx = (int)m_fFrameTime;
	if (m_fFrameTime > m_iFrameMax) {
		m_fFrameTime = 0.f;
		m_iFrameIdx = 0;
	}

}

void Player::Draw(HDC& memDc)
{
	m_pImg->Draw(memDc, m_rRect.left, m_rRect.top, m_rRect.right - m_rRect.left, m_rRect.bottom - m_rRect.top, 0, m_pImg->GetHeight() / m_iFrameMax * m_iFrameIdx, m_pImg->GetWidth(), m_pImg->GetHeight() / m_iFrameMax);
	UiDraw(memDc);
}

void Player::ChangeState(State<Player>* cState)
{
	m_pStateMachine->ChangeState(cState);
}

void Player::ChangeState(PStateName ps)
{
	switch (ps)
	{
	case PStateName::Move:
		ChangeState(PMove::Instance());
		break;
	case PStateName::Stay:
		ChangeState(PStay::Instance());

		break;
	case PStateName::Stun:
		ChangeState(PStun::Instance());

		break;
	case PStateName::Skill:
		ChangeState(PSkill::Instance());

		break;
	default:
		break;
	}
}

void Player::OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int mx = LOWORD(lParam);
	int my = HIWORD(lParam);

	// 마우스 입력처리
	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_bIsClick = true;
		m_iStartX = mx;
		m_iStartY = my;
		break;
	case WM_MOUSEMOVE:
		// TODO: 카드를 집었을 때 커서 위치에 그 카드 위치하게
		if (m_bIsClick && m_iClickSelect != -1)
		{
			Card* SelectedCard = m_pHandCard[m_iClickSelect];

			int NewXPoint = (SelectedCard->GetPoint().x + (mx - m_iStartX));
			int NewYPoint = (SelectedCard->GetPoint().y + (my - m_iStartY));

			SelectedCard->SetPoint(NewXPoint, NewYPoint);

			m_iStartX = mx;
			m_iStartY = my;
		}
		break;
	case WM_LBUTTONUP:
		if (m_bIsClick)
		{
			//TODO: 플레이어가 카드 사용처리

			m_bIsClick = false;
			if (m_iClickSelect != -1)
			{
				if (my < WINHEIGHT * 3 / 5 && m_iManaCount >= m_pHandCard[m_iClickSelect]->GetMana())
				{
					m_iManaCount -= m_pHandCard[m_iClickSelect]->GetMana();
					UseCard();
					SetCardPoint();
				}
				else
				{
					m_pHandCard[m_iClickSelect]->SetPoint(m_pPrevCardPoint);
				}
				m_iClickSelect = -1;
				m_pPrevCardPoint = { -1,-1 };
			}
		}
		break;
	default:
		break;
	}
}

void Player::OnProcessingKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 키보드 입력처리
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'e':
		case 'E':
			//TODO 각성기 발동
			break;
		case 'd':
		case 'D':
			SetDir(Right);
			if (m_pStateMachine->isInState(*PStay::Instance()))
				ChangeState(PMove::Instance());
			if (GetAsyncKeyState(0x41) & 0x8000 && m_pStateMachine->isInState(*PMove::Instance()))
				ChangeState(PStay::Instance());

			break;
		case 'a':
		case 'A':
			SetDir(Left);
			if (m_pStateMachine->isInState(*PStay::Instance()))
				ChangeState(PMove::Instance());
			if (GetAsyncKeyState(0x44) & 0x8000 && m_pStateMachine->isInState(*PMove::Instance()))
				ChangeState(PStay::Instance());

			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case 'd':
		case 'D':
		case 'a':
		case 'A':
			if (!m_pStateMachine->isInState(*PStay::Instance()))
				ChangeState(PStay::Instance());
			if (GetAsyncKeyState(0x41) & 0x8000 || GetAsyncKeyState(0x44) & 0x8000) {
				if (GetAsyncKeyState(0x41) & 0x8000) {
					SetDir(Left);
					if (m_pStateMachine->isInState(*PStay::Instance()))
						ChangeState(PMove::Instance());
				}
				if (GetAsyncKeyState(0x44) & 0x8000) {
					SetDir(Right);
					if (m_pStateMachine->isInState(*PStay::Instance()))
						ChangeState(PMove::Instance());
				}
			}
		default:
			break;
		}
		break;
	default:
		break;
	}

}

void Player::UiDraw(HDC& memDc)
{
	HBRUSH hBrush, oldBrush;
	TCHAR numStr[3];

	//각성기 출력창
	m_pUltiImg->Draw(memDc, WINWIDTH - 150, 10, 100, 100,
		0, 0, 77, 77);
	hBrush = CreateSolidBrush(RGB(255, 215, 0));
	oldBrush = (HBRUSH)SelectObject(memDc, hBrush);
	Rectangle(memDc, WINWIDTH - 150, 100, WINWIDTH - 150 + ((double)m_iUltimate / ULTIMATESKILL) * 100, 110);
	SelectObject(memDc, oldBrush); DeleteObject(hBrush);

	// 왼쪽아래 카드 덱
	m_pDeck->Draw(memDc, -44, 750, 204, 300,
		0, 0, m_pDeck->GetWidth(), m_pDeck->GetHeight());

	//덱의 카드 남은 수
	RECT deckText = { 135, 725, 185, 775 };
	Ellipse(memDc, deckText.left, deckText.top, deckText.right, deckText.bottom);
	swprintf_s(numStr, L"%d", m_iCardCount - (m_iHandCardCount + m_iDeadCardCount));
	DrawText(memDc, numStr, lstrlen(numStr), &deckText, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	//경험치바 출력
	hBrush = CreateSolidBrush(RGB(0, 255, 255));
	oldBrush = (HBRUSH)SelectObject(memDc, hBrush);
	Rectangle(memDc, 170, WINHEIGHT - ((double)m_iExperience / m_iExperienceBar[m_iLevel]) * 100, 190, WINHEIGHT);
	SelectObject(memDc, oldBrush); DeleteObject(hBrush);

	//레벨출력
	RECT levelRect = { 150, WINHEIGHT - 20, 210, WINHEIGHT };
	swprintf_s(numStr, L"%d", m_iLevel + 1);
	Rectangle(memDc, 150, WINHEIGHT - 20, 210, WINHEIGHT);
	DrawText(memDc, numStr, lstrlen(numStr), &levelRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	//빈 마나
	for (int i = 0; i < m_iMaxMana; i++)
	{
		m_pManaImg[1]->Draw(memDc, 1600 - 55 * ((i % 5) + 1), 900 - 55 * ((i / 5) + 1), 50, 50, 0, 0, m_pManaImg[1]->GetWidth(), m_pManaImg[1]->GetHeight());
	}
	//찬 마나
	for (int i = 0; i < m_iManaCount; i++)
	{
		m_pManaImg[0]->Draw(memDc, 1600 - 55 * ((i % 5) + 1), 900 - 55 * ((i / 5) + 1), 50, 50, 0, 0, m_pManaImg[0]->GetWidth(), m_pManaImg[0]->GetHeight());
	}
}

void Player::UseCard()
{
	if (!m_pStateMachine->isInState(*PSkill::Instance()) && !m_pStateMachine->isInState(*PStun::Instance()))
	{
		//TODO: 카드 실행
		bool canNull = true;
		ChangeState(PSkill::Instance());
		//switch (m_pHandCard[m_iClickSelect]->GetCardName())
		//{
		//case CardName::N_ghltjsckd: // 회선창
		//	if (player.GetDirection() == Left)
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_회선창_이펙트(left).png");
		//	else
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_회선창_이펙트.png");
		//	for (int i = 0; i < player.GetFrame_Max(); i++) {
		//		if (i < 2) {
		//			if (player.GetDirection() == Left)
		//				player.SetOder(i, { -15,10 }, -1);
		//			else
		//				player.SetOder(i, { 15,10 }, -1);
		//		}
		//		else {
		//			if (player.GetDirection() == Left)
		//				player.SetOder(i, { -15,-10 }, -1);
		//			else
		//				player.SetOder(i, { 15,-10 }, -1);
		//		}
		//	}
		//	m_bOnemore = true;
		//	player.SetBaseDelay(3);
		//	player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
		//	player.SetDamage(9);
		//	player.SetNeutralization(10);
		//	player.SetDestruction(0);
		//	if (m_ppTripord[(int)CardName::N_ghltjsckd][0] == 1) {
		//		for (int i = 0; i < player.GetFrame_Max(); i++) {
		//			if (i < 2) {
		//				if (player.GetDirection() == Left)
		//					player.SetOder(i, { -20,10 }, -1);
		//				else
		//					player.SetOder(i, { 20,10 }, -1);
		//			}
		//			else {
		//				if (player.GetDirection() == Left)
		//					player.SetOder(i, { -20,-10 }, -1);
		//				else
		//					player.SetOder(i, { 20,-10 }, -1);
		//			}
		//		}

		//	}
		//	else if (m_ppTripord[(int)CardName::N_ghltjsckd][0] == 2) {
		//		player.SetDamage(player.GetDamage() + 2);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_ghltjsckd][0] == 3) {
		//		m_bOnemore = false;
		//		player.SetDamage(player.GetDamage() + 4);
		//	}
		//	if (m_ppTripord[(int)CardName::N_ghltjsckd][1] == 1) {
		//		player.SetType(Knockdown);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_ghltjsckd][1] == 2) {
		//		player.SetNamed_Damage(3);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_ghltjsckd][(int)TriIndex::I_Tier2] == 3) {
		//		PlusUltimate();
		//	}

		//	if (m_ppTripord[(int)CardName::N_ghltjsckd][(int)TriIndex::I_Tier3] == 1) {
		//		if (!m_pHandCard[m_iClickSelect]->GetOnce()) {//찐카드
		//			Ghltjsckd* temp = new Ghltjsckd(m_ppTripord, true);
		//			m_pHandCard[m_iClickSelect] = temp;
		//			canNull = false;
		//		}
		//	}
		//	else if (m_ppTripord[(int)CardName::N_ghltjsckd][(int)TriIndex::I_Tier3] == 2) {
		//		DrawCard(true);
		//	}
		//	break;
		//case CardName::N_dusghkstja: // 연환섬
		//	if (player.GetDirection() == Left)
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_연환섬_이펙트_돌진추가(left).png");
		//	else
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_연환섬_이펙트_돌진추가.png");
		//	for (int i = 0; i < player.GetFrame_Max(); i++) {
		//		if (i < 3) {
		//			if (player.GetDirection() == Left)
		//				player.SetOder(i, { -20,0 }, -1);
		//			else
		//				player.SetOder(i, { 20,0 }, -1);
		//		}
		//		else {
		//			player.SetOder(i, { 0,0 }, -1);
		//		}
		//	}
		//	player.SetBaseDelay(3);
		//	player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
		//	player.SetDamage(6);
		//	player.SetNeutralization(5);
		//	player.SetDestruction(1);
		//	if (m_ppTripord[(int)CardName::N_dusghkstja][0] == 1) {
		//		player.SetFrame_Now(3);
		//		player.SetDamage(6 + 1);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_dusghkstja][0] == 2) {
		//		for (int i = 0; i < player.GetFrame_Max(); i++) {
		//			if (i < 3) {
		//				if (player.GetDirection() == Left)
		//					player.SetOder(i, { -25,0 }, -1);
		//				else
		//					player.SetOder(i, { 25,0 }, -1);
		//			}
		//			else {
		//				player.SetOder(i, { 0,0 }, -1);
		//			}
		//		}
		//	}
		//	else if (m_ppTripord[(int)CardName::N_dusghkstja][(int)TriIndex::I_Tier1] == 3) {
		//		PlusUltimate();
		//	}
		//	if (m_ppTripord[(int)CardName::N_dusghkstja][1] == 1) {
		//		player.SetBaseDelay(2);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_dusghkstja][1] == 2) {
		//		player.SetNeutralization(player.GetNeutralization() + 3);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_dusghkstja][1] == 3) {
		//		player.SetDamage(player.GetDamage() + 2);
		//	}
		//	if (m_ppTripord[(int)CardName::N_dusghkstja][2] == 1) {
		//		DrawCard();
		//	}
		//	else if (m_ppTripord[(int)CardName::N_dusghkstja][2] == 2) {
		//		for (int i = 0; i < player.GetFrame_Max(); i++) {
		//			if (i < 3) {
		//				if (player.GetDirection() == Left)
		//					player.SetOder(i, { -25,0 }, -1);
		//				else
		//					player.SetOder(i, { 25,0 }, -1);
		//			}
		//			else {
		//				player.SetOder(i, { 0,0 }, SowrdLight);
		//			}
		//		}

		//	}

		//	break;
		//case CardName::N_cjdfydcnftn: // 청룡출수
		//	if (player.GetDirection() == Left)
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_청룡출수_이펙트(left).png");
		//	else
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_청룡출수_이펙트.png");
		//	for (int i = 0; i < player.GetFrame_Max(); i++) {
		//		if (i < 4) {
		//			if (player.GetDirection() == Left)
		//				player.SetOder(i, { -20,0 }, -1);
		//			else
		//				player.SetOder(i, { 20,0 }, -1);
		//		}
		//		else {
		//			player.SetOder(i, { 0,0 }, -1);
		//		}
		//	}
		//	player.SetBaseDelay(2);
		//	player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
		//	player.SetDamage(5);
		//	player.SetNeutralization(15);
		//	player.SetDestruction(0);
		//	if (m_ppTripord[(int)CardName::N_cjdfydcnftn][0] == 1) {
		//		player.SetDamage(player.GetDamage() + 1);

		//	}
		//	else if (m_ppTripord[(int)CardName::N_cjdfydcnftn][0] == 2) {
		//		player.SetFrame_Now(4);
		//		player.SetDamage(player.GetDamage() + 2);

		//	}
		//	else if (m_ppTripord[(int)CardName::N_cjdfydcnftn][0] == 3) {
		//		for (int i = 0; i < player.GetFrame_Max(); i++) {
		//			if (i < 4) {
		//				if (player.GetDirection() == Left)
		//					player.SetOder(i, { -25,0 }, -1);
		//				else
		//					player.SetOder(i, { 25,0 }, -1);
		//			}
		//			else {
		//				player.SetOder(i, { 0,0 }, -1);
		//			}
		//		}
		//	}
		//	if (m_ppTripord[(int)CardName::N_cjdfydcnftn][1] == 1) {
		//		player.SetType(Hurricane);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_cjdfydcnftn][1] == 2) {
		//		//TODO:각성게이지 추가회복
		//	}
		//	else if (m_ppTripord[(int)CardName::N_cjdfydcnftn][1] == 3) {
		//		player.SetRect(player.GetRect().left - 30, player.GetRect().top - 30, player.GetRect().right, player.GetRect().bottom);
		//	}
		//	if (m_ppTripord[(int)CardName::N_cjdfydcnftn][2] == 1) {
		//		player.SetOder(player.GetFrame_Max() - 1, { 0,0 }, Rotation_Spear);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_cjdfydcnftn][2] == 2) {
		//		player.SetOder(player.GetFrame_Max() - 1, { 0,0 }, Airborne_Spear);
		//	}

		//	break;
		//case CardName::N_dmsgkdbtjdxks: // 은하유성탄
		//	if (player.GetDirection() == Left)
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_은하유성탄_이펙트(left).png");
		//	else
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_은하유성탄_이펙트.png");
		//	for (int i = 0; i < player.GetFrame_Max(); i++) {
		//		if (i < 4) {
		//			player.SetOder(i, { 0,15 }, -1);
		//		}
		//		else if (i < 9) {
		//			if (i == 7)
		//				player.SetOder(i, { 0, 0 }, Meteor_Spear);
		//			else
		//				player.SetOder(i, { 0, 0 }, -1);
		//		}
		//		else {
		//			if (player.GetFrame_Max() - 1)
		//				player.SetOder(i, { 0, -20 }, Explosion);
		//			else
		//				player.SetOder(i, { 0, -20 }, -1);
		//		}
		//	}
		//	player.SetBaseDelay(5);
		//	player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
		//	player.SetDamage(20);
		//	player.SetNeutralization(40);
		//	player.SetDestruction(2);

		//	break;
		//case CardName::N_wjrfydvh: // 적룡포
		//	if (player.GetDirection() == Left)
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_적룡포_이펙트(left).png");
		//	else
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_적룡포_이펙트.png");
		//	for (int i = 0; i < player.GetFrame_Max(); i++) {
		//		player.SetOder(i, { 0, 0 }, -1);
		//	}
		//	player.SetOder(player.GetFrame_Max() - 2, { 0,0 }, Red_Spear);
		//	player.SetBaseDelay(3);
		//	player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
		//	player.SetDamage(15);
		//	player.SetNeutralization(5);
		//	player.SetDestruction(1);

		//	if (m_ppTripord[(int)CardName::N_wjrfydvh][0] == 1) {
		//		player.SetBaseDelay(2);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_wjrfydvh][0] == 2) {
		//		// 사거리증가는 Insert_Object에서 처리합니다
		//	}
		//	else if (m_ppTripord[(int)CardName::N_wjrfydvh][0] == 3) {
		//		player.SetDamage(player.GetDamage() + 3);
		//	}

		//	if (m_ppTripord[(int)CardName::N_wjrfydvh][1] == 1) {
		//		//TODO:마나감소
		//	}
		//	else if (m_ppTripord[(int)CardName::N_wjrfydvh][(int)TriIndex::I_Tier2] == 2) {
		//		DrawCard(false);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_wjrfydvh][1] == 3) {
		//		player.SetDestruction(player.GetDestruction() + 1);
		//	}

		//	if (m_ppTripord[(int)CardName::N_wjrfydvh][2] == 1) {
		//		// 2층에 추가 창생성 Insert_Object에서 처리합니다
		//	}
		//	else if (m_ppTripord[(int)CardName::N_wjrfydvh][2] == 2) {
		//		player.SetNamed_Damage(player.GetNamed_Damage() + 15);
		//	}

		//	break;
		//case CardName::N_dbtjdrkdcjs: // 유성강천
		//	if (player.GetDirection() == Left)
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_유성강천_이펙트(left).png");
		//	else
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_유성강천_이펙트.png");
		//	for (int i = 0; i < player.GetFrame_Max(); i++) {
		//		if (i < 3) {
		//			if (player.GetDirection() == Left)
		//				player.SetOder(i, { 0,12 }, -1);
		//			else
		//				player.SetOder(i, { 0,12 }, -1);
		//		}
		//		else if (i < 6) {
		//			player.SetOder(i, { 0, 0 }, -1);
		//		}
		//		else if (i < 8) {
		//			if (player.GetDirection() == Left)
		//				player.SetOder(i, { -15,-20 }, -1);
		//			else
		//				player.SetOder(i, { 15,-20 }, -1);

		//		}
		//		else
		//			player.SetOder(i, { 0, 0 }, -1);
		//	}
		//	player.SetBaseDelay(5);
		//	player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
		//	player.SetDamage(12);
		//	player.SetNeutralization(5);
		//	player.SetDestruction(0);
		//	if (m_ppTripord[(int)CardName::N_dbtjdrkdcjs][0] == 1) {
		//		player.SetBaseDelay(4);

		//	}
		//	else if (m_ppTripord[(int)CardName::N_dbtjdrkdcjs][0] == 2) {
		//		player.SetSeedDamage(player.GetSeedDamage() + 2);

		//	}
		//	else if (m_ppTripord[(int)CardName::N_dbtjdrkdcjs][0] == 3) {
		//		player.SetNamed_Damage(player.GetNamed_Damage() + 2);
		//	}
		//	if (m_ppTripord[(int)CardName::N_dbtjdrkdcjs][1] == 1) {
		//		player.SetOder(player.GetFrame_Max() - 1, { 0,0 }, Earthquake);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_dbtjdrkdcjs][1] == 2) {
		//		player.SetOder(player.GetFrame_Max() - 1, { 0,0 }, Flame_Zone);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_dbtjdrkdcjs][1] == 3) {
		//		player.SetOder(player.GetFrame_Max() - 1, { 0,0 }, Wall);
		//	}
		//	if (m_ppTripord[(int)CardName::N_dbtjdrkdcjs][2] == 1) {
		//		player.SetOder(player.GetFrame_Max() - 1, { 0,0 }, Drop_Red_Spear);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_dbtjdrkdcjs][2] == 2) {
		//		for (int i = 0; i < player.GetFrame_Max(); i++) {
		//			player.SetOder(i, { 0, 0 }, -1);
		//		}
		//		player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
		//		if (player.GetDirection() == Left)
		//			player.SetImage(L"./\\윈플 텀프 이미지\\창술사_유성강천창사라지는_이펙트(left).png");
		//		else
		//			player.SetImage(L"./\\윈플 텀프 이미지\\창술사_유성강천창사라지는_이펙트.png");
		//		player.SetOder(4, { 0,0 }, Drop_Red_Spear);
		//	}

		//	break;
		//case CardName::N_rhlddufvk: // 굉열파
		//	if (player.GetDirection() == Left)
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_굉열파_이펙트(left).png");
		//	else
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_굉열파_이펙트.png");
		//	for (int i = 0; i < player.GetFrame_Max(); i++) {
		//		if (i > 4)
		//			if (player.GetDirection() == Left)
		//				player.SetOder(i, { -8,0 }, -1);
		//			else
		//				player.SetOder(i, { 8,0 }, -1);
		//		else
		//			player.SetOder(i, { 0, 0 }, -1);
		//	}
		//	player.SetOder(player.GetFrame_Max() - 2, { 0,0 }, Yellow_Spear);
		//	player.SetBaseDelay(4);
		//	player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
		//	player.SetDamage(10);
		//	player.SetNeutralization(5);
		//	player.SetDestruction(1);
		//	if (m_ppTripord[(int)CardName::N_rhlddufvk][0] == 1) {
		//		player.SetDestruction(player.GetDestruction() + 1);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_rhlddufvk][0] == 2) {
		//		player.SetBaseDelay(3);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_rhlddufvk][0] == 3) {
		//		player.SetRuncount(100);
		//	}
		//	if (m_ppTripord[(int)CardName::N_rhlddufvk][1] == 1) {
		//		if (player.GetDirection() == Left)
		//			player.SetImage(L"./\\윈플 텀프 이미지\\창술사_굉열파_화염이펙트(left).png");
		//		else
		//			player.SetImage(L"./\\윈플 텀프 이미지\\창술사_굉열파_화염이펙트.png");
		//		player.SetType(Fire);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_rhlddufvk][1] == 2) {
		//		//적을 창끝까지 밀쳐냄
		//	}
		//	else if (m_ppTripord[(int)CardName::N_rhlddufvk][1] == 3) {
		//		player.SetNamed_Damage(player.GetNamed_Damage() + 3);
		//	}
		//	if (m_ppTripord[(int)CardName::N_rhlddufvk][2] == 1) {
		//		player.SetBaseDelay(player.GetBaseDelay() + 1);
		//		player.SetDamage(player.GetDamage() + 4);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_rhlddufvk][2] == 2) {
		//		//TODO:마나감소
		//	}

		//	break;
		//case CardName::N_sktjsckd: // 나선창
		//	if (player.GetDirection() == Left)
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_나선창_이펙트(left).png");
		//	else
		//		player.SetImage(L"./\\윈플 텀프 이미지\\창술사_나선창_이펙트.png");
		//	for (int i = 0; i < player.GetFrame_Max(); i++) {
		//		player.SetOder(i, { 0, 0 }, -1);
		//	}
		//	player.SetOder(player.GetFrame_Max() - 1, { 0, 0 }, Purple_Spear);
		//	player.SetBaseDelay(4);
		//	player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
		//	player.SetDamage(7);
		//	player.SetNeutralization(5);
		//	player.SetDestruction(0);

		//	if (m_ppTripord[(int)CardName::N_sktjsckd][0] == 1) {
		//		player.SetSeedDamage(player.GetSeedDamage() + 1);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_sktjsckd][0] == 2) {
		//		player.SetRuncount(100);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_sktjsckd][(int)TriIndex::I_Tier1] == 3) {
		//		PlusUltimate();
		//	}
		//	if (m_ppTripord[(int)CardName::N_sktjsckd][1] == 1) {
		//		m_bOnemore = true;
		//	}
		//	else if (m_ppTripord[(int)CardName::N_sktjsckd][1] == 2) {
		//		player.SetNamed_Damage(player.GetNamed_Damage() + 2);
		//	}
		//	else if (m_ppTripord[(int)CardName::N_sktjsckd][(int)TriIndex::I_Tier2] == 3) {
		//		DrawCard(false);
		//	}
		//	if (m_ppTripord[(int)CardName::N_sktjsckd][2] == 1) {
		//		//사거리증가
		//	}


		//	break;

		//default:
		//	break;
		//}
		//player.SetOder(player.GetFrame_Now(), { 0,0 }, -1);

		if (canNull) {
			m_pHandCard[m_iClickSelect] = nullptr;
			for (int i = m_iClickSelect; i < m_iHandCardCount - 1; i++)
			{
				m_pHandCard[i] = m_pHandCard[i + 1];
			}
			m_iHandCardCount--;
			m_iDeadCardCount++;
		}
	}
}

void Player::SetCardPoint()
{
	if (m_iHandCardCount * 187 > 900)
	{
		int cardTerm = 900 / m_iHandCardCount;
		for (int i = 0; i < m_iHandCardCount; i++)
		{
			m_pHandCard[i]->SetPoint(300 + (cardTerm * i), 800);
		}
	}
	else
	{
		int temp = m_iHandCardCount / 2;
		if (m_iHandCardCount % 2 == 0) {
			for (int i = 0; i < m_iHandCardCount; i++)
			{
				m_pHandCard[i]->SetPoint(800 + (187 * (i - temp)), 800);
			}
		}
		else {
			for (int i = 0; i < m_iHandCardCount; i++)
			{
				m_pHandCard[i]->SetPoint(800 - 187 / 2 + (187 * (i - temp)), 800);
			}
		}
	}
}

void Player::DrawCard()
{
	int randNum;
	bool keepIn = true;
	if (m_iCardCount - (m_iHandCardCount + m_iDeadCardCount) != 0)
		while (keepIn) {
			//m_iCardCount 이내의 숫자 하나를 받아옴
			randNum = RandomGen::GetRand(m_iCardCount);

			//true면 뽑을 수 있다.
			if (m_pCard[randNum]->GetIsValid() == true) {
				m_pHandCard[m_iHandCardCount++] = m_pCard[randNum];
				m_pCard[randNum]->SetIsValid(false);
				keepIn = false;
			}
		}
}

void Player::DrawCard(bool Attention)
{
	int cardIndex[30];
	if (Attention) {//집중카드 뽑을거
		int j = 0, index;
		for (int i = 0; i < m_iCardCount; i++)
		{
			if ((int)m_pCard[i]->GetCardName() <= 3 && m_pCard[i]->GetIsValid() == true) {
				cardIndex[j] = i;
				j++;
			}
		}
		if (j != 0) {
			index = cardIndex[RandomGen::GetRand(j)];
			m_pHandCard[m_iHandCardCount++] = m_pCard[index];
			m_pCard[index]->SetIsValid(false);
		}
	}
	else {		//난무카드뽑을거
		int j = 0, index;
		for (int i = 0; i < m_iCardCount; i++)
		{
			if ((int)m_pCard[i]->GetCardName() >= 4 && m_pCard[i]->GetIsValid() == true) {
				cardIndex[j] = i;
				j++;
			}
		}
		if (j != 0) {
			index = cardIndex[RandomGen::GetRand(j)];
			m_pHandCard[m_iHandCardCount++] = m_pCard[index];
			m_pCard[index]->SetIsValid(false);
		}
	}
}

void Player::PlusUltimate()
{
	m_iUltimate += 10;
	if (m_iUltimate > ULTIMATESKILL)
		m_iUltimate = ULTIMATESKILL;
}

void Player::MakeCard(int randomValue, int** tripord)
{
	Card* temp = nullptr;
	Card* temp1 = nullptr;
	switch (randomValue)
	{
	case (int)CardName::N_rhlddufvk:
		temp = new Rhlddufvk(tripord);
		temp1 = new Rhlddufvk(tripord);
		break;
	case (int)CardName::N_sktjsckd:
		temp = new Sktjsckd(tripord);
		temp1 = new Sktjsckd(tripord);
		break;
	case (int)CardName::N_dbtjdrkdcjs:
		temp = new Dbtjdrkdcjs(tripord);
		temp1 = new Dbtjdrkdcjs(tripord);
		break;
	case (int)CardName::N_wjrfydvh:
		temp = new Wjrfydvh(tripord);
		temp1 = new Wjrfydvh(tripord);
		break;
	case (int)CardName::N_aodfyddufvk:
		temp = new Aodfyddufvk(tripord);
		temp1 = new Aodfyddufvk(tripord);
		break;
	case (int)CardName::N_qksdnjftja:
		temp = new Qksdnjftja(tripord);
		temp1 = new Qksdnjftja(tripord);
		break;
	case (int)CardName::N_dusghkstja:
		temp = new Dusghkstja(tripord);
		temp1 = new Dusghkstja(tripord);
		break;
	case (int)CardName::N_cjdfydwls:
		temp = new Cjdfydwls(tripord);
		temp1 = new Cjdfydwls(tripord);
		break;
	case (int)CardName::N_cjdfydcnftn:
		temp = new Cjdfydcnftn(tripord);
		temp1 = new Cjdfydcnftn(tripord);
		break;
	case (int)CardName::N_ghltjsckd:
		temp = new Ghltjsckd(tripord);
		temp1 = new Ghltjsckd(tripord);
		break;
	case (int)CardName::N_dmsgkdbtjdxks:
		temp = new Dmsgkdbtjdxks();
		temp1 = new Dmsgkdbtjdxks();
		break;
	default:
		temp = nullptr;
		temp1 = nullptr;
		break;
	}

	m_pCard[m_iCardCount++] = temp;
	m_pCard[m_iCardCount++] = temp1;
}

void Player::AddSkillObject(const SkillObject& skillObject)
{
	m_lSkillObjects.push_back(skillObject);
}

CardName Player::GetUseCardName() const
{
	return m_pHandCard[m_iClickSelect]->GetCardName();
}

void Player::SetImg(const TCHAR* str)
{
	m_pImg->Destroy();
	m_pImg->Load(str);
	m_iFrameMax = m_pImg->GetHeight() / 32;
	m_iFrameIdx = 0;
	m_fFrameTime = 0;
}
