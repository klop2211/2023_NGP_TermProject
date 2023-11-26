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

	// ȭ�� �ٲٴµ� ���
	float m_fChangeCount;

	// �� �̹���
	CImage m_cClosing;
	// ���ȭ��
	CImage m_cBackGround;
};

