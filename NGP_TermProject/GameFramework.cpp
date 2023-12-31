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

	m_pScene->SetWndAndInstance(hWnd, m_hInst);
}

void GameFramework::Update()
{
	m_pScene->Update(m_fElapsedTime);
}

void GameFramework::Draw()
{
	HDC hDc = GetDC(m_hWnd);
	HDC memDc = CreateCompatibleDC(hDc);
	HBITMAP hBit = CreateCompatibleBitmap(hDc, WINWIDTH, WINHEIGHT);
	HBITMAP oldBit = (HBITMAP)SelectObject(memDc, hBit);

	m_pScene->Draw(memDc);

	BitBlt(hDc, 0, 0, WINWIDTH, WINHEIGHT, memDc, 0, 0, SRCCOPY);

	SelectObject(memDc, oldBit);
	DeleteDC(memDc);
	ReleaseDC(m_hWnd, hDc);
}

void GameFramework::FrameAdvance()
{
	auto interval = std::chrono::milliseconds(16);
	auto currentTime = std::chrono::system_clock::now();
	if (currentTime - m_tPreviousTime >= interval) {
		if (m_pScene->IsGameStart()) {
			//m_pScene->WaitReadEvent();   // 읽기 완료 대기
			SetElapsedTime();
			Update();
			Draw();
			//m_pScene->SetWriteEvent();
		}
		else {
			SetElapsedTime();
			Update();
			Draw();
		}
	}
}

void GameFramework::SetElapsedTime()
{
	auto currentTime = std::chrono::system_clock::now();

	std::chrono::duration<float> elapsedSeconds = currentTime - m_tPreviousTime;

	m_tPreviousTime = currentTime;

	m_fElapsedTime = elapsedSeconds.count();

}

void GameFramework::OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pScene->OnProcessingMouseMessage(hWnd, message, wParam, lParam);
	switch (message)
	{
	default:
		break;
	}
}

void GameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pScene->OnProcessingKeyboardMessage(hWnd, message, wParam, lParam);
	switch (message)
	{
	default:
		break;
	}

}

LRESULT CALLBACK GameFramework::OnProcessingWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		OnProcessingMouseMessage(hWnd, message, wParam, lParam);
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
		OnProcessingKeyboardMessage(hWnd, message, wParam, lParam);
		break;

	default:
		break;
	}
	return LRESULT(0);
}

void GameFramework::OnProcessingCommandMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pScene->OnProcessingCommandMessage(hWnd, message, wParam, lParam);
}
