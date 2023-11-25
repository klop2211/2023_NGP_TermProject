#include "stdafx.h"
#include "PlayerOwnedStates.h"
#include "Scene.h"

Scene::Scene()
{
	m_pPlayer = new Player;
	m_lObjectList.push_back(m_pPlayer);

}

Scene::~Scene()
{
}

void Scene::Update(float elapsed)
{
	for (auto object : m_lObjectList) {
		object->Update(elapsed);
	}
}

void Scene::Draw(HDC& memDc)
{
	// 배경 여기서 그려줘야함

	for (auto object : m_lObjectList) {
		object->Draw(memDc);
	}
}

void Scene::OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 마우스 입력처리
	switch (message)
	{
	default:
		break;
	}
}

void Scene::OnProcessingKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
			m_pPlayer->SetDir(Right);
			m_pPlayer->ChangeState(PMove::Instance());
			break;
		case 'a':
		case 'A':
			m_pPlayer->SetDir(Left);
			m_pPlayer->ChangeState(PMove::Instance());
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
