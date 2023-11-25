#pragma once
#include "Player.h"


class Scene
{
public:
	Scene();
	~Scene();

	void Update(float elapsed);
	void Draw(HDC& memDc);
	void OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	Player* m_pPlayer;
	std::list<Object*> m_lObjectList;

};

