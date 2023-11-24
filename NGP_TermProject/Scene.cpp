#include "stdafx.h"
#include "Player.h"
#include "Scene.h"

Scene::Scene()
{
	m_pPlayer = new Player;
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
