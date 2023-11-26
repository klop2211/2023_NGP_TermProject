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

	// 게임 시작전 페이드아웃
	void DrawChangeLoading(HDC& memDc);
	void UpdateChangeLoading(float elapsed);

	// 게임 시작전 선택화면
	void DrawGameLoading(HDC& memDc);

	// 메인 게임화면
	void DrawGameStart(HDC& memDc);
	void UpdateGameStart(float elapsed);

	// 게임 시작전 페이드인
	void DrawChangeStart(HDC& memDc);
	void UpdateChangeStart(float elapsed);
private:
	Player* m_pPlayer;
	std::list<Object*> m_lObjectList;

	class Castle* m_pCastle;

	// 게임이 시작했는지
	bool m_bStart;
	// 화면이 바뀌는 중인지
	bool m_bChanging;
	// 카드 뽑는중인지
	bool m_bCardDrawing;
	// 클릭중인지(홀드 드래그)
	bool m_bIsClick;

	// 화면 바꾸는데 사용
	float m_fChangeCount;

	// 원 이미지
	CImage m_cClosing;
	// 배경화면
	CImage m_cBackGround;
	// 타이틀 화면에 쓰이는 이미지
	CImage m_cLoadBit, m_cStartBit, m_cQuitBit;

	// 현재 마우스 좌표 저장
	int m_iMx, m_iMy;
	// 드래그 시 시작 마우스 좌표 저장
	int m_iStartX, m_iStartY;
};

