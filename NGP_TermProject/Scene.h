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

	bool IsGameStart() const { return m_bStart; }

	// Msg 읽어와 상태 적용하는 코드들
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

	// 현재 가지고 있는 몬스터 리스트
	std::map<int, class Bat*> m_BatMap;
	std::map<int, class Wolf*> m_WolfMap;
	std::map<int, class Bone*> m_BoneMap;
	class Papyrus* m_Papyrus;

	class Castle* m_pCastle;

	class Shop* m_Shop;

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
	// 1p 표시용 화살포 이미지
	CImage m_cArrowImg;
	
	// 현재 마우스 좌표 저장
	int m_iMx, m_iMy;
	// 드래그 시 시작 마우스 좌표 저장
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

