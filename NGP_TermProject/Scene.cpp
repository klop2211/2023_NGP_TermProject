#include "stdafx.h"
#include "Common.h"
#include "PlayerOwnedStates.h"
#include "Scene.h"
#include "Castle.h"
#include "../Server/StateMessage.h"

SOCKET* Scene::m_pSock;
HANDLE* Scene::m_pReadEvent;
HANDLE* Scene::m_pWriteEvent;

Scene::Scene()
{
	m_pPlayer = NULL;

	m_pCastle = new Castle;

	m_fChangeCount = 0;
	m_cClosing.Load(TEXT("���� ���� �̹���\\��.png"));
	m_cBackGround.Load(TEXT("���� ���� �̹���\\��漺X.png"));
	m_cLoadBit.Load(TEXT("���� ���� �̹���\\������Ʈ��.png"));
	m_cStartBit.Load(TEXT("���� ���� �̹���\\Start.png"));
	m_cQuitBit.Load(TEXT("���� ���� �̹���\\Quit.png"));

	m_bStart = false, m_bChanging = false; 				//���� ���ۿ�
	//m_bStart = true, changing = false;				//ȭ��ٲ�°� �����Ƽ� �����
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
	// �� ������ gameLoading -> changeLoading -> chageStart -> gameStart;
	if (m_bStart) {
		if (m_bChanging)
		{
			UpdateChangeStart(elapsed);		//���� ������ ���� ���̵���
		}
		else
		{
			UpdateGameStart(elapsed);		//���� ����ȭ��

			//TODO: ��������
		}
	}
	else {
		if (m_bChanging)
			UpdateChangeLoading(elapsed);	// ���� ������ ���� ���̵�ƿ�
	}

	for (auto object : m_lObjectList) {
		object->Update(elapsed);
	}
}

void Scene::Draw(HDC& memDc)
{
	// ��� ���⼭ �׷������
	// �� ������ gameLoading -> changeLoading -> chageStart -> gameStart;
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
	// ���콺 �Է�ó��
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
			// ����ȭ���� Ŭ�� ó��
			if (m_iMx >= 500 && m_iMx <= 1100)
			{
				// GameStart ��ư
				if (m_iMy >= 550 && m_iMy <= 650)
				{
					m_pReadEvent = new HANDLE;
					m_pWriteEvent = new HANDLE;
					*m_pReadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
					*m_pWriteEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
					CreateThread(NULL, 0, ReceiveThread, NULL, 0, NULL);
					m_bChanging = true;
				}
				// Quit ��ư
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

		// TODO: ī�带 ������ �� Ŀ�� ��ġ�� �� ī�� ��ġ�ϰ�
		//if (m_bIsClick && clickSelect != -1) {
		//	handCard[clickSelect]->point.x += (m_iMx - m_iStartX);
		//	handCard[clickSelect]->point.y += (m_iMy - m_iStartY);
		//	m_iStartX = m_iMx;
		//	m_iStartY = m_iMy;
		//}
		break;
	case WM_LBUTTONUP:
		if (m_bIsClick) {
			//TODO: �÷��̾ ī�� ���ó��
			
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
	// Ű���� �Է�ó��
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

	//���콺�� ���� Ŀ�� ī��
	int selectCard = -1;

	//��� �׸���
	m_cBackGround.Draw(memdc, 0, 0, WINWIDTH, WINHEIGHT,
		0, 0, m_cBackGround.GetWidth(), m_cBackGround.GetHeight());

	m_pCastle->Draw(memdc);
}

void Scene::UpdateGameStart(float elapsed)
{
	//TODO �÷��̾�� ó��
	{
		//ī�带 �پ��� �� �ʱ�ȭ
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
		//		//���ۿ� 4�� �̱�
		//		for (int i = 0; i < 4; i++) {
		//			drawCard();
		//		}
		//		m_bCardDrawing = false;
		//		m_bStart = clock();

		//		//4���� �ڸ���ġ
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
		m_lObjectList.push_back(m_pPlayer);
		
	}
}

DWORD WINAPI Scene::ReceiveThread(LPVOID arg)
{
	int retval;
	char* SERVERIP = (char*)"127.0.0.1";


	// ���� ����
	m_pSock = new SOCKET;
	*m_pSock = socket(AF_INET, SOCK_STREAM, 0);
	//if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(*m_pSock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	//if (retval == SOCKET_ERROR) err_quit("connect()");

	StateMsgType* typeBuf;
	typeBuf = new StateMsgType;

	while (1) {
		WaitForSingleObject(*m_pWriteEvent, INFINITE);   // ���� �Ϸ� ���

		retval = recv(*m_pSock, (char*)typeBuf, sizeof(StateMsgType), 0);

		SetEvent(*m_pReadEvent);
	}

	return 0;
}

