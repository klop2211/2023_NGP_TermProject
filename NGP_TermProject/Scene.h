#pragma once
#include "Player.h"

#include <queue>
#include <map>

struct StateMsgArgu;

class Scene
{
public:
	Scene();
	~Scene();

	void Update(float elapsed);
	void Draw(HDC& memDc);
	void OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnProcessingCommandMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

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

	bool IsGameStart() const { return m_bStart; }

	// Msg �о�� ���� �����ϴ� �ڵ��
	void UpdateMonsterLocation(MonsterType MT, int SN, POINT Location);
	void UpdateMonsterHp(MonsterType MT, int SN, int Hp);
	void UpdateMonsterState(MonsterType MT, int SN, MonsterStateType SMT);
	void UpdateCastleHp(int Hp);
	void UpdateBossState(BossStateType BST);
	void UpdateMonsterKill(int, int, MonsterType);

	void SetWndAndInstance(HWND hWnd, HINSTANCE& Inst);

private:
	static DWORD WINAPI ReceiveThread(LPVOID arg);

private:
	HINSTANCE m_hInst;
	HWND m_hWnd;

	Player* m_pPlayer;
	Player* m_pPlayer2; // 2P
	std::list<Object*> m_lObjectList;

	// ���� ������ �ִ� ���� ����Ʈ
	std::map<int, class Bat*> m_BatMap;
	std::map<int, class Wolf*> m_WolfMap;
	std::map<int, class Bone*> m_BoneMap;
	class Papyrus* m_Papyrus;

	class Castle* m_pCastle;

	class Shop* m_Shop;

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
	// 1p ǥ�ÿ� ȭ���� �̹���
	CImage m_cArrowImg;
	
	// ���� ���콺 ��ǥ ����
	int m_iMx, m_iMy;
	// �巡�� �� ���� ���콺 ��ǥ ����
	int m_iStartX, m_iStartY;

	static std::queue<StateMsgInfo> m_StateMsgQueue;
	static class MemoryReadStream*	m_ReadStream;
	static class MemoryWriteStream* m_WriteStream;

	static SOCKET* m_pSock;
	static HANDLE* m_pReadEvent;
	static HANDLE* m_pWriteEvent;

	static int m_iClientNum;
	static int m_iMsgSize;
	static StateMsgArgu* m_pStateMsgArgu;

};

