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
	// ��� ���⼭ �׷������

	for (auto object : m_lObjectList) {
		object->Draw(memDc);
	}
}

void Scene::OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// ���콺 �Է�ó��
	switch (message)
	{
	default:
		break;
	}
}

void Scene::OnProcessingKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
