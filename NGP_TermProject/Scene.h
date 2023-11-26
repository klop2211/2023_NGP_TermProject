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

	// ���� ������ ���̵�ƿ�
	void DrawChangeLoading(HDC& memDc);
	void UpdateChangeLoading(float elapsed);

	// ���� ������ ����ȭ��
	void DrawGameLoading(HDC& memDc);

	// ���� ����ȭ��
	void DrawGameStart(HDC& memDc);
	void UpdateGameStart(float elapsed);

	// ���� ������ ���̵���
	void DrawChangeStart(HDC& memDc);
	void UpdateChangeStart(float elapsed);
private:
	Player* m_pPlayer;
	std::list<Object*> m_lObjectList;

	class Castle* m_pCastle;

	// ������ �����ߴ���
	bool m_bStart;
	// ȭ���� �ٲ�� ������
	bool m_bChanging;
	// ī�� �̴�������
	bool m_bCardDrawing;
	// Ŭ��������(Ȧ�� �巡��)
	bool m_bIsClick;

	// ȭ�� �ٲٴµ� ���
	float m_fChangeCount;

	// �� �̹���
	CImage m_cClosing;
	// ���ȭ��
	CImage m_cBackGround;
	// Ÿ��Ʋ ȭ�鿡 ���̴� �̹���
	CImage m_cLoadBit, m_cStartBit, m_cQuitBit;

	// ���� ���콺 ��ǥ ����
	int m_iMx, m_iMy;
	// �巡�� �� ���� ���콺 ��ǥ ����
	int m_iStartX, m_iStartY;
};

