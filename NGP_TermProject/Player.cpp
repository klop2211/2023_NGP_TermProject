#include "stdafx.h"
#include "PlayerOwnedStates.h"
#include "Player.h"
#include "Card.h"
#include "Random.h"
#include "OtherCard.h"
#include "../MemStream/MemoryWriteStream.h"

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

	m_iMaxMana = 10;
	m_iManaCount = 10;

	m_iLevel = 0;
	m_bOnemore = false;
	m_iMoney = 0;
	m_fDrawTimer = 0.f;
	m_fManaTimer = 0.f;

	m_bSkillCheck = false;

	m_iExperience = 0;
	for (int i = 0; i < 10; i++)
	{
		m_iExperienceBar[i] = (i + 1) * (i + 1) * 2 + 30 / (i + 2);
	}

	memset(m_ppTripord, 0, sizeof(int) * 40);

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
		if (m_pStateMachine->isInState(*PSkill::Instance())) {
			m_bSkillCheck = true;
			ChangeState(PStateName::Stay);
		}
		m_fFrameTime = 0.f;
		m_iFrameIdx = 0;
	}

	for (auto p = m_lSkillObjects.begin(); p != m_lSkillObjects.end(); ++p) {
		p->Update(elapsed);
		if (!p->GetLife()) {
			auto temp = p;
			++p;
			m_lSkillObjects.erase(temp);
			if (p == m_lSkillObjects.end())
				break;
		}
	}	

	// 카드를 다쓰면 덱 초기화
	if (m_iCardCount == m_iDeadCardCount) {
		ResetCard();
		m_bCardDrawing = true;
	}

	if (m_bCardDrawing) {
		if (m_iCardCount >= 10)
		{
			//시작용 4장 뽑기
			for (int i = 0; i < 4; i++) {
				DrawCard();
			}
			m_bCardDrawing = false;

			//4장의 자리배치
			SetCardPoint();
		}
	}

	if (m_iCardCount >= 10 && m_iHandCardCount < 7)
	{
		m_fDrawTimer += elapsed;
		if (m_fDrawTimer >= 2.5f)
		{
			DrawCard();
			SetCardPoint();
			m_fDrawTimer = 0;
		}
	}

	if (m_iManaCount < m_iMaxMana)
	{
		m_fManaTimer += elapsed;
		if (m_fManaTimer >= 1.f)
		{
			++m_iManaCount;
			m_fManaTimer = 0;
		}
	}
}

void Player::Draw(HDC& memDc)
{
	m_pImg->Draw(memDc, m_rRect.left, m_rRect.top, m_rRect.right - m_rRect.left, m_rRect.bottom - m_rRect.top, 0, m_pImg->GetHeight() / m_iFrameMax * m_iFrameIdx, m_pImg->GetWidth(), m_pImg->GetHeight() / m_iFrameMax);
	
	for (auto& obj : m_lSkillObjects) {
		obj.Draw(memDc);
	}
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

	m_iSelectCard = -1;

	// 마우스 입력처리
	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_bIsClick = true;
		m_iStartX = mx;
		m_iStartY = my;


		for (int i = 0; i < m_iHandCardCount; i++)
		{
			if (mx > m_pHandCard[i]->GetPoint().x && mx < m_pHandCard[i]->GetPoint().x + CARDMINIWIDTH\
				&& my > m_pHandCard[i]->GetPoint().y && my < m_pHandCard[i]->GetPoint().y + CARDMINIHEIGHT)
			{
				m_iClickSelect = i;
			}
		}

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
		else
		{
			//마우스와 카드 연관 처리
			for (int i = 0; i < m_iHandCardCount; i++)
			{
				if (mx > m_pHandCard[i]->GetPoint().x && mx < m_pHandCard[i]->GetPoint().x + CARDMINIWIDTH\
					&& my > m_pHandCard[i]->GetPoint().y && my < m_pHandCard[i]->GetPoint().y + CARDMINIHEIGHT)
				{
					//if (m_bIsClick) {
					//	m_iClickSelect = i;
					if (m_pPrevCardPoint.x == -1)
						m_pPrevCardPoint = m_pHandCard[i]->GetPoint();
					//}
					//else
						m_iSelectCard = i;
					break;
				}
			}
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
			if (m_iUltimate >= 100) {
				m_CurrentCardName = CardName::N_dmsgkdbtjdxks;
				ChangeState(PSkill::Instance());
				m_iUltimate = 0;
			}

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

		case 't':
		case 'T':
			ChangeState(PSkill::Instance());
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

void Player::OnProcessingCommandMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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

	//카드 출력
	for (int i = 0; i < m_iHandCardCount; i++) {
		if (i == m_iSelectCard)
			m_pHandCard[i]->closeDraw(memDc);
		else if (i == m_iClickSelect)
			m_pHandCard[i]->dragDraw(memDc);
		else
			m_pHandCard[i]->handDraw(memDc);
	}

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
		m_bSkillCheck = true;
		m_CurrentCardName = GetUseCardName();
		ChangeState(PSkill::Instance());

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

void Player::MakeCard(int randomValue)
{
	Card* temp = nullptr;
	Card* temp1 = nullptr;
	switch (randomValue)
	{
	case (int)CardName::N_rhlddufvk:
		temp = new Rhlddufvk(m_ppTripord[(int)CardName::N_rhlddufvk]);
		temp1 = new Rhlddufvk(m_ppTripord[(int)CardName::N_rhlddufvk]);
		break;
	case (int)CardName::N_sktjsckd:
		temp = new Sktjsckd(m_ppTripord[(int)CardName::N_sktjsckd]);
		temp1 = new Sktjsckd(m_ppTripord[(int)CardName::N_sktjsckd]);
		break;
	case (int)CardName::N_dbtjdrkdcjs:
		temp = new Dbtjdrkdcjs(m_ppTripord[(int)CardName::N_dbtjdrkdcjs]);
		temp1 = new Dbtjdrkdcjs(m_ppTripord[(int)CardName::N_dbtjdrkdcjs]);
		break;
	case (int)CardName::N_wjrfydvh:
		temp = new Wjrfydvh(m_ppTripord[(int)CardName::N_wjrfydvh]);
		temp1 = new Wjrfydvh(m_ppTripord[(int)CardName::N_wjrfydvh]);
		break;
	case (int)CardName::N_aodfyddufvk:
		temp = new Aodfyddufvk(m_ppTripord[(int)CardName::N_aodfyddufvk]);
		temp1 = new Aodfyddufvk(m_ppTripord[(int)CardName::N_aodfyddufvk]);
		break;
	case (int)CardName::N_qksdnjftja:
		temp = new Qksdnjftja(m_ppTripord[(int)CardName::N_qksdnjftja]);
		temp1 = new Qksdnjftja(m_ppTripord[(int)CardName::N_qksdnjftja]);
		break;
	case (int)CardName::N_dusghkstja:
		temp = new Dusghkstja(m_ppTripord[(int)CardName::N_dusghkstja]);
		temp1 = new Dusghkstja(m_ppTripord[(int)CardName::N_dusghkstja]);
		break;
	case (int)CardName::N_cjdfydwls:
		temp = new Cjdfydwls(m_ppTripord[(int)CardName::N_cjdfydwls]);
		temp1 = new Cjdfydwls(m_ppTripord[(int)CardName::N_cjdfydwls]);
		break;
	case (int)CardName::N_cjdfydcnftn:
		temp = new Cjdfydcnftn(m_ppTripord[(int)CardName::N_cjdfydcnftn]);
		temp1 = new Cjdfydcnftn(m_ppTripord[(int)CardName::N_cjdfydcnftn]);
		break;
	case (int)CardName::N_ghltjsckd:
		temp = new Ghltjsckd(m_ppTripord[(int)CardName::N_ghltjsckd]);
		temp1 = new Ghltjsckd(m_ppTripord[(int)CardName::N_ghltjsckd]);
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


void Player::AddSkillObject(const ObjectType& type)
{
	m_lSkillObjects.emplace_back(type, this);
}

UseCardStateMsg* Player::CreateUseCardStateMsg(int clientNum)
{
	UseCardStateMsg* temp = new UseCardStateMsg;
	temp->PlayerId = clientNum;
	temp->Card = (CardType)m_CurrentCardName;
	temp->Damage = m_iDamage;
	temp->StunDamage = m_iStunDamage;
	temp->NamedDamage = m_iNamedDamage;
	temp->Destuction = m_iDestruction;
	temp->Type = m_iType;

	return temp;
}

void Player::CreateSOLMsg(int clientNum, MemoryWriteStream* mws)
{
	StateMsgType smt = StateMsgType::SkillObjectLocation;
	SkillObjectLocationMsg sol;
	for (auto& obj : m_lSkillObjects) {
		sol.PlayerId = clientNum;
		sol.ObjectType = obj.GetObjectType();
		sol.Location = POINT{ (int)obj.GetLocation().x, (int)obj.GetLocation().y };
		sol.Size = obj.GetRect().right - obj.GetRect().left;
		mws->Write(smt);
		mws->Write(sol);
	}

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

void Player::SetCardTripod(int cardEnum)
{
	for (int i = 0; i < m_iCardCount; i++)
	{
		CardName CN = m_pCard[i]->GetCardName();
		if ((int)CN == cardEnum) {
			m_pCard[i]->SetTripord(m_ppTripord[(int)CN]);
			m_pCard[i]->__init__();
		}
	}
}

void Player::ResetCard()
{
	for (int i = 0; i < m_iCardCount; i++)
	{
		m_pCard[i]->SetIsValid(true);
	}
	m_iDeadCardCount = 0;
	m_iHandCardCount = 0;
}
