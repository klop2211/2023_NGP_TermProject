#pragma once
#include <chrono>

class Scene;

class GameFramework
{
public:
	GameFramework();
	~GameFramework();

	void Init(HWND hWnd);
	void Update();
	void Draw();
	void FrameAdvance();
	void SetElapsedTime();
	void OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND m_hWnd;
	Scene* m_pScene;
	float m_fElapsedTime;
	std::chrono::time_point<std::chrono::system_clock> m_tPreviousTime;
};

