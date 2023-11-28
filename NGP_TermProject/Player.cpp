#include "stdafx.h"
#include "PlayerOwnedStates.h"
#include "Player.h"

Player::Player()
{
	m_dDir = Right;
	m_pImg = new CImage;
	SetImg(L"./���� ���� �̹���/â����.png");
	m_pStateMachine = new StateMachine<Player>(this);
	m_pStateMachine->SetCurrentState(PStay::Instance());
	m_Location.x = 100;
	m_Location.y = GROUNDYPOINT - PLAYER_SIZE;
	m_iSpeed = 0;
	m_fFrameTime = 0.f;
	SetRect(RECT{ 100, 100, 100 + PLAYER_SIZE, 100 + PLAYER_SIZE });

	m_pUltiImg = new CImage;	m_pUltiImg->Load(TEXT("ī�����//��ų�ʻ�ȭ//������.png"));
	m_pDeck = new CImage;		m_pDeck->Load(TEXT("���� ���� �̹���//ī��޸�.png"));
	m_pManaImg[0] = new CImage;	m_pManaImg[0]->Load(TEXT("���� ���� �̹���//����.png"));
	m_pManaImg[1] = new CImage;	m_pManaImg[1]->Load(TEXT("���� ���� �̹���//�󸶳�.png"));

	m_iUltimate = 0;	
	m_iCardCount = 0;
	m_iHandCardCount = 0;
	m_iDeadCardCount = 0;
	m_iMaxMana = 0;
	m_iManaCount = 0;
	m_iLevel = 0;

	m_iExperience = 0;
	for (int i = 0; i < 10; i++)
	{
		m_iExperienceBar[i] = (i + 1) * (i + 1) * 2 + 30 / (i + 2);
	}
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

	// �̵�
	if (m_dDir == Right)
		m_Location.x += m_iSpeed * elapsed;
	else
		m_Location.x -= m_iSpeed * elapsed;

	// ��ġ��� RECT ����
	SetRectByLocation();

	// ��������Ʈ ������ ����
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

void Player::OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// ���콺 �Է�ó��
	//switch (message)
	//{
	//case WM_LBUTTONDOWN:
	//	if (!m_bCardDrawing)
	//	{
	//		m_bIsClick = true;
	//		m_iStartX = m_iMx;
	//		m_iStartY = m_iMy;
	//	}
	//	break;
	//case WM_MOUSEMOVE:
	//	m_iMx = LOWORD(lParam);
	//	m_iMy = HIWORD(lParam);

	//	// TODO: ī�带 ������ �� Ŀ�� ��ġ�� �� ī�� ��ġ�ϰ�
	//	if (m_bIsClick && clickSelect != -1){
	//		handCard[clickSelect]->point.x += (m_iMx - m_iStartX);
	//		handCard[clickSelect]->point.y += (m_iMy - m_iStartY);
	//		m_iStartX = m_iMx;
	//		m_iStartY = m_iMy;
	//	}
	//	break;
	//case WM_LBUTTONUP:
	//	if (m_bIsClick) {
	//		//TODO: �÷��̾ ī�� ���ó��

	//		m_bIsClick = false;
	//		//if (clickSelect != -1) {
	//		//	if (m_iMy < WINHEIGHT * 3 / 5 && manaCount >= handCard[clickSelect]->Mana) {
	//		//		manaCount -= handCard[clickSelect]->Mana;
	//		//		useCard();
	//		//		setCardPoint();
	//		//	}
	//		//	else {
	//		//		handCard[clickSelect]->point = prevCardPoint;
	//		//	}
	//		//	clickSelect = -1;
	//		//	prevCardPoint = { -1,-1 };
	//		//}
	//	}
	//	break;
	//default:
	//	break;
	//}
}

void Player::OnProcessingKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Ű���� �Է�ó��
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'e':
		case 'E':
			//TODO ������ �ߵ�
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

	//������ ���â
	m_pUltiImg->Draw(memDc, WINWIDTH - 150, 10, 100, 100,
		0, 0, 77, 77);
	hBrush = CreateSolidBrush(RGB(255, 215, 0));
	oldBrush = (HBRUSH)SelectObject(memDc, hBrush);
	Rectangle(memDc, WINWIDTH - 150, 100, WINWIDTH - 150 + ((double)m_iUltimate / ULTIMATESKILL) * 100, 110);
	SelectObject(memDc, oldBrush); DeleteObject(hBrush);

	// ���ʾƷ� ī�� ��
	m_pDeck->Draw(memDc, -44, 750, 204, 300,
		0, 0, m_pDeck->GetWidth(), m_pDeck->GetHeight());

	//���� ī�� ���� ��
	RECT deckText = { 135, 725, 185, 775 };
	Ellipse(memDc, deckText.left, deckText.top, deckText.right, deckText.bottom);
	swprintf_s(numStr, L"%d", m_iCardCount - (m_iHandCardCount + m_iDeadCardCount));
	DrawText(memDc, numStr, lstrlen(numStr), &deckText, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	//����ġ�� ���
	hBrush = CreateSolidBrush(RGB(0, 255, 255));
	oldBrush = (HBRUSH)SelectObject(memDc, hBrush);
	Rectangle(memDc, 170, WINHEIGHT - ((double)m_iExperience / m_iExperienceBar[m_iLevel]) * 100, 190, WINHEIGHT);
	SelectObject(memDc, oldBrush); DeleteObject(hBrush);

	//�������
	RECT levelRect = { 150, WINHEIGHT - 20, 210, WINHEIGHT };
	swprintf_s(numStr, L"%d", m_iLevel + 1);
	Rectangle(memDc, 150, WINHEIGHT - 20, 210, WINHEIGHT);
	DrawText(memDc, numStr, lstrlen(numStr), &levelRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	//�� ����
	for (int i = 0; i < m_iMaxMana; i++)
	{
		m_pManaImg[1]->Draw(memDc, 1600 - 55 * ((i % 5) + 1), 900 - 55 * ((i / 5) + 1), 50, 50, 0, 0, m_pManaImg[1]->GetWidth(), m_pManaImg[1]->GetHeight());
	}
	//�� ����
	for (int i = 0; i < m_iManaCount; i++)
	{
		m_pManaImg[0]->Draw(memDc, 1600 - 55 * ((i % 5) + 1), 900 - 55 * ((i / 5) + 1), 50, 50, 0, 0, m_pManaImg[0]->GetWidth(), m_pManaImg[0]->GetHeight());
	}
}

void Player::SetImg(const TCHAR* str)
{
	m_pImg->Destroy();
	m_pImg->Load(str);
	m_iFrameMax = m_pImg->GetHeight() / 32;
	m_iFrameIdx = 0;
	m_fFrameTime = 0;
}
