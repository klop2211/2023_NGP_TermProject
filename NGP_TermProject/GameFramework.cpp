#include "stdafx.h"
#include "Scene.h"
#include "GameFramework.h"

GameFramework::GameFramework()
{
	m_pScene = new Scene;
}

GameFramework::~GameFramework()
{
	delete m_pScene;
	m_pScene = NULL;
}

void GameFramework::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	m_tPreviousTime = std::chrono::system_clock::now();
}

void GameFramework::Update()
{
	m_pScene->Update(m_fElapsedTime);
}

void GameFramework::Draw()
{
	PAINTSTRUCT ps;
	HDC hDc = BeginPaint(m_hWnd, &ps);
	HDC memDc = CreateCompatibleDC(hDc);
	HBITMAP hBit;
	HBITMAP oldBit = (HBITMAP)SelectObject(memDc, hBit);

	m_pScene->Draw(memDc);

	BitBlt(hDc, 0, 0, WINWIDTH, WINHEIGHT, memDc, 0, 0, SRCCOPY);

	SelectObject(memDc, oldBit);
	DeleteDC(memDc);
	EndPaint(m_hWnd, &ps);
}

void GameFramework::FrameAdvance()
{
	SetElapsedTime();
	Update();
	Draw();
}

void GameFramework::SetElapsedTime()
{
	auto currentTime = std::chrono::system_clock::now();

	std::chrono::duration<float> elapsedSeconds = currentTime - m_tPreviousTime;

	m_tPreviousTime = currentTime;

	m_fElapsedTime = elapsedSeconds.count();

}
