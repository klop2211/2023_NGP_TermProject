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

void Player::SetImg(const TCHAR* str)
{
	m_pImg->Destroy();
	m_pImg->Load(str);
	m_iFrameMax = m_pImg->GetHeight() / 32;
	m_iFrameIdx = 0;
	m_fFrameTime = 0;
}
