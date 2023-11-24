#include "stdafx.h"
#include "StateMachine.h"
#include "PlayerOwnedStates.h"
#include "Player.h"

Player::Player()
{
	m_dDir = Right;
	m_pImg = new CImage;
	m_pImg->Load(L"./윈플 텀프 이미지/창술사.png");
	m_pStateMachine = new StateMachine<Player>(this);

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
	m_pStateMachine->Update();
}

void Player::Draw(HDC& memDc)
{

}

void Player::SetImg(const TCHAR* str)
{
	m_pImg->Destroy();
	m_pImg->Load(str);
}
