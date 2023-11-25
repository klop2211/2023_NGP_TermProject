#include "stdafx.h"
#include "PlayerOwnedStates.h"
#include "Player.h"

Player::Player()
{
	m_dDir = Right;
	m_pImg = new CImage;
	SetImg(L"./윈플 텀프 이미지/창술사.png");
	m_pStateMachine = new StateMachine<Player>(this);
	m_pStateMachine->SetCurrentState(PStay::Instance());
	m_Location.x = 100;
	m_Location.y = 100;
	m_iSpeed = 0;
	SetRect(RECT{ 100, 100, 100 + PLAYER_SIZE, 100 + PLAYER_SIZE });
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
	if (m_dDir == Right)
		m_Location.x += m_iSpeed * elapsed;
	else
		m_Location.x -= m_iSpeed * elapsed;
	SetRectByLocation();
}

void Player::Draw(HDC& memDc)
{
	m_pImg->Draw(memDc, m_rRect.left, m_rRect.top, m_rRect.right - m_rRect.left, m_rRect.bottom - m_rRect.top, 0, m_pImg->GetHeight() / m_iFrameMax * m_iFrameIdx, m_pImg->GetWidth(), m_pImg->GetHeight() / m_iFrameMax);

}

void Player::ChangeState(State<Player>* cState)
{
	m_pStateMachine->ChangeState(cState);
}

void Player::OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

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
			ChangeState(PMove::Instance());
			break;
		case 'a':
		case 'A':
			SetDir(Left);
			ChangeState(PMove::Instance());
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{

		default:
			break;
		}
		break;
	default:
		break;
	}

}

void Player::SetImg(const TCHAR* str)
{
	m_pImg->Destroy();
	m_pImg->Load(str);
	m_iFrameMax = m_pImg->GetHeight() / 32;
	m_iFrameIdx = 0;
}
