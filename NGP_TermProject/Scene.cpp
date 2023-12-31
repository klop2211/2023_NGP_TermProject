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

	m_Shop = nullptr;


	m_fChangeCount = 0;
	m_fEndTime = 0.f;

	m_cClosing.Load(TEXT("윈플 텀프 이미지\\원.png"));
	m_cBackGround.Load(TEXT("윈플 텀프 이미지\\배경성X.png"));
	m_cLoadBit.Load(TEXT("윈플 텀프 이미지\\레온하트성.png"));
	m_cStartBit.Load(TEXT("윈플 텀프 이미지\\Start.png"));
	m_cQuitBit.Load(TEXT("윈플 텀프 이미지\\Quit.png"));
	m_cArrowImg.Load(L"./윈플 텀프 이미지/화살표.png");

	m_bGameEnd = false;
	m_bStart = false, m_bChanging = false; 				//원래 시작용
	//m_bStart = true, changing = false;				//화면바뀌는거 귀찮아서 만든거
	m_bCardDrawing = true, m_bIsClick = false;

	m_Papyrus = nullptr;

	m_pGameoverMsg = nullptr;
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
	delete m_pGameoverMsg;
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
			if (m_bGameEnd) {
				m_fEndTime += elapsed;
			}
			else {
				UpdateGameStart(elapsed);		//메인 게임화면
			}
			

			//TODO: 게임종료
		}

#ifdef MULTI_PLAY
		WaitForSingleObject(*m_pReadEvent, INFINITE); 

		// 서버에서 받은 메시지 처리
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
					if (m_pPlayer2->GetStateName() != temp->State && m_pPlayer2->GetStateName() != PStateName::Skill) {
						if(m_pPlayer2->GetStateTime() > 0.05f)
							m_pPlayer2->ChangeState(temp->State);
					}
				}
				if (temp->PlayerId == m_iClientNum && temp->State == PStateName::Stun) {
					if (m_pPlayer->GetStateName() != temp->State)
						if (m_pPlayer->GetStateTime() > 0.05f)
							m_pPlayer->ChangeState(temp->State);
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
				UpdateMonsterKill(temp->PlayerId, temp->SerialId, temp->type);
			}
				break;
			case StateMsgType::GameOver:
			{
				GameOverMsg* temp = (GameOverMsg*)SMI.pStateMsgArgu;
				m_bGameEnd = true;
				m_pGameoverMsg = new GameOverMsg;
				*m_pGameoverMsg = *temp;
			}
				break;
			case StateMsgType::BossHp:
			{
				BossHpMsg* temp = (BossHpMsg*)SMI.pStateMsgArgu;
				UpdateBossHp(temp->Hp, temp->BreakCount, temp->KnockDown);
			}
			break;
			default:

				break;
			}

		}

		// 현 상황을 서버에게 전달
		// 플레이어의 기본정보
		StateMsgType smt = StateMsgType::PlayerLocation;
		PlayerLocationMsg sma;
		if (m_pPlayer != NULL) {
			sma.Location.x = (int)m_pPlayer->GetLocation().x;
			sma.Location.y = (int)m_pPlayer->GetLocation().y;
			sma.PlayerId = m_iClientNum;
			sma.Direction = m_pPlayer->GetDir();
			sma.State = m_pPlayer->GetStateName();
			// 스킬을 사용했는가?
			// 플레이어의 부가정보 Write
			if (m_pPlayer->IsSkillMsg()) {
				m_pPlayer->SetSkillCheck(false);
				smt = StateMsgType::UseCard;
				UseCardStateMsg* usm = m_pPlayer->CreateUseCardStateMsg(m_iClientNum);
				m_WriteStream->Write(smt);
				m_WriteStream->Write(*usm);
				delete usm;
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

		// 플레이어의 스킬 오브젝트 정	보
		if(m_pPlayer != NULL)
			m_pPlayer->CreateSOLMsg(m_iClientNum, m_WriteStream);

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

	if (m_pPlayer != NULL)
	{
		m_pPlayer->UiDraw(memDc);
		if (m_pPlayer->GetLevelUp())
		{
			m_Shop->StartShop(memDc);
		}
	}

	if (m_pPlayer && m_pPlayer->GetCardCount() < 10)
	{
		m_Shop->StartShop(memDc);
	}

	if (m_bGameEnd)
		DrawEnding(memDc, *m_pGameoverMsg);

}

void Scene::OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pPlayer)
	{
		m_pPlayer->OnProcessingMouseMessage(hWnd, message, wParam, lParam);
	}
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
	m_pCastle->Update(elapsed);

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

	// GarbageCollector
	for (auto it = m_WolfMap.begin(); it != m_WolfMap.end();)
	{
		if (it->second->GetCanDie())
		{
			it = m_WolfMap.erase(it);
		}
		else {
			++it;
		}
	}
	for (auto it = m_BatMap.begin(); it != m_BatMap.end();)
	{
		if (it->second->GetCanDie())
		{
			it = m_BatMap.erase(it);
		}
		else {
			++it;
		}
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


void Scene::DrawEnding(HDC& memDc, GameOverMsg gom)
{
	RECT BGRect{ 200, 50, 1400, 850 };
	CImage BGImg;
	BGImg.Load(L"./윈플 텀프 이미지/엔딩 백그라운드.png");
	BGImg.Draw(memDc, BGRect);

	RECT logoRect = { 600, 100, 1000, 300 };
	CImage logoImg;
	if (gom.GameOverFlag == 1)
		logoImg.Load(L"./윈플 텀프 이미지/승리 이미지.png");
	else
		logoImg.Load(L"./윈플 텀프 이미지/패배 이미지.png");
	
	logoImg.Draw(memDc, logoRect);

	POINT P1Position = { 400, 300 }, P2Position = { 1000, 300 };
	CImage NumImg[10], PImg;

	NumImg[0].Load(L"./윈플 텀프 이미지/0 이미지.png");
	NumImg[1].Load(L"./윈플 텀프 이미지/1 이미지.png");
	NumImg[2].Load(L"./윈플 텀프 이미지/2 이미지.png");
	NumImg[3].Load(L"./윈플 텀프 이미지/3 이미지.png");
	NumImg[4].Load(L"./윈플 텀프 이미지/4 이미지.png");
	NumImg[5].Load(L"./윈플 텀프 이미지/5 이미지.png");
	NumImg[6].Load(L"./윈플 텀프 이미지/6 이미지.png");
	NumImg[7].Load(L"./윈플 텀프 이미지/7 이미지.png");
	NumImg[8].Load(L"./윈플 텀프 이미지/8 이미지.png");
	NumImg[9].Load(L"./윈플 텀프 이미지/9 이미지.png");

	PImg.Load(L"./윈플 텀프 이미지/P 이미지.png");

	NumImg[1].Draw(memDc, P1Position.x, P1Position.y, 100, 100);
	PImg.Draw(memDc, P1Position.x + 100, P1Position.y, 100, 100);
	NumImg[2].Draw(memDc, P2Position.x, P2Position.y, 100, 100);
	PImg.Draw(memDc, P2Position.x + 100, P2Position.y, 100, 100);

	POINT EnemyPosition{ 725, 400 };
	CImage EnemyImg;

	if (m_fEndTime > 1) {
		EnemyImg.Load(L"./적관련/늑대.png");
		EnemyImg.Draw(memDc, EnemyPosition.x, EnemyPosition.y, 150, 100, 0, 1, 84, 56);
		EnemyImg.Destroy();
	}

	if (m_fEndTime > 2) {
		EnemyImg.Load(L"./적관련/박쥐.png");
		EnemyImg.Draw(memDc, EnemyPosition.x, EnemyPosition.y + 100, 150, 100, 0, 1, 65, 47);
		EnemyImg.Destroy();
	}

	if (m_fEndTime > 3) {
		EnemyImg.Load(L"./적관련/파피루스.png");
		EnemyImg.Draw(memDc, EnemyPosition.x + 25, EnemyPosition.y + 200, 150, 100, 1, 1, 48, 53);
		EnemyImg.Destroy();
	}

	POINT ScoreMiddlePosition[2]{ { 450,400 },{ 1050, 400 } };
	if (gom.Clients[0].ClientNum == m_iClientNum) {
		// 0번이 1P, 1번이 2P
		// 점수는 최대 3자리(100의자리 수)
		int temp = m_fEndTime > 3 ? 3 : m_fEndTime;
		for (int i = 0; i < temp; ++i) {
			for (int j = 0; j < 2; ++j) {
				int num100, num10, num1;
				if (i == 0) {
					num100 = (int)gom.Clients[j].KillWolf / 100;
					num10 = (int)gom.Clients[j].KillWolf / 10 % 10;
					num1 = (int)gom.Clients[j].KillWolf % 10;
				}
				else if (i == 1) {
					num100 = (int)gom.Clients[j].KillBat / 100;
					num10 = (int)gom.Clients[j].KillBat / 10 % 10;
					num1 = (int)gom.Clients[j].KillBat % 10;
				}
				else {
					num100 = (int)gom.Clients[j].KillPapyrus / 100;
					num10 = (int)gom.Clients[j].KillPapyrus / 10 % 10;
					num1 = (int)gom.Clients[j].KillPapyrus % 10;
				}
				// 자리 수에 따라 위치 조정
				if (num100 != 0) {
					NumImg[num100].Draw(memDc, ScoreMiddlePosition[j].x - 100, ScoreMiddlePosition[j].y + i * 100, 100, 100);
					NumImg[num10].Draw(memDc, ScoreMiddlePosition[j].x, ScoreMiddlePosition[j].y + i * 100, 100, 100);
					NumImg[num1].Draw(memDc, ScoreMiddlePosition[j].x + 100, ScoreMiddlePosition[j].y + i * 100, 100, 100);
				}
				else {
					if (num10 != 0) {
						ScoreMiddlePosition[j].x -= 50;
						NumImg[num10].Draw(memDc, ScoreMiddlePosition[j].x, ScoreMiddlePosition[j].y + i * 100, 100, 100);
						NumImg[num1].Draw(memDc, ScoreMiddlePosition[j].x + 100, ScoreMiddlePosition[j].y + i * 100, 100, 100);
						ScoreMiddlePosition[j].x += 50;
					}
					else {
						NumImg[num1].Draw(memDc, ScoreMiddlePosition[j].x, ScoreMiddlePosition[j].y + i * 100, 100, 100);
					}
				}
			}
		}
	}
	else {
		// 0번이 2P, 1번이 1P
		int temp = m_fEndTime > 3 ? 3 : m_fEndTime;
		for (int i = 0; i < temp; ++i) {
			for (int j = 0; j < 2; ++j) {
				int num100, num10, num1;
				int k = j == 0 ? 1 : 0;
				if (i == 0) {
					num100 = (int)gom.Clients[k].KillWolf / 100;
					num10 = (int)gom.Clients[k].KillWolf / 10 % 10;
					num1 = (int)gom.Clients[k].KillWolf % 10;
				}
				else if (i == 1) {
					num100 = (int)gom.Clients[k].KillBat / 100;
					num10 = (int)gom.Clients[k].KillBat / 10 % 10;
					num1 = (int)gom.Clients[k].KillBat % 10;
				}
				else {
					num100 = (int)gom.Clients[k].KillPapyrus / 100;
					num10 = (int)gom.Clients[k].KillPapyrus / 10 % 10;
					num1 = (int)gom.Clients[k].KillPapyrus % 10;
				}
				// 자리 수에 따라 위치 조정
				if (num100 != 0) {
					NumImg[num100].Draw(memDc, ScoreMiddlePosition[j].x - 100, ScoreMiddlePosition[j].y + i * 100, 100, 100);
					NumImg[num10].Draw(memDc, ScoreMiddlePosition[j].x, ScoreMiddlePosition[j].y + i * 100, 100, 100);
					NumImg[num1].Draw(memDc, ScoreMiddlePosition[j].x + 100, ScoreMiddlePosition[j].y + i * 100, 100, 100);
				}
				else {
					if (num10 != 0) {
						ScoreMiddlePosition[j].x -= 50;
						NumImg[num10].Draw(memDc, ScoreMiddlePosition[j].x, ScoreMiddlePosition[j].y + i * 100, 100, 100);
						NumImg[num1].Draw(memDc, ScoreMiddlePosition[j].x + 100, ScoreMiddlePosition[j].y + i * 100, 100, 100);
						ScoreMiddlePosition[j].x += 50;
					}
					else {
						NumImg[num1].Draw(memDc, ScoreMiddlePosition[j].x, ScoreMiddlePosition[j].y + i * 100, 100, 100);
					}
				}
			}
		}
	}


	BGImg.Destroy();
	logoImg.Destroy();
	PImg.Destroy();
	for (int i = 0; i < 10; ++i)
		NumImg[i].Destroy();
}

//===================Msg 읽어와 상태 적용하는 코드들===========================
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
		//if (m_WolfMap[SN]->GetCurrentHp() <= 0)
		//{
		//	delete m_WolfMap[SN];
		//	m_WolfMap.erase(SN);
		//}
	}
	break;
	case MonsterType::Bat:
	{
		m_BatMap[SN]->SetCurrentHp(Hp);
		//if (m_BatMap[SN]->GetCurrentHp() <= 0)
		//{
		//	delete m_BatMap[SN];
		//	m_BatMap.erase(SN);
		//}
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

void Scene::UpdateBossHp(int Hp, int BreakCount, int KnockDown)
{
	m_Papyrus->SetCurrentHp(Hp);
	m_Papyrus->SetBreakCount(BreakCount);
	m_Papyrus->SetKnockDown(KnockDown);
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

void Scene::UpdateMonsterKill(int Id, int MonsterId, MonsterType MT)
{
	if (Id == m_iClientNum)
	{
		int PrevLevel = m_pPlayer->GetLevel();
		switch (MT)
		{
		case MonsterType::Wolf:
		{
			Wolf w;
			m_pPlayer->AddMoney(w.GetMoney());
			m_pPlayer->AddExp(w.GetExperi());

			m_WolfMap[MonsterId]->SetStatus(MonsterState::Dead);

			//delete m_WolfMap[MonsterId];
			//m_WolfMap.erase(MonsterId);
		}
			break;
		case MonsterType::Bat:
		{
			Bat b;
			m_pPlayer->AddMoney(b.GetMoney());
			m_pPlayer->AddExp(b.GetExperi());

			m_BatMap[MonsterId]->SetStatus(MonsterState::Dead);
			//delete m_BatMap[MonsterId];
			//m_BatMap.erase(MonsterId);
		}
			break;
		default:
			break;
		}
		if (PrevLevel != m_pPlayer->GetLevel())
		{
			m_pPlayer->SetLevelUp(true);
		}
	}
	else
	{
		switch (MT)
		{
		case MonsterType::Wolf:
			m_WolfMap[MonsterId]->SetStatus(MonsterState::Dead);
			break;
		case MonsterType::Bat:
			m_BatMap[MonsterId]->SetStatus(MonsterState::Dead);
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
	char* SERVERIP = (char*)"1.242.205.234";


	// 소켓 생성
	m_pSock = new SOCKET;
	*m_pSock = socket(AF_INET, SOCK_STREAM, 0);
	//if (sock == INVALID_SOCKET) err_quit("socket()");

	// 스트림 생성
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
		WaitForSingleObject(*m_pWriteEvent, INFINITE);   // 쓰기 완료 대기

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




