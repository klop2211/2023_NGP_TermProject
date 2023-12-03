#include "stdafx.h"
#include "Common.h"
#include "PlayerOwnedStates.h"
#include "Scene.h"
#include "Castle.h"
#include "../Server/StateMessage.h"

#include "../MemStream/MemoryReadStream.h"
#include "../MemStream/MemoryWriteStream.h"

#define MULTI_PLAY

SOCKET*			Scene::m_pSock;
HANDLE*			Scene::m_pReadEvent;
HANDLE*			Scene::m_pWriteEvent;
int				Scene::m_iClientNum;
int				Scene::m_iMsgSize;
StateMsgArgu*	Scene::m_pStateMsgArgu;

std::queue<StateMsgInfo>	Scene::m_StateMsgQueue;
MemoryReadStream*			Scene::m_ReadStream;
MemoryWriteStream*			Scene::m_WriteStream;

Scene::Scene()
{
	m_pPlayer = NULL;
	m_pPlayer2 = NULL;
	m_pCastle = new Castle;

	m_fChangeCount = 0;
	m_cClosing.Load(TEXT("윈플 텀프 이미지\\원.png"));
	m_cBackGround.Load(TEXT("윈플 텀프 이미지\\배경성X.png"));
	m_cLoadBit.Load(TEXT("윈플 텀프 이미지\\레온하트성.png"));
	m_cStartBit.Load(TEXT("윈플 텀프 이미지\\Start.png"));
	m_cQuitBit.Load(TEXT("윈플 텀프 이미지\\Quit.png"));
	m_cArrowImg.Load(L"./윈플 텀프 이미지/화살표.png");

	m_bStart = false, m_bChanging = false; 				//원래 시작용
	//m_bStart = true, changing = false;				//화면바뀌는거 귀찮아서 만든거
	m_bCardDrawing = true, m_bIsClick = false;
}

Scene::~Scene()
{
	m_cClosing.Destroy();
	m_cBackGround.Destroy();
	m_cLoadBit.Destroy();
	m_cStartBit.Destroy();
	m_cQuitBit.Destroy();

	delete m_pSock;
	delete m_pReadEvent;
	delete m_pWriteEvent;

}

void Scene::Update(float elapsed)
{
	// 현 순서는 gameLoading -> changeLoading -> chageStart -> gameStart;
	if (m_bStart) {
		if (m_bChanging)
		{
			UpdateChangeStart(elapsed);		//게임 시작전 유사 페이드인
		}
		else
		{
			UpdateGameStart(elapsed);		//메인 게임화면
			

			//TODO: 게임종료
		}

#ifdef MULTI_PLAY
		WaitForSingleObject(*m_pReadEvent, INFINITE);
		while (!m_StateMsgQueue.empty())
		{
			StateMsgInfo SMI = m_StateMsgQueue.front();
			m_StateMsgQueue.pop();

			PlayerLocationMsg* temp = (PlayerLocationMsg*)SMI.pStateMsgArgu;
			if (temp->PlayerId != m_iClientNum && m_pPlayer2 != NULL) {
				m_pPlayer2->SetLocation(temp->Location);
				m_pPlayer2->SetDir((Direction)temp->Direction);
				if (m_pPlayer2->GetStateName() != temp->State)
					m_pPlayer2->ChangeState(temp->State);
			}
		}
		//if (m_pStateMsgArgu != NULL) {
		//	PlayerLocationMsg* temp = (PlayerLocationMsg*)m_pStateMsgArgu;
		//	if (temp->PlayerId != m_iClientNum && m_pPlayer2 != NULL) {
		//		m_pPlayer2->SetLocation(temp->Location);
		//		m_pPlayer2->SetDir((Direction)temp->Direction);
		//		if (m_pPlayer2->GetStateName() != temp->State)
		//			m_pPlayer2->ChangeState(temp->State);
		//	}
		//}

		StateMsgType smt = StateMsgType::PlayerLocation;
		PlayerLocationMsg sma;
		if (m_pPlayer != NULL) {
			sma.Location.x = (int)m_pPlayer->GetLocation().x;
			sma.Location.y = (int)m_pPlayer->GetLocation().y;
			sma.PlayerId = m_iClientNum;
			sma.Direction = m_pPlayer->GetDir();
			sma.State = m_pPlayer->GetStateName();
		}
		else {
			sma.Location.x = 100;
			sma.Location.y = 200;
			sma.PlayerId = -1;
			sma.Direction = 0;
			sma.State = PStateName::Move;
		}
		m_WriteStream->Write(smt);
		m_WriteStream->Write(sma);

		//StateMsgType smt = StateMsgType::PlayerLocation;
		//send(*m_pSock, (char*)&smt, sizeof(StateMsgType), 0);

		//PlayerLocationMsg sma;
		//if (m_pPlayer != NULL) {
		//	sma.Location.x = (int)m_pPlayer->GetLocation().x;
		//	sma.Location.y = (int)m_pPlayer->GetLocation().y;
		//	sma.PlayerId = m_iClientNum;
		//	sma.Direction = m_pPlayer->GetDir();
		//	sma.State = m_pPlayer->GetStateName();
		//}
		//else {
		//	sma.Location.x = 100;
		//	sma.Location.y = 200;
		//	sma.PlayerId = -1;
		//	sma.Direction = 0;
		//	sma.State = PStateName::Move;
		//}
		//send(*m_pSock, (char*)&sma, sizeof(PlayerLocationMsg), 0);
		m_WriteStream->Send();
		SetEvent(*m_pWriteEvent);

#endif // STAND_ALONE

	}
	else {
		if (m_bChanging)
			UpdateChangeLoading(elapsed);	// 게임 시작전 유사 페이드아웃
	}



	for (auto object : m_lObjectList) {
		object->Update(elapsed);
	}
}

void Scene::Draw(HDC& memDc)
{
	// 배경 여기서 그려줘야함
	// 현 순서는 gameLoading -> changeLoading -> chageStart -> gameStart;
	if (m_bStart) {
		if (m_bChanging)
		{
			DrawChangeStart(memDc);
		}
		else
		{
			DrawGameStart(memDc);
		}
	}
	else {
		if (m_bChanging)
			DrawChangeLoading(memDc);
		else
			DrawGameLoading(memDc);
	}

	for (auto object : m_lObjectList) {
		object->Draw(memDc);
	}
}

void Scene::OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 마우스 입력처리
	switch (message)
	{
	case WM_LBUTTONDOWN:
		if (m_bStart) {
			if (!m_bCardDrawing) {
				m_bIsClick = true;
				m_iStartX = m_iMx;
				m_iStartY = m_iMy;
			}
		}
		else
		{
			// 선택화면의 클릭 처리
			if (m_iMx >= 500 && m_iMx <= 1100)
			{
				// GameStart 버튼
				if (m_iMy >= 550 && m_iMy <= 650)
				{
#ifdef MULTI_PLAY
					m_pReadEvent = new HANDLE;
					m_pWriteEvent = new HANDLE;
					*m_pReadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
					*m_pWriteEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
					CreateThread(NULL, 0, ReceiveThread, NULL, 0, NULL);

#endif // DEBUG


					m_bChanging = true;
				}
				// Quit 버튼
				else if (m_iMy >= 700 && m_iMy <= 800)
				{
					PostQuitMessage(0);
				}
			}
		}
		break;
	case WM_MOUSEMOVE:
		m_iMx = LOWORD(lParam);
		m_iMy = HIWORD(lParam);

		// TODO: 카드를 집었을 때 커서 위치에 그 카드 위치하게
		//if (m_bIsClick && clickSelect != -1) {
		//	handCard[clickSelect]->point.x += (m_iMx - m_iStartX);
		//	handCard[clickSelect]->point.y += (m_iMy - m_iStartY);
		//	m_iStartX = m_iMx;
		//	m_iStartY = m_iMy;
		//}
		break;
	case WM_LBUTTONUP:
		if (m_bIsClick) {
			//TODO: 플레이어가 카드 사용처리
			
			m_bIsClick = false;
			//if (clickSelect != -1) {
			//	if (m_iMy < WINHEIGHT * 3 / 5 && manaCount >= handCard[clickSelect]->Mana) {
			//		manaCount -= handCard[clickSelect]->Mana;
			//		useCard();
			//		setCardPoint();
			//	}
			//	else {
			//		handCard[clickSelect]->point = prevCardPoint;
			//	}
			//	clickSelect = -1;
			//	prevCardPoint = { -1,-1 };
			//}
		}
		break;
	default:
		break;
	}
}

void Scene::OnProcessingKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(m_pPlayer)
		m_pPlayer->OnProcessingKeyboardMessage(hWnd, message, wParam, lParam);
	// 키보드 입력처리
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{

		default:
			break;
		}
		break;
	default:
		break;
	}

}

void Scene::UpdateChangeLoading(float elapsed)
{
	m_fChangeCount += 1000 * elapsed;
	if (m_fChangeCount >= 1000.f)
	{
		m_fChangeCount = 10;
		m_bStart = true;
	}
}

void Scene::DrawChangeLoading(HDC& memDc)
{
	HBRUSH hBrush, oldBrush;
	int iChangeCount = (int)m_fChangeCount;
	DrawGameLoading(memDc);
	//hBrush = CreateSolidBrush(RGB(0, 0, 0));
	//oldBrush = (HBRUSH)SelectObject(memDc, hBrush);
	//Rectangle(memDc, 0, 0, WINWIDTH, iChangeCount * 9 / 16);
	//Rectangle(memDc, 0, 0, iChangeCount, WINHEIGHT);
	//Rectangle(memDc, WINWIDTH - (iChangeCount), 0, WINWIDTH, WINHEIGHT);
	//Rectangle(memDc, 0, WINHEIGHT - iChangeCount / 2, WINWIDTH, WINHEIGHT);
	//SelectObject(memDc, oldBrush); DeleteObject(hBrush);

	//m_cClosing.Draw(memDc, -200 + iChangeCount, -550 + iChangeCount, 2000 - iChangeCount * 2, 2000 - iChangeCount * 2,
	//	0, 0, m_cClosing.GetWidth(), m_cClosing.GetHeight());
}

void Scene::DrawGameLoading(HDC& memDc)
{
	m_cLoadBit.Draw(memDc, 0, 0, WINWIDTH, WINHEIGHT,
		0, 0, m_cLoadBit.GetWidth(), m_cLoadBit.GetHeight());
	m_cStartBit.Draw(memDc, 500, 550, 600, 100,
		0, 0, m_cStartBit.GetWidth(), m_cStartBit.GetHeight());
	m_cQuitBit.Draw(memDc, 500, 700, 600, 100,
		0, 0, m_cQuitBit.GetWidth(), m_cQuitBit.GetHeight());
}

void Scene::DrawGameStart(HDC& memdc)
{
	HBRUSH hBrush, oldBrush;

	//마우스에 의해 커질 카드
	int selectCard = -1;

	//배경 그리기
	m_cBackGround.Draw(memdc, 0, 0, WINWIDTH, WINHEIGHT,
		0, 0, m_cBackGround.GetWidth(), m_cBackGround.GetHeight());

	m_pCastle->Draw(memdc);

	// 플레이어 화살표 UI
	int x, y;
	x = (int)m_pPlayer->GetLocation().x;
	y = (int)m_pPlayer->GetLocation().y;
	m_cArrowImg.Draw(memdc, RECT{ x, y - 50, x + 100, y });
	
}

void Scene::UpdateGameStart(float elapsed)
{
	//TODO 플레이어에서 처리
	{
		//카드를 다쓰면 덱 초기화
		//if (cardCount == deadCardCount) {
		//	resetCard();
		//	m_bCardDrawing = true;
		//	wait = 0;
		//}

		//if (m_bCardDrawing) {
		//	if (cardCount < 10) {
		//		startShop(hDC, memdc);
		//	}
		//	else {
		//		//시작용 4장 뽑기
		//		for (int i = 0; i < 4; i++) {
		//			drawCard();
		//		}
		//		m_bCardDrawing = false;
		//		m_bStart = clock();

		//		//4장의 자리배치
		//		setCardPoint();
		//	}
		//}
	}
}

void Scene::DrawChangeStart(HDC& memdc) {
	HBRUSH hBrush, oldBrush;
	int iChangeCount = (int)m_fChangeCount;

	m_cBackGround.Draw(memdc, 0, 0, WINWIDTH, WINHEIGHT,
		0, 0, m_cBackGround.GetWidth(), m_cBackGround.GetHeight());
	m_pCastle->DrawCastle(memdc);

	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, 0, 0, WINWIDTH, 450 - iChangeCount);
	Rectangle(memdc, 0, 0, 800 - iChangeCount, WINHEIGHT);
	Rectangle(memdc, iChangeCount * 2 + (800 - iChangeCount), 0, WINWIDTH, WINHEIGHT);
	Rectangle(memdc, 0, iChangeCount * 2 + 450 - iChangeCount, WINWIDTH, WINHEIGHT);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);

	m_cClosing.Draw(memdc, 800 - iChangeCount, 450 - iChangeCount, iChangeCount * 2, iChangeCount * 2,
		0, 0, m_cClosing.GetWidth(), m_cClosing.GetHeight());
}

void Scene::UpdateChangeStart(float elapsed)
{
	m_fChangeCount += 500 * elapsed;
	if (m_fChangeCount >= 1400)
	{
		m_fChangeCount = 0;
		m_bChanging = false;
		m_pPlayer = new Player;
		m_pPlayer2 = new Player;
		m_lObjectList.push_back(m_pPlayer);
		m_lObjectList.push_back(m_pPlayer2);

	}
}

DWORD WINAPI Scene::ReceiveThread(LPVOID arg)
{
	int retval;
	char* SERVERIP = (char*)"1.242.205.234";


	// 소켓 생성
	m_pSock = new SOCKET;
	*m_pSock = socket(AF_INET, SOCK_STREAM, 0);
	//if (sock == INVALID_SOCKET) err_quit("socket()");

	// 스트림 생성
	m_ReadStream = new MemoryReadStream(*m_pSock);
	m_WriteStream = new MemoryWriteStream(*m_pSock);

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(*m_pSock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	//if (retval == SOCKET_ERROR) err_quit("connect()");

	StateMsgType typeBuf;	
	retval = recv(*m_pSock, (char*)&typeBuf, sizeof(BYTE), MSG_WAITALL);
	retval = recv(*m_pSock, (char*)&m_iClientNum, sizeof(int), MSG_WAITALL);

	StateMsgType smt = StateMsgType::PlayerLocation;
	PlayerLocationMsg temp;
	temp.Location = POINT{ 0,0 };
	temp.PlayerId = -1;
	temp.State = PStateName::Move;
	temp.Direction = 0;
	m_WriteStream->Write(smt);
	m_WriteStream->Write(temp);
	m_WriteStream->Send();

	//StateMsgType smt = StateMsgType::PlayerLocation;
	//send(*m_pSock, (char*)&smt, sizeof(StateMsgType), 0);

	//PlayerLocationMsg temp;
	//temp.Location = POINT{ 0,0 };
	//temp.PlayerId = -1;
	//temp.State = PStateName::Move;
	//temp.Direction = 0;
	//send(*m_pSock, (char*)&temp, sizeof(PlayerLocationMsg), 0);

	m_pStateMsgArgu = NULL;
	while (1) {
		WaitForSingleObject(*m_pWriteEvent, INFINITE);   // 쓰기 완료 대기


		//for (int i = 0; i < 2; ++i) {
			if (m_pStateMsgArgu != NULL)
				delete m_pStateMsgArgu;
			BYTE StateMsg;
			BYTE upper2Bits = 0;
			BYTE lower6Bits = 0;

			bool IsOver = false;
			m_ReadStream->Read(m_StateMsgQueue, IsOver);

			//retval = recv(*m_pSock, (char*)&StateMsg, sizeof(BYTE), MSG_WAITALL);
			//if (retval == SOCKET_ERROR) {
			//	PostQuitMessage(0);
			//}

			//// 상위 2비트 추출
			//upper2Bits = StateMsg >> 6;

			//// 하위 6비트 추출
			//lower6Bits = StateMsg & 0x3F;

			//// 추가로 읽을 바이트 사이즈
			//switch (lower6Bits)
			//{
			//case (int)StateMsgType::MonsterSpawn:	m_iMsgSize = sizeof(MonsterSpawnStateMsg); break;
			//case (int)StateMsgType::MonsterHp:		m_iMsgSize = sizeof(MonsterHpStateMsg); break;
			//case  (int)StateMsgType::PlayerLocation:m_iMsgSize = sizeof(PlayerLocationMsg); break;
			//case (int)StateMsgType::UseCard:		m_iMsgSize = sizeof(UseCardStateMsg);	break;
			//case  (int)StateMsgType::CastleHp:		m_iMsgSize = sizeof(CastleHpStateMsg);	break;
			//default:
			//	break;
			//}


			//switch (lower6Bits)
			//{
			//case	(int)StateMsgType::MonsterSpawn:	m_pStateMsgArgu = new MonsterSpawnStateMsg; break;
			//case	(int)StateMsgType::MonsterHp:		m_pStateMsgArgu = new MonsterHpStateMsg;	break;
			//case	(int)StateMsgType::PlayerLocation:	m_pStateMsgArgu = new PlayerLocationMsg;	break;
			//case	(int)StateMsgType::UseCard:			m_pStateMsgArgu = new UseCardStateMsg;		break;
			//case	(int)StateMsgType::CastleHp:		m_pStateMsgArgu = new CastleHpStateMsg;		break;
			//default:
			//	break;
			//}

			//retval = recv(*m_pSock, (char*)m_pStateMsgArgu, m_iMsgSize, MSG_WAITALL);
			//if (retval == SOCKET_ERROR) {
			//	PostQuitMessage(0);
			//}

			//PlayerLocationMsg* temp = (PlayerLocationMsg*)m_pStateMsgArgu;
			//if (temp->PlayerId != m_iClientNum)
			//{
			//	break;
			//}
		//}
		SetEvent(*m_pReadEvent);
	}

	return 0;
}




