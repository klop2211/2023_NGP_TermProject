#include "stdafx.h"
#include "PlayerOwnedStates.h"
#include "Scene.h"
#include "Castle.h"

Scene::Scene()
{
	m_pPlayer = new Player;
	m_lObjectList.push_back(m_pPlayer);

	m_pCastle = new Castle;

	m_fChangeCount = 0;
	m_cClosing.Load(TEXT("���� ���� �̹���\\��.png"));
	m_cBackGround.Load(TEXT("���� ���� �̹���\\��漺X.png"));

	m_bStart = false, m_bChanging = false; 				//���� ���ۿ�
	//m_bStart = true, changing = false;				//ȭ��ٲ�°� �����Ƽ� �����
	m_bCardDrawing = true, m_bIsClick = false;
}

Scene::~Scene()
{
	m_cClosing.Destroy();
	m_cBackGround.Destroy();
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
	m_fChangeCount += 500 * elapsed;
	if (m_fChangeCount >= 1000.f)
	{
		m_fChangeCount = 0;
		m_bStart = true;
	}
}

void Scene::DrawChangeLoading(HDC& memDc)
{
	int iChangeCount = (int)m_fChangeCount;

	m_cClosing.Draw(memDc, -200 + iChangeCount, -550 + iChangeCount, 2000 - iChangeCount * 2, 2000 - iChangeCount * 2,
		0, 0, m_cClosing.GetWidth(), m_cClosing.GetHeight());
}

void Scene::DrawGameLoading(HDC& memDc)
{
	CImage LoadBit, startBit, quitBit;
	LoadBit.Load(TEXT("���� ���� �̹���\\������Ʈ��.png"));
	startBit.Load(TEXT("���� ���� �̹���\\Start.png"));
	quitBit.Load(TEXT("���� ���� �̹���\\Quit.png"));

	LoadBit.Draw(memDc, 0, 0, WINWIDTH, WINHEIGHT,
		0, 0, LoadBit.GetWidth(), LoadBit.GetHeight());
	startBit.Draw(memDc, 500, 550, 600, 100,
		0, 0, startBit.GetWidth(), startBit.GetHeight());
	quitBit.Draw(memDc, 500, 700, 600, 100,
		0, 0, quitBit.GetWidth(), quitBit.GetHeight());
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

	//TODO: �÷��̾�� ������, ī�� ���
	{
		//������ ���â
		//ultiImg.Draw(memdc, WINWIDTH - 150, 10, 100, 100,
		//	0, 0, 77, 77);
		//hBrush = CreateSolidBrush(RGB(255, 215, 0));
		//oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
		//Rectangle(memdc, WINWIDTH - 150, 100, WINWIDTH - 150 + ((double)ultimate / ULTIMATESKILL) * 100, 110);
		//SelectObject(memdc, oldBrush); DeleteObject(hBrush);

		//���ʾƷ� ī�� ��
		//Deck.Draw(memdc, -44, 750, 204, 300,
		//	0, 0, Deck.GetWidth(), Deck.GetHeight());

		////���� ī�� ���� ��
		//Ellipse(memdc, deckText);
		//swprintf_s(numStr, L"%d", cardCount - (handCardCount + deadCardCount));
		//DrawText(memdc, numStr, lstrlen(numStr), &deckText, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		////����ġ�� ���
		//hBrush = CreateSolidBrush(RGB(0, 255, 255));
		//oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
		//Rectangle(memdc, 170, WINHEIGHT - ((double)experience / experienceBar[level]) * 100, 190, WINHEIGHT);
		//SelectObject(memdc, oldBrush); DeleteObject(hBrush);

		////�������
		//swprintf_s(numStr, L"%d", level + 1);
		//Rectangle(memdc, 150, WINHEIGHT - 20, 210, WINHEIGHT);
		//DrawText(memdc, numStr, lstrlen(numStr), &levelRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		////�� ����
		//for (int i = 0; i < maxMana; i++)
		//{
		//	manaImg[1].Draw(memdc, 1600 - 55 * ((i % 5) + 1), 900 - 55 * ((i / 5) + 1), 50, 50, 0, 0, manaImg[1].GetWidth(), manaImg[1].GetHeight());
		//}
		////�� ����
		//for (int i = 0; i < manaCount; i++)
		//{
		//	manaImg[0].Draw(memdc, 1600 - 55 * ((i % 5) + 1), 900 - 55 * ((i / 5) + 1), 50, 50, 0, 0, manaImg[0].GetWidth(), manaImg[0].GetHeight());
		//}
	}
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

	m_cClosing.Load(TEXT("��.png"));

	m_cBackGround.Draw(memdc, 0, 0, WINWIDTH, WINHEIGHT,
		0, 0, m_cBackGround.GetWidth(), m_cBackGround.GetHeight());
	m_cBackGround.Draw(memdc, 0, 0, 259, 635,
		0, 0, m_cBackGround.GetWidth(), m_cBackGround.GetHeight());

	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, 0, 0, WINWIDTH, 450 - m_fChangeCount);
	Rectangle(memdc, 0, 0, 800 - m_fChangeCount, WINHEIGHT);
	Rectangle(memdc, m_fChangeCount * 2 + (800 - m_fChangeCount), 0, WINWIDTH, WINHEIGHT);
	Rectangle(memdc, 0, m_fChangeCount * 2 + 450 - m_fChangeCount, WINWIDTH, WINHEIGHT);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);

	m_cClosing.Draw(memdc, 800 - m_fChangeCount, 450 - m_fChangeCount, m_fChangeCount * 2, m_fChangeCount * 2,
		0, 0, m_cClosing.GetWidth(), m_cClosing.GetHeight());
}

void Scene::UpdateChangeStart(float elapsed)
{
	m_fChangeCount += 500 * elapsed;
	if (m_fChangeCount >= 1400)
	{
		m_fChangeCount = 0;
		m_bChanging = false;
	}
}
