#include "stdafx.h"
#include "PlayerOwnedStates.h"
#include "Scene.h"
#include "Castle.h"
#include "../Server/StateMessage.h"

#include "../MemStream/MemoryReadStream.h"
#include "../MemStream/MemoryWriteStream.h"

#include "Bat.h"
#include "Wolf.h"
#include "Papyrus.h"
#include "Bone.h"

#include "Shop.h"

//#define MULTI_PLAY

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

	m_Shop = nullptr;


	m_fChangeCount = 0;
	m_cClosing.Load(TEXT("���� ���� �̹���\\��.png"));
	m_cBackGround.Load(TEXT("���� ���� �̹���\\��漺X.png"));
	m_cLoadBit.Load(TEXT("���� ���� �̹���\\������Ʈ��.png"));
	m_cStartBit.Load(TEXT("���� ���� �̹���\\Start.png"));
	m_cQuitBit.Load(TEXT("���� ���� �̹���\\Quit.png"));
	m_cArrowImg.Load(L"./���� ���� �̹���/ȭ��ǥ.png");

	m_bStart = false, m_bChanging = false; 				//���� ���ۿ�
	//m_bStart = true, changing = false;				//ȭ��ٲ�°� �����Ƽ� �����
	m_bCardDrawing = true, m_bIsClick = false;

	m_Papyrus = nullptr;
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

#ifdef MULTI_PLAY
		WaitForSingleObject(*m_pReadEvent, INFINITE); 

		// �������� ���� �޽��� ó��
		while (!m_StateMsgQueue.empty())
		{
			StateMsgInfo SMI = m_StateMsgQueue.front();
			m_StateMsgQueue.pop();

			switch (SMI.StateMsg) {
			case StateMsgType::MonsterLocation:
			{
				MonsterLocationMsg* temp = (MonsterLocationMsg*)SMI.pStateMsgArgu;
				UpdateMonsterLocation(temp->Type, temp->SerialId, temp->Location);
			}
				break;
			case StateMsgType::MonsterHp:
			{
				MonsterHpMsg* temp = (MonsterHpMsg*)SMI.pStateMsgArgu;
				UpdateMonsterHp(temp->Type, temp->SerialId, temp->Hp);
			}
				break;
			case StateMsgType::MonsterState:
			{
				MonsterStateMsg* temp = (MonsterStateMsg*)SMI.pStateMsgArgu;
				UpdateMonsterState(temp->Type, temp->SerialId, temp->State);
			}
				break;
			case StateMsgType::PlayerLocation:
			{
				PlayerLocationMsg* temp = (PlayerLocationMsg*)SMI.pStateMsgArgu;
				if (temp->PlayerId != m_iClientNum && m_pPlayer2 != NULL) {
					m_pPlayer2->SetLocation(temp->Location);
					m_pPlayer2->SetDir((Direction)temp->Direction);
					if (m_pPlayer2->GetStateName() != temp->State)
						m_pPlayer2->ChangeState(temp->State);
				}
			}
				break;
			case StateMsgType::CastleHp:
			{
				CastleHpStateMsg* temp = (CastleHpStateMsg*)SMI.pStateMsgArgu;
				UpdateCastleHp(temp->Hp);
			}
				break;
			case StateMsgType::UseCard:
			{
				UseCardStateMsg* temp = (UseCardStateMsg*)SMI.pStateMsgArgu;
				if (temp->PlayerId != m_iClientNum && m_pPlayer2 != NULL) {
					m_pPlayer2->SetCurrentCardName((CardName)temp->Card);
				}

			}
				break; 
			case StateMsgType::BossState:
			{
				BossStateMsg* temp = (BossStateMsg*)SMI.pStateMsgArgu;
				UpdateBossState(temp->Pattern);
			}
				break;
			case StateMsgType::MonsterKill:
			{
				MonsterKillMsg* temp = (MonsterKillMsg*)SMI.pStateMsgArgu;
				UpdateMonsterKill(temp->PlayerId, temp->type);
			}
			break;
			default:
				break;
			}

		}

		// �� ��Ȳ�� �������� ����
		// �÷��̾��� �⺻����
		StateMsgType smt = StateMsgType::PlayerLocation;
		PlayerLocationMsg sma;
		if (m_pPlayer != NULL) {
			sma.Location.x = (int)m_pPlayer->GetLocation().x;
			sma.Location.y = (int)m_pPlayer->GetLocation().y;
			sma.PlayerId = m_iClientNum;
			sma.Direction = m_pPlayer->GetDir();
			sma.State = m_pPlayer->GetStateName();
			// ��ų�� ����ߴ°�?
			// �÷��̾��� �ΰ����� Write
			if (m_pPlayer->IsSkillMsg()) {
				m_pPlayer->SetSkillCheck(false);
				smt = StateMsgType::UseCard;
				UseCardStateMsg* usm = m_pPlayer->CreateUseCardStateMsg(m_iClientNum);
				m_WriteStream->Write(smt);
				m_WriteStream->Write(*usm);
				delete usm;
			}
			// �÷��̾��� ��ų ������Ʈ ��	��
			{
				m_pPlayer->CreateSOLMsg(m_iClientNum, m_WriteStream);
			}
		}
		else {
			sma.Location.x = 100;
			sma.Location.y = 200;
			sma.PlayerId = -1;
			sma.Direction = 0;
			sma.State = PStateName::Move;
		}
		smt = StateMsgType::PlayerLocation;
		m_WriteStream->Write(smt);
		m_WriteStream->Write(sma);






		m_WriteStream->Send();
		SetEvent(*m_pWriteEvent);

#endif // STAND_ALONE

	}
	else {
		if (m_bChanging)
			UpdateChangeLoading(elapsed);	// ���� ������ ���� ���̵�ƿ�
	}



	for (auto object : m_lObjectList) {
		object->Update(elapsed);
	}
	for (const auto& w : m_WolfMap)
	{
		w.second->Update(elapsed);
	}
	for (const auto& b : m_BatMap)
	{
		b.second->Update(elapsed);
	}
	if (m_Papyrus)
	{
		m_Papyrus->Update(elapsed);
		for (const auto& b : m_BoneMap)
		{
			b.second->Update(elapsed);
		}
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

			if (m_pPlayer && m_pPlayer->GetCardCount() < 10)
			{
				m_Shop->StartShop(memDc);
			}
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

	m_pPlayer->UiDraw(memDc);

	for (const auto& w : m_WolfMap)
	{
		w.second->Draw(memDc);
	}
	for (const auto& b : m_BatMap)
	{
		b.second->Draw(memDc);
	}
	if (m_Papyrus)
	{
		m_Papyrus->Draw(memDc);
		for (const auto& b : m_BoneMap)
		{
			b.second->Draw(memDc);
		}
	}
}

void Scene::OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pPlayer)
	{
		m_pPlayer->OnProcessingMouseMessage(hWnd, message, wParam, lParam);
	}
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
#ifdef MULTI_PLAY
					m_pReadEvent = new HANDLE;
					m_pWriteEvent = new HANDLE;
					*m_pReadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
					*m_pWriteEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
					CreateThread(NULL, 0, ReceiveThread, NULL, 0, NULL);

#endif // DEBUG


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
		case 'p':
		case 'P':
			m_pPlayer->DrawCard();
			m_pPlayer->SetCardPoint();
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

void Scene::OnProcessingCommandMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
		{
			m_Shop->OnProcessingCommandMessage(hWnd, wParam, m_pPlayer);
		}
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

	// �÷��̾� ȭ��ǥ UI
	int x, y;
	x = (int)m_pPlayer->GetLocation().x;
	y = (int)m_pPlayer->GetLocation().y;
	m_cArrowImg.Draw(memdc, RECT{ x, y - 50, x + 100, y });
	
}

void Scene::UpdateGameStart(float elapsed)
{
	m_pCastle->Update(elapsed);
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
		m_pPlayer2 = new Player;
		m_lObjectList.push_back(m_pPlayer);
		m_lObjectList.push_back(m_pPlayer2);

	}
}

//===================Msg �о�� ���� �����ϴ� �ڵ��===========================
void Scene::UpdateMonsterLocation(MonsterType MT, int SN, POINT Location)
{
	switch (MT)
	{
	case MonsterType::Wolf:
	{
		if (m_WolfMap.find(SN) != m_WolfMap.end())
		{
			m_WolfMap[SN]->SetLocation(Location);
		}
		else
		{
			Wolf* wolf = new Wolf();
			m_WolfMap.insert({ SN, wolf });
		}
	}
		break;
	case MonsterType::Bat:
	{
		if (m_BatMap.find(SN) != m_BatMap.end())
		{
			m_BatMap[SN]->SetLocation(Location);
		}
		else
		{
			Bat* bat = new Bat();
			m_BatMap.insert({ SN, bat });
		}
	}
		break;
	case MonsterType::Papyrus:
	{
		if (m_Papyrus)
		{
			m_Papyrus->SetLocation(Location);
		}
		else
		{
			m_Papyrus = new Papyrus();
		}
	}
		break;
	case MonsterType::UBBone:
	case MonsterType::BBone1:
	case MonsterType::BBone2:
	{
		if (m_BoneMap.find(SN) != m_BoneMap.end())
		{
			if (Location.x == -1 && Location.y == -1)
			{
				delete m_BoneMap[SN];
				m_BoneMap.erase(SN);
			}
			else
			{
				m_BoneMap[SN]->SetLocation(Location);
			}
		}
		else
		{
			if (Location.x != -1 || Location.y != -1)
			{
				Bone* bone = new Bone(MT, Location.x, Location.y);
				m_BoneMap.insert({ SN, bone });
			}
		}
	}
	break;
	default:
		break;
	}
}

void Scene::UpdateMonsterHp(MonsterType MT, int SN, int Hp)
{
	switch (MT)
	{
	case MonsterType::Wolf:
	{
		m_WolfMap[SN]->SetCurrentHp(Hp);
		if (m_WolfMap[SN]->GetCurrentHp() <= 0)
		{
			delete m_WolfMap[SN];
			m_WolfMap.erase(SN);
		}
	}
	break;
	case MonsterType::Bat:
	{
		m_BatMap[SN]->SetCurrentHp(Hp);
		if (m_BatMap[SN]->GetCurrentHp() <= 0)
		{
			delete m_BatMap[SN];
			m_BatMap.erase(SN);
		}
	}
	break;
	case MonsterType::Papyrus:
	{
		m_Papyrus->SetCurrentHp(Hp);
	}
	break;
	default:
		break;
	}
}

void Scene::UpdateMonsterState(MonsterType MT, int SN, MonsterStateType SMT)
{
	MonsterState ms = MonsterState::Move;
	switch (SMT)
	{
	case MonsterStateType::Move:
		ms = MonsterState::Move;
		break;
	case MonsterStateType::Attack:
		ms = MonsterState::Attack;
		break;
	case MonsterStateType::Ice:
		break;
	case MonsterStateType::Fire:
		break;
	default:
		break;
	}

	switch (MT)
	{
	case MonsterType::Wolf:
	{
		m_WolfMap[SN]->SetStatus(ms);
	}
	break;
	case MonsterType::Bat:
	{
		m_BatMap[SN]->SetStatus(ms);
	}
	break;
	default:
		break;
	}
}

void Scene::UpdateCastleHp(int Hp)
{
	m_pCastle->SetCurrentHp(Hp);
}

void Scene::UpdateBossState(BossStateType BST)
{
	m_Papyrus->SetStatus(BST);
}

void Scene::UpdateMonsterKill(int Id, MonsterType MT)
{
	if (Id == m_iClientNum)
	{
		switch (MT)
		{
		case MonsterType::Wolf:
		{
			Wolf w;
			m_pPlayer->AddMoney(w.GetMoney());
			m_pPlayer->AddExp(w.GetExperi());
		}
			break;
		case MonsterType::Bat:
		{
			Bat b;
			m_pPlayer->AddMoney(b.GetMoney());
			m_pPlayer->AddExp(b.GetExperi());
		}
			break;
		default:
			break;
		}
	}
}

void Scene::SetWndAndInstance(HWND hWnd, HINSTANCE& Inst)
{
	m_Shop = new Shop(hWnd, Inst);
	m_Shop->SetRandValue();
}


//=========================================================
DWORD WINAPI Scene::ReceiveThread(LPVOID arg)
{
	int retval;
	char* SERVERIP = (char*)"127.0.0.1";


	// ���� ����
	m_pSock = new SOCKET;
	*m_pSock = socket(AF_INET, SOCK_STREAM, 0);
	//if (sock == INVALID_SOCKET) err_quit("socket()");

	// ��Ʈ�� ����
	m_ReadStream = new MemoryReadStream();
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


	m_pStateMsgArgu = NULL;
	while (1) {
		WaitForSingleObject(*m_pWriteEvent, INFINITE);   // ���� �Ϸ� ���

		if (m_pStateMsgArgu != NULL)
			delete m_pStateMsgArgu;

		BYTE StateMsg;
		BYTE upper2Bits = 0;
		BYTE lower6Bits = 0;

		bool IsOver = false;

		m_ReadStream->Read(*m_pSock, m_StateMsgQueue, IsOver);

		SetEvent(*m_pReadEvent);
	}

	return 0;
}




