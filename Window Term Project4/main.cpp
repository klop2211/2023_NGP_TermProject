//�ܼ� ���
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

//TODO: ���� �����̻�, ���� ����, ��ο� ���

#include <windows.h>
#include <time.h>
#include <tchar.h>
#include <atlimage.h>

#define WINWIDTH 1600		//������ ����
#define WINHEIGHT 900		//������ ����

#define CARDWIDTH 307		//ī�� ���� ũ��
#define CARDHEIGHT 492		//ī�� ���� ũ��
#define CARDMINIWIDTH 187	//ī�� ���� ũ��
#define CARDMINIHEIGHT 300	//ī�� ���� ũ��
#define CARDVARIABLE 10		//ī�� ����

#define MAXHANDCARD 7		//�տ� �� �� �ִ� ī�� ��		
#define CARDDRAWTERM 300	//60�� 1��
#define CARDSPAWNRAND 25	//������ Ʈ����ȭ ī�尡 �ȳ��� Ȯ�� x%
#define MANAREGENERATION 30	//���� ���

#define MAXWOLF 25
#define MAXBAT 10

#define ULTIMATESKILL 200

#define GROUNDYPOINT 634
#define CASTLEXPOINT 235

#define IDC_BUTTON_BUY1 10001
#define IDC_BUTTON_BUY1 10001
#define IDC_BUTTON_BUY2 10002
#define IDC_BUTTON_BUY3 10003
#define IDC_BUTTON_BUY4 10004

enum CardName {N_rhlddufvk, N_sktjsckd, N_dbtjdrkdcjs, N_wjrfydvh, N_aodfyddufvk, N_qksdnjftja, N_dusghkstja, N_cjdfydwls, N_cjdfydcnftn, N_ghltjsckd, N_dmsgkdbtjdxks};
enum CardRect { R_main, R_tier1, R_tier2, R_tier3 };
enum TriIndex {I_Tier1, I_Tier2, I_Tier3, I_selected};


HINSTANCE g_hlnst;
LPCTSTR lpszClass = L"WIndow Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";

HDC hDC, memdc, backdc;
HBITMAP hBit1, hBackBit, oldBit1, oldBackBit;
CImage BackGround[2], Deck, manaImg[2], bossHpBar, ultiImg;
CImage batImg, wolfImg, papyrusImg;
HWND hWnd;
int mx, my, startX, startY, castleMovement;

//���� ī���� ���� ��ġ
POINT prevCardPoint = { -1,-1 };

//�� ���� ����, �ִ� ���� ����
int manaCount = 1, maxMana = 1;

//ī���� Ʈ�������� Ȯ��
int Tripord[CARDVARIABLE][4] = { 0, };

//������ ��� ī�� 3��
int randValue[3] = { -1, -1, -1 };

//������ ī�� ����
int cardPrice[3] = { -1, -1, -1 };

//���� Ʈ�� ��ȣ
int triNum[3] = { -1, -1, -1 };

//������ �����ߴ���, ȭ���� �ٲ�� ������, ī�� �̴�������
bool start, changing, cardDrawing;

//���콺 Ŭ�� ����
bool isClick;
int clickSelect = -1;

//ĳ���� ��, ����ġ, ����ġ��, ����, ������ ������, ��ü��
int money, experience, experienceBar[10], level, ultimate, castleHp;

void useCard();
void resetCard();
void gameStart();
void hitCastle(int damage);
void getExp(int experi);
void getMoney(int _money);
void plusUltimate();
void updateEnemy(int& wave);

#include "Random.h"
#include "_Object.h"
#include "Object.h"
#include "Player.h"
#include "Card.h"
#include "Shop.h"
#include "Start.h"
#include "Loading.h"

struct Node_Object // ��ų ������Ʈ�� ������ �ܹ��� ���Ḯ��Ʈ
{
	Object data;
	Node_Object* next = NULL;
};
bool key_a, key_d, play_on, onemore;
int PlayerSize = 100;
Node_Object* head;
void Insert_Object(Node_Object* head, const int& object_type, const int& dir);
void UpdatePlayer();
void setCardTripod(int cardEnum);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	// WinMain() �Լ� ó������
	// 1. ������ Ŭ���� �����
	MSG Message;
	WNDCLASSEX WndClass;											// ����ü ����
	g_hlnst = hInstance;

	// 2. ������ Ŭ���� ����ü�� �Ӽ��� �����ϰ� ����ϱ� (������ �Լ�, ������, Ŀ��, ����)
	WndClass.cbSize = sizeof(WndClass);								// �� ����ü�� ũ��
	WndClass.style = CS_HREDRAW | CS_VREDRAW;							// ��� ��Ÿ��	->	�۾��� ��/���̰� ����Ǹ� �����츦 �ٽ� �׸���
	WndClass.lpfnWndProc = (WNDPROC)WndProc;							// ���ν��� �Լ�
	WndClass.cbClsExtra = 0;											// Ŭ���� ���� �޸�  -- ������
	WndClass.cbWndExtra = 0;											// ������ ���� �޸�  -- ������
	WndClass.hInstance = hInstance;									// ������ �ν��Ͻ�
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);					// ������
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					// Ŀ��
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// ����
	WndClass.lpszMenuName = NULL;										// �޴��̸�
	WndClass.lpszClassName = lpszClass;								// Ŭ�����̸�
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);				// ���� ������
	RegisterClassEx(&WndClass);

	// 3. ������ ����� (������ ��ǥ, ��Ÿ��)
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW,		//(������Ŭ�����̸�, ������Ÿ��Ʋ�̸�, �����콺Ÿ��,
		0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);				//������x,y��ǥ, �����찡��,����ũ��, �θ������ڵ�, �޴��ڵ�, �������α׷��ν��Ͻ�. ��������������)

	// 4. �����츦 ȭ�鿡 ����
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 5. �����쿡�� �߻��� �̺�Ʈ�� ���� �޽��� ������
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	RECT winRect = { 0,0,WINWIDTH,WINHEIGHT };
	PAINTSTRUCT ps;
	RECT rect;

	switch (iMessage) {
	case WM_CREATE:
		AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, false);
		MoveWindow(hWnd, 100, 50, winRect.right - winRect.left, winRect.bottom - winRect.top, false);
		BackGround[0].Load(TEXT("��.png"));			//���� ȭ��
		BackGround[1].Load(TEXT("��漺X.png"));		
		Deck.Load(TEXT("ī��޸�.png"));

		batImg.Load(TEXT	(".//������//����.png"));
		wolfImg.Load(TEXT	(".//������//����.png"));
		papyrusImg.Load(TEXT(".//������//���Ƿ罺.png"));
		bossHpBar.Load(TEXT	("����ü�¹�.png"));
		ultiImg.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������.png"));
		//ultiImg.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������_��������ź.png"));

		manaImg[0].Load(TEXT("����.png"));
		manaImg[1].Load(TEXT("�󸶳�.png"));

		//Tripord[N_ghltjsckd][I_Tier3] = 2;

		papyrus.hitBox = { -500,-500,0,0 };

		// �÷��̾� �ʱ� ����
		player.SetRect(500, GROUNDYPOINT - PlayerSize, 500 + PlayerSize, GROUNDYPOINT);
		head = new Node_Object;
		head->next = NULL;
		key_a = key_d = play_on = onemore = false;
		player.SetImage(L"./\\���� ���� �̹���\\â����.png");

		start = false, changing = false, 				//���� ���ۿ�
		//start = true, changing = false;				//ȭ��ٲ�°� �����Ƽ� �����
		cardDrawing = true, isClick = false;
		manaCount = 10, maxMana = 10, castleHp = 1000;
		money = 0, ultimate = 200, experience = 0, level = 0;
		for (int i = 0; i < 10; i++)
		{
			experienceBar[i] = (i+1) * (i+1) * 2 + 30 / (i+2);
		}
		SetTimer(hWnd, 0, 17, NULL);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hDC);
		oldBit1 = (HBITMAP)SelectObject(memdc, hBit1);

		BitBlt(hDC, 0, 0, WINWIDTH, WINHEIGHT, memdc, 0, 0, SRCCOPY);

		SelectObject(memdc, oldBit1);
		DeleteDC(memdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		// �� ������ gameLoading -> changeLoading -> chageStart -> gameStart;
		if (start) {
			if (changing) {
				changeStart();		//���� ������ ���� ���̵���
			}
			else {
				
				gameStart();		//���� ����ȭ��
				if (castleHp <= 0 || papyrus.hp <= 0) {
					KillTimer(hWnd, 0);
					PostQuitMessage(0);
				}
			}
		}
		else {
			if (changing)
				changeLoading();	// ���� ������ ���� ���̵�ƿ�
			else
				gameLoading();		// ���� ������ ����ȭ��
		}
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_LBUTTONDOWN:
		if (start) {
			if (!cardDrawing) {
				isClick = true;
				startX = mx;
				startY = my;
			}
		}
		else {
			gameLoadClick(lParam);	// ����ȭ���϶� Ŭ�� ����
		}
		break;
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (isClick && clickSelect != -1) {
			handCard[clickSelect]->point.x += (mx - startX);
			handCard[clickSelect]->point.y += (my - startY);
			startX = mx;
			startY = my;
		}
		break;
	case WM_LBUTTONUP:
		if (isClick) {
			isClick = false;
			if (clickSelect != -1) {
				if (my < WINHEIGHT * 3 / 5 && manaCount >= handCard[clickSelect]->Mana){
					manaCount -= handCard[clickSelect]->Mana;
					useCard();
					setCardPoint();
				}
				else {
					handCard[clickSelect]->point = prevCardPoint;
				}
				clickSelect = -1;
				prevCardPoint = { -1,-1 };
			}
		}
		break;
	case WM_KEYDOWN:
		if (wParam == 'e' || wParam == 'E') {
			if (player.GetState() != Skill && player.GetState() != Stun && ultimate > 199) {
				player.SetState(Skill);
				if (player.GetDirection() == Left)
					player.SetImage(L"./\\���� ���� �̹���\\â����_��������ź_����Ʈ(left).png");
				else
					player.SetImage(L"./\\���� ���� �̹���\\â����_��������ź_����Ʈ.png");
				for (int i = 0; i < player.GetFrame_Max(); i++) {
					if (i < 4) {
						player.SetOder(i, { 0,15 }, -1);
					}
					else if (i < 9) {
						if (i == 7)
							player.SetOder(i, { 0, 0 }, Meteor_Spear);
						else
							player.SetOder(i, { 0, 0 }, -1);
					}
					else {
						player.SetOder(i, { 0, -20 }, -1);
					}
				}
				player.SetOder(player.GetFrame_Max() - 1, { 0, -20 }, Explosion);
				player.SetBaseDelay(5);
				player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
				player.SetDamage(20);
				player.SetNeutralization(40);
				player.SetDestruction(2);
			}
		}
		else if (wParam == 'a' || wParam == 'A') {
			

			if (key_a == false && (player.GetState() == Stay || player.GetState() == Move || player.GetState() == Run)) {
				key_a = true;
				player.SetImage(L"./\\���� ���� �̹���\\â����_move(left).png");
				player.SetState(Move);
			}

		}
		else if (wParam == 'd' || wParam == 'D') {
			if (key_d == false && (player.GetState() == Stay || player.GetState() == Move || player.GetState() == Run)) {
				key_d = true;
				player.SetImage(L"./\\���� ���� �̹���\\â����_move.png");
				player.SetState(Move);
			}

		}
		break;
	case WM_KEYUP:
		if (wParam == 'a' || wParam == 'A') {
			if (key_a == true) {
				key_a = false;
				if (!key_d) {
					player.SetImage(L"./\\���� ���� �̹���\\â����(left).png");
					player.SetState(Stay);
				}
			}

		}
		else if (wParam == 'd' || wParam == 'D') {
			if (key_d == true) {
				key_d = false;
				if (!key_a) {
					player.SetImage(L"./\\���� ���� �̹���\\â����.png");
					player.SetState(Stay);
				}
			}

		}
		break;
	case WM_COMMAND:
	{
		bool startTimer = false;
		switch (LOWORD(wParam))
		{
			case IDC_BUTTON_BUY1:
				if(money >= cardPrice[0]) {
					startTimer = true;
					if (cardPrice[0] == 5 || cardPrice[0] == 0) {
						Tripord[randValue[0]][3] = 1;
						makeCard(randValue[0]);
					}
					else {
						if (cardPrice[0] == 10)
							Tripord[randValue[0]][0] = triNum[0];
						else if (cardPrice[0] == 20)
							Tripord[randValue[0]][1] = triNum[0];
						else if (cardPrice[0] == 30)
							Tripord[randValue[0]][2] = triNum[0];

						setCardTripod(randValue[0]);
					}
					money -= cardPrice[0];
				}
				break;
			case IDC_BUTTON_BUY2:
				if (money >= cardPrice[1]) {
					startTimer = true;
					if (cardPrice[1] == 5 || cardPrice[1] == 0) {
						Tripord[randValue[1]][3] = 1;
						makeCard(randValue[1]);
					}
					else {
						if (cardPrice[1] == 10)
							Tripord[randValue[1]][0] = triNum[1];
						else if (cardPrice[1] == 20)
							Tripord[randValue[1]][1] = triNum[1];
						else if (cardPrice[1] == 30)
							Tripord[randValue[1]][2] = triNum[1];

						setCardTripod(randValue[1]);
					}
					money -= cardPrice[1];
				}
				break;
			case IDC_BUTTON_BUY3:
				if (money >= cardPrice[2]) {
					startTimer = true;
					if (cardPrice[2] == 5 || cardPrice[2] == 0) {
						Tripord[randValue[2]][3] = 1;
						makeCard(randValue[2]);
					}
					else {
						if (cardPrice[2] == 10)
							Tripord[randValue[2]][0] = triNum[2];
						else if (cardPrice[2] == 20)
							Tripord[randValue[2]][1] = triNum[2];
						else if (cardPrice[2] == 30)
							Tripord[randValue[2]][2] = triNum[2];

						setCardTripod(randValue[2]);
					}
					money -= cardPrice[2];
				}
				break;
			case IDC_BUTTON_BUY4:
				startTimer = true;
				break;
		default:
			break;
		}
		if (startTimer) {
			DestroyWindow(GetDlgItem(hWnd, IDC_BUTTON_BUY1));
			DestroyWindow(GetDlgItem(hWnd, IDC_BUTTON_BUY2));
			DestroyWindow(GetDlgItem(hWnd, IDC_BUTTON_BUY3));
			DestroyWindow(GetDlgItem(hWnd, IDC_BUTTON_BUY4));
			SetTimer(hWnd, 0, 17, NULL);
		}
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
void UpdatePlayer() {
	player.DelayMinus();
	if (player.GetState() == Stun) {
		player.SetStuncount(player.GetStuncount() - 1);
		if (0 == player.GetDelay()) {
			player.PlusFrame_Now();
			if (player.GetFrame_Max() <= player.GetFrame_Now()) {
				player.SetFrame_Now(0);
				player.Delete_Hitlist();
			}
			player.SetDelay(player.GetBaseDelay());
		}
		if (player.GetStuncount() == 0)
			player.SetState(Stay);
	}
	else {
		if (player.GetState() == Stay)
			player.SetSpeed(0, -15);
		else if (player.GetState() == Move || player.GetState() == Run) {
			if (key_a) {
				if (player.GetState() == Run)
					player.SetSpeed(-15, 0);
				else
					player.SetSpeed(-7, 0);
			}
			if (key_d) {
				if (player.GetState() == Run)
					player.SetSpeed(15, 0);
				else
					player.SetSpeed(7, 0);
			}
			if (player.GetRuncount() <= 0) {
				player.SetState(Move);
			}
			else {
				player.SetState(Run);
			}
		}
		player.SetRuncount(player.GetRuncount() - 1);
		if (0 == player.GetDelay()) {
			player.PlusFrame_Now();
			if (player.GetFrame_Max() <= player.GetFrame_Now()) {
				player.SetFrame_Now(0);
				player.Delete_Hitlist();
				if (player.GetState() == Skill && !onemore) {
					player.SetRect(player.GetRect().right - PlayerSize, player.GetRect().bottom - PlayerSize, player.GetRect().right, player.GetRect().bottom);
					player.SetState(Stay);
					if (player.GetDirection() == Left)
						player.SetImage(L"./\\���� ���� �̹���\\â����(left).png");
					else
						player.SetImage(L"./\\���� ���� �̹���\\â����.png");

				}
				onemore = false;
			}
			player.SetSpeed(player.GetOder(player.GetFrame_Now()).speed.x, player.GetOder(player.GetFrame_Now()).speed.y);
			player.SetDelay(player.GetBaseDelay());
			if (player.GetOder(player.GetFrame_Now()).spawn_object_type > -1) {
				Insert_Object(head, player.GetOder(player.GetFrame_Now()).spawn_object_type, player.GetDirection());
			}
			if (!onemore)
				player.SetOder(player.GetFrame_Now(), { 0,0 }, -1);
		}

		player.Move(GROUNDYPOINT);
		RECT null_rect = { 0,0,0,0 };

		for (int i = 0; i < 2; i++) {
			if (bone[i] != NULL)
				if (IntersectRect(&null_rect, player.GetRect(1), &bone[i]->hitBox)) {
					player.SetState(Stun);
					player.SetStuncount(100);
				}

		}
		for (int i = 0; i < 15; i++) {
			if (miniBone[i] != NULL)
				if (IntersectRect(&null_rect, player.GetRect(1), &miniBone[i]->hitBox)) {
					player.SetState(Stun);
					player.SetStuncount(30);
					delete miniBone[i];
					miniBone[i] = nullptr;
				}

		}

		if (player.GetState() == Skill){
			if (IntersectRect(&null_rect, player.GetRect(1), &papyrus.hitBox)) {
				if (!player.Check_HItList(&papyrus)) {
					papyrus.hit(player.GetNamed_Damage() + player.GetDamage(), player.GetDestruction(), player.GetNeutralization());
					player.Insert_Hitlist(&papyrus);
				}
			}

		for (int i = 0; i < MAXWOLF; i++) {
			if (wolf[i] != NULL) {
				if (wolf[i]->canDie) {
					delete wolf[i];
					wolf[i] = nullptr;
				}
				else if (IntersectRect(&null_rect, player.GetRect(1), &wolf[i]->hitBox) && wolf[i]->status != Wolf_Dead && wolf[i]->status != Wolf_Die) {
					if (!player.Check_HItList(wolf[i])) {
						if (player.GetType() == Ice) {
							wolf[i]->st = Ice_s;
							wolf[i]->count = wolf[i]->wait = 0;
						}
						if (player.GetType() == Fire) {
							wolf[i]->st = Fire_s;
							wolf[i]->count = wolf[i]->wait = 0;
						}
						if (player.GetType() == Hurricane) {
							int weight = wolf[i]->hitBox.right - wolf[i]->hitBox.left;
							if (player.GetDirection() == Left) {
								wolf[i]->hitBox.left = player.GetRect().left - 50;
								wolf[i]->hitBox.right = wolf[i]->hitBox.left + weight;
							}
							else {
								wolf[i]->hitBox.left = player.GetRect().right + 50;
								wolf[i]->hitBox.right = wolf[i]->hitBox.left + weight;
							}
						}
						wolf[i]->hit(player.GetDamage() + player.GetSeedDamage());
						player.Insert_Hitlist(wolf[i]);
					}
				}
			}
		}
		for (int i = 0; i < MAXBAT; i++) {
			if (bat[i] != NULL) {
				if (bat[i]->canDie) {
					delete bat[i];
					bat[i] = nullptr;
				}
				else if (IntersectRect(&null_rect, player.GetRect(1), &bat[i]->hitBox) && bat[i]->status != Bat_Dead && bat[i]->status != Bat_Die) {
					if (!player.Check_HItList(bat[i])) {
						bat[i]->hit(player.GetDamage() + player.GetSeedDamage());
						player.Insert_Hitlist(bat[i]);

					}
				}
			}
		}
	}
		for (Node_Object* p = head; p->next != NULL; p = p->next) {
			if (p->next->data.GetFrame_Now() == p->next->data.GetFrame_Max()) {
				if (p->next->data.GetAttacknums() == 0) {
					Node_Object* target = p->next;
					p->next = p->next->next;
					delete target;
					if (p->next == NULL)
						break;
				}
				else {
					p->next->data.SetAttacknums(p->next->data.GetAttacknums() - 1);
					p->next->data.SetFrame_Now(0);
				}
			}
			p->next->data.DelayMinus();
			if (p->next->data.GetDelay() == 0) {
				p->next->data.PlusFrame_Now();
				p->next->data.SetDelay(p->next->data.GetBaseDelay());
			}
			if (p->next->data.GetType() == Airborne_Spear) {
				p->next->data.SetSpeed(player.GetSpeed().x, player.GetSpeed().y);
			}
			p->next->data.Move(GROUNDYPOINT);
			if (IntersectRect(&null_rect, p->next->data.GetRect(1), &papyrus.hitBox)) {
				if (!player.Check_HItList(&papyrus)) {
					papyrus.hit(p->next->data.GetNamed_Damage() + p->next->data.GetDamage(), p->next->data.GetDestruction(), p->next->data.GetNeutralization());
					p->next->data.Insert_Hitlist(&papyrus);
				}
			}
			for (int i = 0; i < MAXWOLF; i++) {
				if (wolf[i] != NULL) {
					if (wolf[i]->canDie) {
						delete wolf[i];
						wolf[i] = nullptr;
					}
					else if (IntersectRect(&null_rect, p->next->data.GetRect(1), &wolf[i]->hitBox) && wolf[i]->status != Wolf_Dead && wolf[i]->status != Wolf_Die) {
						if (!p->next->data.Check_HItList(wolf[i])) {
							wolf[i]->hit(p->next->data.GetDamage() + p->next->data.GetSeedDamage());
							p->next->data.Insert_Hitlist(wolf[i]);
						}
						if (p->next->data.GetType() == Earthquake || p->next->data.GetType() == Wall) {
							wolf[i]->hit(0);
						}
						if (player.GetType() == Hurricane) {
							int weight = wolf[i]->hitBox.right - wolf[i]->hitBox.left;
							if (player.GetDirection() == Left) {
								wolf[i]->hitBox.left = player.GetRect().left - 50;
								wolf[i]->hitBox.right = wolf[i]->hitBox.left + weight;
							}
							else {
								wolf[i]->hitBox.left = player.GetRect().right + 50;
								wolf[i]->hitBox.right = wolf[i]->hitBox.left + weight;
							}
						}

					}
				}

			}
			for (int i = 0; i < MAXBAT; i++) {
				if (bat[i] != NULL) {
					if (bat[i]->canDie) {
						delete bat[i];
						bat[i] = nullptr;
					}
					else if (IntersectRect(&null_rect, p->next->data.GetRect(1), &bat[i]->hitBox) && bat[i]->status != Bat_Dead && bat[i]->status != Bat_Die) {
						if (!p->next->data.Check_HItList(bat[i])) {
							bat[i]->hit(p->next->data.GetDamage() + p->next->data.GetSeedDamage());
							p->next->data.Insert_Hitlist(bat[i]);

						}
						if (p->next->data.GetType() == Wall) {
							bat[i]->hit(0);
						}
						if (player.GetType() == Hurricane) {
							int weight = wolf[i]->hitBox.right - wolf[i]->hitBox.left;
							if (player.GetDirection() == Left) {
								wolf[i]->hitBox.left = player.GetRect().left - 50;
								wolf[i]->hitBox.right = wolf[i]->hitBox.left + weight;
							}
							else {
								wolf[i]->hitBox.left = player.GetRect().right + 50;
								wolf[i]->hitBox.right = wolf[i]->hitBox.left + weight;
							}
						}

					}
				}
			}

		}
	}
}
void useCard() {
	if (player.GetState() != Skill && player.GetState() != Stun) {

		//TODO: ī�� ����
		bool canNull = true;
		player.SetState(Skill);
		switch (handCard[clickSelect]->cardname)
		{
		case N_cjdfydwls: // û����
			if (player.GetDirection() == Left)
				player.SetImage(L"./\\���� ���� �̹���\\â����_û����_����Ʈ(left).png");
			else
				player.SetImage(L"./\\���� ���� �̹���\\â����_û����_����Ʈ.png");
			for (int i = 0; i < player.GetFrame_Max(); i++) {
				player.SetOder(i, { 0,0 }, -1);
			}
			player.SetBaseDelay(10);
			player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
			player.SetDamage(5);
			player.SetNeutralization(5);
			player.SetDestruction(1);
			if (Tripord[N_cjdfydwls][0] == 1) {
				player.SetNeutralization(player.GetNeutralization() + 2);
			}
			else if (Tripord[N_cjdfydwls][0] == 2) {
				player.SetDamage(player.GetDamage() + 1);

			}
			else if (Tripord[N_cjdfydwls][0] == 3) {
				player.SetRect(player.GetRect().left - 30, player.GetRect().top - 30, player.GetRect().right, player.GetRect().bottom);
			}
			if (Tripord[N_cjdfydwls][1] == 1) {
				if (player.GetDirection() == Left)
					player.SetImage(L"./\\���� ���� �̹���\\â����_û����â�������_����Ʈ(left).png");
				else
					player.SetImage(L"./\\���� ���� �̹���\\â����_û����â�������_����Ʈ.png");
				for (int i = 0; i < player.GetFrame_Max(); i++) {
					player.SetOder(i, { 0,0 }, -1);
					if (i == 4)
						player.SetOder(i, { 0,0 }, Drop_Spear);

				}
				player.SetRect(player.GetRect().left + 30, player.GetRect().top + 30, player.GetRect().right, player.GetRect().bottom);
				player.SetBaseDelay(4);
				player.SetDamage(player.GetDamage() + 2);

			}
			else if (Tripord[N_cjdfydwls][1] == 2) {
				player.SetRect(player.GetRect().left - 30, player.GetRect().top - 30, player.GetRect().right, player.GetRect().bottom);

			}
			else if (Tripord[N_cjdfydwls][1] == 3) {
				player.SetOder(3, { 0,0 }, Wall);

			}
			if (Tripord[N_cjdfydwls][2] == 1) {
				drawCard();
				setCardPoint();
			}
			else if (Tripord[N_cjdfydwls][2] == 2) {
				//TODO:�������� 
			}
			break;
		case N_qksdnjftja: // �ݿ���
			if (player.GetDirection() == Left)
				player.SetImage(L"./\\���� ���� �̹���\\â����_�ݿ���_����Ʈ(left).png");
			else
				player.SetImage(L"./\\���� ���� �̹���\\â����_�ݿ���_����Ʈ.png");
			for (int i = 0; i < player.GetFrame_Max(); i++) {
				if (i < 2)
					if (player.GetDirection() == Left)
						player.SetOder(i, { -20,0 }, -1);
					else
						player.SetOder(i, { 20,0 }, -1);

				else
					player.SetOder(i, { 0,0 }, -1);

			}
			player.SetBaseDelay(5);
			player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
			player.SetDamage(12);
			player.SetNeutralization(20);
			player.SetDestruction(2);

			if (Tripord[N_qksdnjftja][0] == 1) {
				player.SetDestruction(player.GetDestruction() + 1);
			}
			else if (Tripord[N_qksdnjftja][0] == 2) {
				player.SetDamage(player.GetDamage() + 2);
			}
			else if (Tripord[N_qksdnjftja][0] == 3) {
				for (int i = 0; i < player.GetFrame_Max(); i++) {
					if (i < 2)
						if (player.GetDirection() == Left)
							player.SetOder(i, { -30,0 }, -1);
						else
							player.SetOder(i, { 30,0 }, -1);

					else
						player.SetOder(i, { 0,0 }, -1);

				}

			}
			if (Tripord[N_qksdnjftja][1] == 1) {
				player.SetNeutralization(player.GetNeutralization() + 10);
			}
			else if (Tripord[N_qksdnjftja][1] == 2) {
				player.SetNamed_Damage(player.GetNamed_Damage() + 2);
			}
			else if (Tripord[N_qksdnjftja][1] == 3) {
				//TODO:�������� 

			}
			if (Tripord[N_qksdnjftja][2] == 1) {
				player.SetType(Hurricane);
			}
			else if (Tripord[N_qksdnjftja][2] == 2) {
				player.SetOder(player.GetFrame_Max() - 1, { 0,0 }, Hurricane);
			}

			break;
		case N_aodfyddufvk: // �ͷ濭��
			if (player.GetDirection() == Left)
				player.SetImage(L"./\\���� ���� �̹���\\â����_�ͷ濭��2_����Ʈ(left).png");
			else
				player.SetImage(L"./\\���� ���� �̹���\\â����_�ͷ濭��2_����Ʈ.png");
			for (int i = 0; i < player.GetFrame_Max(); i++) {
				if (player.GetDirection() == Left)
					player.SetOder(i, { -2,0 }, -1);
				else
					player.SetOder(i, { 2,0 }, -1);
			}
			player.SetBaseDelay(5);
			player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
			player.SetDamage(10);
			player.SetNeutralization(15);
			player.SetDestruction(0);
			if (Tripord[N_aodfyddufvk][0] == 1) {
				player.SetRect(player.GetRect().left - 30, player.GetRect().top - 30, player.GetRect().right, player.GetRect().bottom);
			}
			else if (Tripord[N_aodfyddufvk][0] == 2) {
				player.SetNeutralization(player.GetNeutralization() + 5);
			}
			else if (Tripord[N_aodfyddufvk][0] == 3) {
				player.SetDamage(player.GetDamage() + 2);
			}
			if (Tripord[N_aodfyddufvk][1] == 1) {
				player.SetBaseDelay(4);
			}
			else if (Tripord[N_aodfyddufvk][1] == 2) {
				if (player.GetDirection() == Left)
					player.SetImage(L"./\\���� ���� �̹���\\â����_�ͷ濭��2_��������Ʈ(left).png");
				else
					player.SetImage(L"./\\���� ���� �̹���\\â����_�ͷ濭��2_��������Ʈ.png");
				player.SetType(Ice);
			}
			else if (Tripord[N_aodfyddufvk][1] == 3) {
				if (player.GetDirection() == Left)
					player.SetImage(L"./\\���� ���� �̹���\\â����_�ͷ濭��2_ȭ������Ʈ(left).png");
				else
					player.SetImage(L"./\\���� ���� �̹���\\â����_�ͷ濭��2_ȭ������Ʈ.png");
				player.SetType(Fire);
			}
			if (Tripord[N_aodfyddufvk][2] == 1) {
				onemore = true;
			}
			else if (Tripord[N_aodfyddufvk][2] == 2) {
				//TODO:��������
			}
			break;
		case N_ghltjsckd: // ȸ��â
			if (player.GetDirection() == Left)
				player.SetImage(L"./\\���� ���� �̹���\\â����_ȸ��â_����Ʈ(left).png");
			else
				player.SetImage(L"./\\���� ���� �̹���\\â����_ȸ��â_����Ʈ.png");
			for (int i = 0; i < player.GetFrame_Max(); i++) {
				if (i < 2) {
					if (player.GetDirection() == Left)
						player.SetOder(i, { -15,10 }, -1);
					else
						player.SetOder(i, { 15,10 }, -1);
				}
				else {
					if (player.GetDirection() == Left)
						player.SetOder(i, { -15,-10 }, -1);
					else
						player.SetOder(i, { 15,-10 }, -1);
				}
			}
			onemore = true;
			player.SetBaseDelay(3);
			player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
			player.SetDamage(9);
			player.SetNeutralization(10);
			player.SetDestruction(0);
			if (Tripord[N_ghltjsckd][0] == 1) {
				for (int i = 0; i < player.GetFrame_Max(); i++) {
					if (i < 2) {
						if (player.GetDirection() == Left)
							player.SetOder(i, { -20,10 }, -1);
						else
							player.SetOder(i, { 20,10 }, -1);
					}
					else {
						if (player.GetDirection() == Left)
							player.SetOder(i, { -20,-10 }, -1);
						else
							player.SetOder(i, { 20,-10 }, -1);
					}
				}

			}
			else if (Tripord[N_ghltjsckd][0] == 2) {
				player.SetDamage(player.GetDamage() + 2);
			}
			else if (Tripord[N_ghltjsckd][0] == 3) {
				onemore = false;
				player.SetDamage(player.GetDamage() + 4);
			}
			if (Tripord[N_ghltjsckd][1] == 1) {
				player.SetType(Knockdown);
			}
			else if (Tripord[N_ghltjsckd][1] == 2) {
				player.SetNamed_Damage(3);
			}
			else if (Tripord[N_ghltjsckd][I_Tier2] == 3) {
				plusUltimate();
			}

			if (Tripord[N_ghltjsckd][I_Tier3] == 1) {
				if (!handCard[clickSelect]->getOnce()) {//��ī��
					Ghltjsckd* temp = new Ghltjsckd(true);
					handCard[clickSelect] = temp;
					canNull = false;
				}
			}
			else if (Tripord[N_ghltjsckd][I_Tier3] == 2) {
				drawCard(true);
			}
			break;
		case N_dusghkstja: // ��ȯ��
			if (player.GetDirection() == Left)
				player.SetImage(L"./\\���� ���� �̹���\\â����_��ȯ��_����Ʈ_�����߰�(left).png");
			else
				player.SetImage(L"./\\���� ���� �̹���\\â����_��ȯ��_����Ʈ_�����߰�.png");
			for (int i = 0; i < player.GetFrame_Max(); i++) {
				if (i < 3) {
					if (player.GetDirection() == Left)
						player.SetOder(i, { -20,0 }, -1);
					else
						player.SetOder(i, { 20,0 }, -1);
				}
				else {
					player.SetOder(i, { 0,0 }, -1);
				}
			}
			player.SetBaseDelay(3);
			player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
			player.SetDamage(6);
			player.SetNeutralization(5);
			player.SetDestruction(1);
			if (Tripord[N_dusghkstja][0] == 1) {
				player.SetFrame_Now(3);
				player.SetDamage(6 + 1);
			}
			else if (Tripord[N_dusghkstja][0] == 2) {
				for (int i = 0; i < player.GetFrame_Max(); i++) {
					if (i < 3) {
						if (player.GetDirection() == Left)
							player.SetOder(i, { -25,0 }, -1);
						else
							player.SetOder(i, { 25,0 }, -1);
					}
					else {
						player.SetOder(i, { 0,0 }, -1);
					}
				}
			}
			else if (Tripord[N_dusghkstja][I_Tier1] == 3) {
				plusUltimate();
			}
			if (Tripord[N_dusghkstja][1] == 1) {
				player.SetBaseDelay(2);
			}
			else if (Tripord[N_dusghkstja][1] == 2) {
				player.SetNeutralization(player.GetNeutralization() + 3);
			}
			else if (Tripord[N_dusghkstja][1] == 3) {
				player.SetDamage(player.GetDamage() + 2);
			}
			if (Tripord[N_dusghkstja][2] == 1) {
				drawCard();
			}
			else if (Tripord[N_dusghkstja][2] == 2) {
				for (int i = 0; i < player.GetFrame_Max(); i++) {
					if (i < 3) {
						if (player.GetDirection() == Left)
							player.SetOder(i, { -25,0 }, -1);
						else
							player.SetOder(i, { 25,0 }, -1);
					}
					else {
						player.SetOder(i, { 0,0 }, SowrdLight);
					}
				}

			}

			break;
		case N_cjdfydcnftn: // û�����
			if (player.GetDirection() == Left)
				player.SetImage(L"./\\���� ���� �̹���\\â����_û�����_����Ʈ(left).png");
			else
				player.SetImage(L"./\\���� ���� �̹���\\â����_û�����_����Ʈ.png");
			for (int i = 0; i < player.GetFrame_Max(); i++) {
				if (i < 4) {
					if (player.GetDirection() == Left)
						player.SetOder(i, { -20,0 }, -1);
					else
						player.SetOder(i, { 20,0 }, -1);
				}
				else {
					player.SetOder(i, { 0,0 }, -1);
				}
			}
			player.SetBaseDelay(2);
			player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
			player.SetDamage(5);
			player.SetNeutralization(15);
			player.SetDestruction(0);
			if (Tripord[N_cjdfydcnftn][0] == 1) {
				player.SetDamage(player.GetDamage() + 1);

			}
			else if (Tripord[N_cjdfydcnftn][0] == 2) {
				player.SetFrame_Now(4);
				player.SetDamage(player.GetDamage() + 2);

			}
			else if (Tripord[N_cjdfydcnftn][0] == 3) {
				for (int i = 0; i < player.GetFrame_Max(); i++) {
					if (i < 4) {
						if (player.GetDirection() == Left)
							player.SetOder(i, { -25,0 }, -1);
						else
							player.SetOder(i, { 25,0 }, -1);
					}
					else {
						player.SetOder(i, { 0,0 }, -1);
					}
				}
			}
			if (Tripord[N_cjdfydcnftn][1] == 1) {
				player.SetType(Hurricane);
			}
			else if (Tripord[N_cjdfydcnftn][1] == 2) {
				//TODO:���������� �߰�ȸ��
			}
			else if (Tripord[N_cjdfydcnftn][1] == 3) {
				player.SetRect(player.GetRect().left - 30, player.GetRect().top - 30, player.GetRect().right, player.GetRect().bottom);
			}
			if (Tripord[N_cjdfydcnftn][2] == 1) {
				player.SetOder(player.GetFrame_Max() - 1, { 0,0 }, Rotation_Spear);
			}
			else if (Tripord[N_cjdfydcnftn][2] == 2) {
				player.SetOder(player.GetFrame_Max() - 1, { 0,0 }, Airborne_Spear);
			}

			break;
		case N_dmsgkdbtjdxks: // ��������ź
			if (player.GetDirection() == Left)
				player.SetImage(L"./\\���� ���� �̹���\\â����_��������ź_����Ʈ(left).png");
			else
				player.SetImage(L"./\\���� ���� �̹���\\â����_��������ź_����Ʈ.png");
			for (int i = 0; i < player.GetFrame_Max(); i++) {
				if (i < 4) {
					player.SetOder(i, { 0,15 }, -1);
				}
				else if (i < 9) {
					if (i == 7)
						player.SetOder(i, { 0, 0 }, Meteor_Spear);
					else
						player.SetOder(i, { 0, 0 }, -1);
				}
				else {
					if (player.GetFrame_Max() - 1)
						player.SetOder(i, { 0, -20 }, Explosion);
					else
						player.SetOder(i, { 0, -20 }, -1);
				}
			}
			player.SetBaseDelay(5);
			player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
			player.SetDamage(20);
			player.SetNeutralization(40);
			player.SetDestruction(2);

			break;
		case N_wjrfydvh: // ������
			if (player.GetDirection() == Left)
				player.SetImage(L"./\\���� ���� �̹���\\â����_������_����Ʈ(left).png");
			else
				player.SetImage(L"./\\���� ���� �̹���\\â����_������_����Ʈ.png");
			for (int i = 0; i < player.GetFrame_Max(); i++) {
				player.SetOder(i, { 0, 0 }, -1);
			}
			player.SetOder(player.GetFrame_Max() - 2, { 0,0 }, Red_Spear);
			player.SetBaseDelay(3);
			player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
			player.SetDamage(15);
			player.SetNeutralization(5);
			player.SetDestruction(1);

			if (Tripord[N_wjrfydvh][0] == 1) {
				player.SetBaseDelay(2);
			}
			else if (Tripord[N_wjrfydvh][0] == 2) {
				// ��Ÿ������� Insert_Object���� ó���մϴ�
			}
			else if (Tripord[N_wjrfydvh][0] == 3) {
				player.SetDamage(player.GetDamage() + 3);
			}

			if (Tripord[N_wjrfydvh][1] == 1) {
				//TODO:��������
			}
			else if (Tripord[N_wjrfydvh][I_Tier2] == 2) {
				drawCard(false);
			}
			else if (Tripord[N_wjrfydvh][1] == 3) {
				player.SetDestruction(player.GetDestruction() + 1);
			}

			if (Tripord[N_wjrfydvh][2] == 1) {
				// 2���� �߰� â���� Insert_Object���� ó���մϴ�
			}
			else if (Tripord[N_wjrfydvh][2] == 2) {
				player.SetNamed_Damage(player.GetNamed_Damage() + 15);
			}

			break;
		case N_dbtjdrkdcjs: // ������õ
			if (player.GetDirection() == Left)
				player.SetImage(L"./\\���� ���� �̹���\\â����_������õ_����Ʈ(left).png");
			else
				player.SetImage(L"./\\���� ���� �̹���\\â����_������õ_����Ʈ.png");
			for (int i = 0; i < player.GetFrame_Max(); i++) {
				if (i < 3) {
					if (player.GetDirection() == Left)
						player.SetOder(i, { 0,12 }, -1);
					else
						player.SetOder(i, { 0,12 }, -1);
				}
				else if (i < 6) {
					player.SetOder(i, { 0, 0 }, -1);
				}
				else if (i < 8) {
					if (player.GetDirection() == Left)
						player.SetOder(i, { -15,-20 }, -1);
					else
						player.SetOder(i, { 15,-20 }, -1);

				}
				else
					player.SetOder(i, { 0, 0 }, -1);
			}
			player.SetBaseDelay(5);
			player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
			player.SetDamage(12);
			player.SetNeutralization(5);
			player.SetDestruction(0);
			if (Tripord[N_dbtjdrkdcjs][0] == 1) {
				player.SetBaseDelay(4);

			}
			else if (Tripord[N_dbtjdrkdcjs][0] == 2) {
				player.SetSeedDamage(player.GetSeedDamage() + 2);

			}
			else if (Tripord[N_dbtjdrkdcjs][0] == 3) {
				player.SetNamed_Damage(player.GetNamed_Damage() + 2);
			}
			if (Tripord[N_dbtjdrkdcjs][1] == 1) {
				player.SetOder(player.GetFrame_Max() - 1, { 0,0 }, Earthquake);
			}
			else if (Tripord[N_dbtjdrkdcjs][1] == 2) {
				player.SetOder(player.GetFrame_Max() - 1, { 0,0 }, Flame_Zone);
			}
			else if (Tripord[N_dbtjdrkdcjs][1] == 3) {
				player.SetOder(player.GetFrame_Max() - 1, { 0,0 }, Wall);
			}
			if (Tripord[N_dbtjdrkdcjs][2] == 1) {
				player.SetOder(player.GetFrame_Max() - 1, { 0,0 }, Drop_Red_Spear);
			}
			else if (Tripord[N_dbtjdrkdcjs][2] == 2) {
				for (int i = 0; i < player.GetFrame_Max(); i++) {
					player.SetOder(i, { 0, 0 }, -1);
				}
				player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
				if (player.GetDirection() == Left)
					player.SetImage(L"./\\���� ���� �̹���\\â����_������õâ�������_����Ʈ(left).png");
				else
					player.SetImage(L"./\\���� ���� �̹���\\â����_������õâ�������_����Ʈ.png");
				player.SetOder(4, { 0,0 }, Drop_Red_Spear);
			}

			break;
		case N_rhlddufvk: // ������
			if (player.GetDirection() == Left)
				player.SetImage(L"./\\���� ���� �̹���\\â����_������_����Ʈ(left).png");
			else
				player.SetImage(L"./\\���� ���� �̹���\\â����_������_����Ʈ.png");
			for (int i = 0; i < player.GetFrame_Max(); i++) {
				if (i > 4)
					if (player.GetDirection() == Left)
						player.SetOder(i, { -8,0 }, -1);
					else
						player.SetOder(i, { 8,0 }, -1);
				else
					player.SetOder(i, { 0, 0 }, -1);
			}
			player.SetOder(player.GetFrame_Max() - 2, { 0,0 }, Yellow_Spear);
			player.SetBaseDelay(4);
			player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
			player.SetDamage(10);
			player.SetNeutralization(5);
			player.SetDestruction(1);
			if (Tripord[N_rhlddufvk][0] == 1) {
				player.SetDestruction(player.GetDestruction() + 1);
			}
			else if (Tripord[N_rhlddufvk][0] == 2) {
				player.SetBaseDelay(3);
			}
			else if (Tripord[N_rhlddufvk][0] == 3) {
				player.SetRuncount(100);
			}
			if (Tripord[N_rhlddufvk][1] == 1) {
				if (player.GetDirection() == Left)
					player.SetImage(L"./\\���� ���� �̹���\\â����_������_ȭ������Ʈ(left).png");
				else
					player.SetImage(L"./\\���� ���� �̹���\\â����_������_ȭ������Ʈ.png");
				player.SetType(Fire);
			}
			else if (Tripord[N_rhlddufvk][1] == 2) {
				//���� â������ ���ĳ�
			}
			else if (Tripord[N_rhlddufvk][1] == 3) {
				player.SetNamed_Damage(player.GetNamed_Damage() + 3);
			}
			if (Tripord[N_rhlddufvk][2] == 1) {
				player.SetBaseDelay(player.GetBaseDelay() + 1);
				player.SetDamage(player.GetDamage() + 4);
			}
			else if (Tripord[N_rhlddufvk][2] == 2) {
				//TODO:��������
			}

			break;
		case N_sktjsckd: // ����â
			if (player.GetDirection() == Left)
				player.SetImage(L"./\\���� ���� �̹���\\â����_����â_����Ʈ(left).png");
			else
				player.SetImage(L"./\\���� ���� �̹���\\â����_����â_����Ʈ.png");
			for (int i = 0; i < player.GetFrame_Max(); i++) {
				player.SetOder(i, { 0, 0 }, -1);
			}
			player.SetOder(player.GetFrame_Max() - 1, { 0, 0 }, Purple_Spear);
			player.SetBaseDelay(4);
			player.SetSpeed(player.GetOder(0).speed.x, player.GetOder(0).speed.y);
			player.SetDamage(7);
			player.SetNeutralization(5);
			player.SetDestruction(0);

			if (Tripord[N_sktjsckd][0] == 1) {
				player.SetSeedDamage(player.GetSeedDamage() + 1);
			}
			else if (Tripord[N_sktjsckd][0] == 2) {
				player.SetRuncount(100);
			}
			else if (Tripord[N_sktjsckd][I_Tier1] == 3) {
				plusUltimate();
			}
			if (Tripord[N_sktjsckd][1] == 1) {
				onemore = true;
			}
			else if (Tripord[N_sktjsckd][1] == 2) {
				player.SetNamed_Damage(player.GetNamed_Damage() + 2);
			}
			else if (Tripord[N_sktjsckd][I_Tier2] == 3) {
				drawCard(false);
			}
			if (Tripord[N_sktjsckd][2] == 1) {
				//��Ÿ�����
			}


			break;

		default:
			break;
		}
		player.SetOder(player.GetFrame_Now(), { 0,0 }, -1);

		if (canNull) {
			handCard[clickSelect] = nullptr;
			for (int i = clickSelect; i < handCardCount - 1; i++)
			{
				handCard[i] = handCard[i + 1];
			}
			handCardCount--;
			deadCardCount++;
		}
	}
}

void resetCard() {
	for (int i = 0; i < cardCount; i++)
	{
		card[i]->isValid = true;
	}
	deadCardCount = 0;
	handCardCount = 0;
}
void Insert_Object(Node_Object* head, const int& object_type, const int& dir) {
	if (head == NULL)
		return;
	Node_Object* newNode;
	newNode = new Node_Object;
	newNode->data.SetType((ObjectType)object_type);
	if (object_type == Drop_Spear) {
		if (dir == Right) {
			newNode->data.SetRect(player.GetPoint().x + 150, player.GetPoint().y - 400, player.GetPoint().x + 300, player.GetPoint().y - 200);
		}
		else
			newNode->data.SetRect(player.GetPoint().x - 300, player.GetPoint().y - 400, player.GetPoint().x - 150, player.GetPoint().y - 200);
		newNode->data.SetImage(L"./\\���� ���� �̹���\\â����_û����_â������.png");
		newNode->data.SetSpeed(0, -10);
		newNode->data.SetBaseDelay(4);
	}
	else if (object_type == Meteor_Spear) {
		if (dir == Right) {
			newNode->data.SetRect(player.GetPoint().x + 50, player.GetPoint().y + 50, player.GetPoint().x + 150, player.GetPoint().y + 150);
			newNode->data.SetImage(L"./\\���� ���� �̹���\\��������ź_�����ϴ�â.png");
			newNode->data.SetSpeed(10, -10);

		}
		else {
			newNode->data.SetRect(player.GetPoint().x - 150, player.GetPoint().y + 50, player.GetPoint().x - 50, player.GetPoint().y + 150);
			newNode->data.SetImage(L"./\\���� ���� �̹���\\��������ź_�����ϴ�â(left).png");
			newNode->data.SetSpeed(-10, -10);
		}
		newNode->data.SetBaseDelay(5);

	}
	else if (object_type == Explosion) {
		if (dir == Right) {
			newNode->data.SetRect(player.GetPoint().x + 150, GROUNDYPOINT - 500, player.GetPoint().x + 550, GROUNDYPOINT);
			newNode->data.SetSpeed(0, 0);

		}
		else {
			newNode->data.SetRect(player.GetPoint().x - 550, GROUNDYPOINT - 500, player.GetPoint().x - 150, GROUNDYPOINT);
			newNode->data.SetSpeed(0, 0);
		}
		newNode->data.SetImage(L"./\\���� ���� �̹���\\��������ź_��������Ʈ.png");
		newNode->data.SetBaseDelay(4);

	}
	else if (object_type == Hurricane) {
		if (dir == Right) {
			newNode->data.SetRect(player.GetPoint().x + 100, GROUNDYPOINT - 300, player.GetPoint().x + 250, GROUNDYPOINT);
			newNode->data.SetSpeed(0, 0);

		}
		else {
			newNode->data.SetRect(player.GetPoint().x - 250, GROUNDYPOINT - 300, player.GetPoint().x - 100, GROUNDYPOINT);
			newNode->data.SetSpeed(0, 0);
		}
		newNode->data.SetImage(L"./\\���� ���� �̹���\\ȸ����.png");
		newNode->data.SetBaseDelay(4);
	}
	else if (object_type == Wall) {
		newNode->data.SetRect(player.GetPoint().x + 100, GROUNDYPOINT - 200, player.GetPoint().x + 250, GROUNDYPOINT);
		newNode->data.SetSpeed(0, 0);
		newNode->data.SetImage(L"./\\���� ���� �̹���\\��(right).png");
		newNode->data.SetBaseDelay(150);
		newNode->next = head->next;
		head->next = newNode;

		newNode = new Node_Object;
		newNode->data.SetType((ObjectType)object_type);
		newNode->data.SetRect(player.GetPoint().x - 250, GROUNDYPOINT - 200, player.GetPoint().x - 100, GROUNDYPOINT);
		newNode->data.SetSpeed(0, 0);
		newNode->data.SetImage(L"./\\���� ���� �̹���\\��.png");
		newNode->data.SetBaseDelay(150);
		newNode->next = head->next;
		head->next = newNode;
		return;
	}
	else if (object_type == SowrdLight) {
		if (dir == Right) {
			newNode->data.SetRect(player.GetPoint().x, GROUNDYPOINT - 100, player.GetPoint().x + 100, GROUNDYPOINT);
			newNode->data.SetSpeed(35, 0);
			newNode->data.SetImage(L"./\\���� ���� �̹���\\�˱�.png");
		}
		else {
			newNode->data.SetRect(player.GetPoint().x - 100, GROUNDYPOINT - 100, player.GetPoint().x, GROUNDYPOINT);
			newNode->data.SetSpeed(-35, 0);
			newNode->data.SetImage(L"./\\���� ���� �̹���\\�˱�(left).png");

		}
		newNode->data.SetBaseDelay(2);

	}
	else if (object_type == Rotation_Spear) {
		newNode->data.SetRect(player.GetPoint().x, GROUNDYPOINT - 100, player.GetPoint().x + 100, GROUNDYPOINT);
		newNode->data.SetSpeed(0, 0);
		newNode->data.SetImage(L"./\\���� ���� �̹���\\ȸ���ϴ�â.png");
		newNode->data.SetBaseDelay(2);
		newNode->data.SetAttacknums(3);
	}
	else if (object_type == Airborne_Spear) {
		newNode->data.SetRect(player.GetPoint().x - 25, GROUNDYPOINT - 150, player.GetPoint().x + 25, GROUNDYPOINT - 100);
		newNode->data.SetSpeed(player.GetSpeed().x, player.GetSpeed().y);
		newNode->data.SetImage(L"./\\���� ���� �̹���\\ȸ���ϴ�â.png");
		newNode->data.SetBaseDelay(2);
		newNode->data.SetAttacknums(3);
		newNode->data.SetDamage(player.GetDamage());
		newNode->data.SetNamed_Damage(player.GetNamed_Damage());
		newNode->data.SetNeutralization(player.GetNeutralization());
		newNode->data.SetDestruction(player.GetDestruction());
		newNode->next = head->next;
		head->next = newNode;

		newNode = new Node_Object;
		newNode->data.SetType((ObjectType)object_type);
		newNode->data.SetRect(player.GetPoint().x - 125, GROUNDYPOINT - 50, player.GetPoint().x - 75, GROUNDYPOINT);
		newNode->data.SetSpeed(player.GetSpeed().x, player.GetSpeed().y);
		newNode->data.SetImage(L"./\\���� ���� �̹���\\ȸ���ϴ�â.png");
		newNode->data.SetBaseDelay(2);
		newNode->data.SetAttacknums(3);
		newNode->data.SetDamage(player.GetDamage());
		newNode->data.SetNamed_Damage(player.GetNamed_Damage());
		newNode->data.SetNeutralization(player.GetNeutralization());
		newNode->data.SetDestruction(player.GetDestruction());
		newNode->next = head->next;
		head->next = newNode;

		newNode = new Node_Object;
		newNode->data.SetType((ObjectType)object_type);
		newNode->data.SetRect(player.GetPoint().x + 75, GROUNDYPOINT - 50, player.GetPoint().x + 125, GROUNDYPOINT);
		newNode->data.SetSpeed(player.GetSpeed().x, player.GetSpeed().y);
		newNode->data.SetImage(L"./\\���� ���� �̹���\\ȸ���ϴ�â.png");
		newNode->data.SetBaseDelay(2);
		newNode->data.SetAttacknums(3);
		newNode->data.SetDamage(player.GetDamage());
		newNode->data.SetNamed_Damage(player.GetNamed_Damage());
		newNode->data.SetNeutralization(player.GetNeutralization());
		newNode->data.SetDestruction(player.GetDestruction());
		newNode->next = head->next;
		head->next = newNode;
		return;
	}
	else if (object_type == Red_Spear) {
		newNode->data.SetBaseDelay(10);

		if (dir == Right) {
			if (Tripord[N_wjrfydvh][0] == 2)
				newNode->data.SetRect(player.GetPoint().x, GROUNDYPOINT - 100, player.GetPoint().x + 500, GROUNDYPOINT);
			else
				newNode->data.SetRect(player.GetPoint().x, GROUNDYPOINT - 100, player.GetPoint().x + 400, GROUNDYPOINT);
			newNode->data.SetSpeed(0, 0);
			newNode->data.SetImage(L"./\\���� ���� �̹���\\������ ��Ÿ.png");
			if (Tripord[N_wjrfydvh][2] == 1) {
				newNode->data.SetDamage(player.GetDamage());
				newNode->data.SetNamed_Damage(player.GetNamed_Damage());
				newNode->data.SetNeutralization(player.GetNeutralization());
				newNode->data.SetDestruction(player.GetDestruction());
				newNode->next = head->next;
				head->next = newNode;

				newNode = new Node_Object;
				newNode->data.SetType((ObjectType)object_type);
				newNode->data.SetBaseDelay(10);
				if (Tripord[N_wjrfydvh][0] == 2)
					newNode->data.SetRect(player.GetPoint().x, GROUNDYPOINT - 250, player.GetPoint().x + 500, GROUNDYPOINT - 150);
				else
					newNode->data.SetRect(player.GetPoint().x, GROUNDYPOINT - 250, player.GetPoint().x + 500, GROUNDYPOINT - 150);
				newNode->data.SetSpeed(0, 0);
				newNode->data.SetImage(L"./\\���� ���� �̹���\\������ ��Ÿ.png");
				newNode->data.SetDamage(player.GetDamage());
				newNode->data.SetNamed_Damage(player.GetNamed_Damage());
				newNode->data.SetNeutralization(player.GetNeutralization());
				newNode->data.SetDestruction(player.GetDestruction());
				newNode->next = head->next;
				head->next = newNode;
				return;
			}
		}
		else {
			if (Tripord[N_wjrfydvh][0] == 2)
				newNode->data.SetRect(player.GetPoint().x - 500, GROUNDYPOINT - 100, player.GetPoint().x, GROUNDYPOINT);
			else
				newNode->data.SetRect(player.GetPoint().x - 400, GROUNDYPOINT - 100, player.GetPoint().x, GROUNDYPOINT);
			newNode->data.SetSpeed(0, 0);
			newNode->data.SetImage(L"./\\���� ���� �̹���\\������ ��Ÿ(left).png");
			if (Tripord[N_wjrfydvh][2] == 1) {
				newNode->data.SetDamage(player.GetDamage());
				newNode->data.SetNamed_Damage(player.GetNamed_Damage());
				newNode->data.SetNeutralization(player.GetNeutralization());
				newNode->data.SetDestruction(player.GetDestruction());
				newNode->next = head->next;
				head->next = newNode;

				newNode = new Node_Object;
				newNode->data.SetType((ObjectType)object_type);
				newNode->data.SetBaseDelay(10);
				if (Tripord[N_wjrfydvh][0] == 2)
					newNode->data.SetRect(player.GetPoint().x - 500, GROUNDYPOINT - 250, player.GetPoint().x, GROUNDYPOINT - 150);
				else
					newNode->data.SetRect(player.GetPoint().x - 400, GROUNDYPOINT - 250, player.GetPoint().x, GROUNDYPOINT - 150);
				newNode->data.SetSpeed(0, 0);
				newNode->data.SetImage(L"./\\���� ���� �̹���\\������ ��Ÿ(left).png");
				newNode->data.SetDamage(player.GetDamage());
				newNode->data.SetNamed_Damage(player.GetNamed_Damage());
				newNode->data.SetNeutralization(player.GetNeutralization());
				newNode->data.SetDestruction(player.GetDestruction());
				newNode->next = head->next;
				head->next = newNode;
				return;
			}

		}
	}
	else if (object_type == Earthquake) {
		newNode->data.SetRect(player.GetPoint().x - 150, GROUNDYPOINT - 100, player.GetPoint().x + 150, GROUNDYPOINT);
		newNode->data.SetSpeed(0, 0);
		newNode->data.SetImage(L"./\\���� ���� �̹���\\����.png");
		newNode->data.SetBaseDelay(2);
		newNode->data.SetAttacknums(3);

	}
	else if (object_type == Flame_Zone) {
		newNode->data.SetRect(player.GetPoint().x - 150, GROUNDYPOINT - 100, player.GetPoint().x + 150, GROUNDYPOINT);
		newNode->data.SetSpeed(0, 0);
		newNode->data.SetImage(L"./\\���� ���� �̹���\\ȭ������.png");
		newNode->data.SetBaseDelay(2);
		newNode->data.SetAttacknums(3);

	}
	else if (object_type == Drop_Red_Spear) {
		newNode->data.SetRect(player.GetPoint().x - 250, GROUNDYPOINT - 500, player.GetPoint().x - 150, GROUNDYPOINT - 400);
		newNode->data.SetSpeed(0, -15);
		newNode->data.SetImage(L"./\\���� ���� �̹���\\�������� â.png");
		newNode->data.SetBaseDelay(32);
		newNode->data.SetDamage(player.GetDamage());
		newNode->data.SetNamed_Damage(player.GetNamed_Damage());
		newNode->data.SetNeutralization(player.GetNeutralization());
		newNode->data.SetDestruction(player.GetDestruction());
		newNode->next = head->next;
		head->next = newNode;

		for (int i = 0; i < 3; i++) {
			newNode = new Node_Object;
			newNode->data.SetType((ObjectType)object_type);
			if (i == 0)
				newNode->data.SetRect(player.GetPoint().x - 150, GROUNDYPOINT - 450, player.GetPoint().x - 50, GROUNDYPOINT - 350);
			else if (i == 1)
				newNode->data.SetRect(player.GetPoint().x + 50, GROUNDYPOINT - 450, player.GetPoint().x + 150, GROUNDYPOINT - 350);
			else if (i == 2)
				newNode->data.SetRect(player.GetPoint().x + 150, GROUNDYPOINT - 500, player.GetPoint().x + 250, GROUNDYPOINT - 400);
			newNode->data.SetSpeed(0, -15);
			newNode->data.SetImage(L"./\\���� ���� �̹���\\�������� â.png");
			newNode->data.SetBaseDelay(32);
			newNode->data.SetDamage(player.GetDamage());
			newNode->data.SetNamed_Damage(player.GetNamed_Damage());
			newNode->data.SetNeutralization(player.GetNeutralization());
			newNode->data.SetDestruction(player.GetDestruction());
			newNode->next = head->next;
			head->next = newNode;

		}
		return;
	}
	else if (object_type == Yellow_Spear) {
		newNode->data.SetBaseDelay(10);
		if (dir == Right) {
			if (Tripord[N_rhlddufvk][2] == 1)
				newNode->data.SetRect(player.GetPoint().x - 50, GROUNDYPOINT - 100, player.GetPoint().x + 400, GROUNDYPOINT);
			else
				newNode->data.SetRect(player.GetPoint().x - 50, GROUNDYPOINT - 100, player.GetPoint().x + 300, GROUNDYPOINT);
			newNode->data.SetImage(L"./\\���� ���� �̹���\\�����ĸ�Ÿ.png");

		}
		else {
			if (Tripord[N_rhlddufvk][2] == 1)
				newNode->data.SetRect(player.GetPoint().x - 400, GROUNDYPOINT - 100, player.GetPoint().x + 50, GROUNDYPOINT);
			else
				newNode->data.SetRect(player.GetPoint().x - 300, GROUNDYPOINT - 100, player.GetPoint().x + 50, GROUNDYPOINT);
			newNode->data.SetImage(L"./\\���� ���� �̹���\\�����ĸ�Ÿ(left).png");
		}
	}
	else if (object_type == Purple_Spear) {
		newNode->data.SetBaseDelay(10);
		if (dir == Right) {
			if (Tripord[N_sktjsckd][2] == 1)
				newNode->data.SetRect(player.GetPoint().x - 50, GROUNDYPOINT - 100, player.GetPoint().x + 250, GROUNDYPOINT);
			else
				newNode->data.SetRect(player.GetPoint().x - 50, GROUNDYPOINT - 100, player.GetPoint().x + 150, GROUNDYPOINT);
			newNode->data.SetImage(L"./\\���� ���� �̹���\\����â��Ÿ.png");
			if (Tripord[N_sktjsckd][2] == 2)
				newNode->data.SetSpeed(30, 0);
		}
		else {
			if (Tripord[N_sktjsckd][2] == 1)
				newNode->data.SetRect(player.GetPoint().x - 250, GROUNDYPOINT - 100, player.GetPoint().x + 50, GROUNDYPOINT);
			else
				newNode->data.SetRect(player.GetPoint().x - 150, GROUNDYPOINT - 100, player.GetPoint().x + 50, GROUNDYPOINT);
			newNode->data.SetImage(L"./\\���� ���� �̹���\\����â��Ÿ(left).png");
			if (Tripord[N_sktjsckd][2] == 2)
				newNode->data.SetSpeed(-30, 0);
		}

	}

	newNode->data.SetDamage(player.GetDamage());
	newNode->data.SetNamed_Damage(player.GetNamed_Damage());
	newNode->data.SetNeutralization(player.GetNeutralization());
	newNode->data.SetDestruction(player.GetDestruction());
	newNode->next = head->next;
	head->next = newNode;

}

void gameStart() {		//���� ����ȭ��
	static RECT deckText = { 135, 725, 185, 775 }, levelRect = { 150, WINHEIGHT - 20, 210, WINHEIGHT };
	static RECT moneyRect = { WINWIDTH - 100, 730 - 50, WINWIDTH, 900-100 };
	static time_t start;
	time_t end;

	TCHAR numStr[3], moneyStr[10];
	HBRUSH hBrush, oldBrush;
	int prevLevel = level;

	static int wait = 0, manaWait = 0, wave = 2;
	UpdatePlayer();


	//���콺�� ���� Ŀ�� ī��
	int selectCard = -1;

	hDC = GetDC(hWnd);
	if (hBit1 == NULL)
		hBit1 = CreateCompatibleBitmap(hDC, WINWIDTH, WINHEIGHT);
	memdc = CreateCompatibleDC(hDC);

	oldBit1 = (HBITMAP)SelectObject(memdc, hBit1);

	//��� �׸���
	BackGround[1].Draw(memdc, 0, 0, WINWIDTH, WINHEIGHT,
		0, 0, BackGround[1].GetWidth(), BackGround[1].GetHeight());
	if (castleMovement >= 1) {
		++castleMovement;
		int move = 4;
		move *= castleMovement % 2 ? 1 : -1;
		BackGround[0].Draw(memdc, 0 + move, 0, 259 + move, 635,
			0, 0, BackGround[0].GetWidth(), BackGround[0].GetHeight());
		if (castleMovement == 6) {
			castleMovement = 0;
		}
	}
	else{
		BackGround[0].Draw(memdc, 0, 0, 259, 635,
			0, 0, BackGround[0].GetWidth(), BackGround[0].GetHeight());
	}

	//��ü�� ���
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, 0, 650, 0 + ((double)castleHp / 1000) * 260, 670);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);

	//ī�带 �پ��� �� �ʱ�ȭ
	if (cardCount == deadCardCount) {
		resetCard();
		cardDrawing = true;
		wait = 0;
	}

	//������ ���â
	ultiImg.Draw(memdc, WINWIDTH - 150, 10, 100, 100,
		0, 0, 77, 77);
	hBrush = CreateSolidBrush(RGB(255, 215, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, WINWIDTH - 150, 100, WINWIDTH - 150 + ((double)ultimate / ULTIMATESKILL) * 100, 110);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);


	//���ʾƷ� ī�� ��
	Deck.Draw(memdc, -44, 750, 204, 300,
		0, 0, Deck.GetWidth(), Deck.GetHeight());
	//���� ī�� ���� ��
	Ellipse(memdc, deckText);
	swprintf_s(numStr, L"%d", cardCount - (handCardCount + deadCardCount));
	DrawText(memdc, numStr, lstrlen(numStr), &deckText, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	//����ġ�� ���
	hBrush = CreateSolidBrush(RGB(0, 255, 255));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, 170, WINHEIGHT - ((double)experience / experienceBar[level]) * 100, 190, WINHEIGHT );
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);

	//�������
	swprintf_s(numStr, L"%d", level + 1);
	Rectangle(memdc, 150, WINHEIGHT - 20, 210, WINHEIGHT );
	DrawText(memdc, numStr, lstrlen(numStr), &levelRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);


	//���� ���
	{
		//�� ����
		for (int i = 0; i < maxMana; i++)
		{
			manaImg[1].Draw(memdc, 1600 - 55 * ((i % 5) + 1), 900 - 55 * ((i / 5) + 1), 50, 50, 0, 0, manaImg[1].GetWidth(), manaImg[1].GetHeight());
		}
		//�� ����
		for (int i = 0; i < manaCount; i++)
		{
			manaImg[0].Draw(memdc, 1600 - 55 * ((i % 5) + 1), 900 - 55 * ((i / 5) + 1), 50, 50, 0, 0, manaImg[0].GetWidth(), manaImg[0].GetHeight());
		}
	}


	if (cardDrawing) {
		if (cardCount < 10) {
			startShop(hDC, memdc);
		}
		else {
			//���ۿ� 4�� �̱�
			for (int i = 0; i < 4; i++) {
				drawCard();
			}
			cardDrawing = false;
			start = clock();

			//4���� �ڸ���ġ
			setCardPoint();
		}
	}
	else {
		printf("wait : %d\n", wait);
		end = clock();
		if (((double)end - start)/CLOCKS_PER_SEC > 1) {
			if (manaCount < 10) {
				manaCount++;
				start = clock();
			}
		}

		//���콺�� ī�� ���� ó��
		for (int i = 0; i < handCardCount; i++)
		{
			if (mx > handCard[i]->point.x && mx < handCard[i]->point.x + CARDMINIWIDTH\
				&& my > handCard[i]->point.y && my < handCard[i]->point.y + CARDMINIHEIGHT)
			{
				if (isClick) {
					clickSelect = i;
					if (prevCardPoint.x == -1)
						prevCardPoint = handCard[i]->point;
				}
				else
					selectCard = i;
				break;
			}
		}

		//��ο� Ÿ�̸�
		if (cardCount - (handCardCount + deadCardCount) != 0) {
			if (++wait % CARDDRAWTERM == 0) {
				if (handCardCount < 7 && clickSelect == -1) {
					drawCard();
					setCardPoint();
				}
				else
					--wait;
			}
		}


		updateEnemy(wave);
		switch (wave)
		{
			case 3:
				papyrus.update();
				papyrus.draw();
			case 2:
				for (int i = 0; i < MAXBAT; i++)
				{
					if (bat[i] != nullptr) {
						bat[i]->update();
						bat[i]->draw();
					}
				}
			case 1:
				for (int i = 0; i < MAXWOLF; i++)
				{
					if (wolf[i] != nullptr) {
						wolf[i]->update();
						wolf[i]->draw();
					}
				}
				break;
		default:
			break;
		}

		for (int i = 0; i < 2; i++)
		{
			if (bone[i] != nullptr) {
				if (bone[i]->canDie) {
					if (bone[i]->num == 0)
						papyrus.status = UP_Move;
					else
						papyrus.status = P_Move;
					delete bone[i];
					bone[i] = nullptr;
				}
				else {
					bone[i]->update();
					bone[i]->draw();
				}
			}
		}

		for (int i = 0; i < 15; i++)
		{
			if (miniBone[i] != nullptr) {
				if (miniBone[i]->canDie) {
					delete miniBone[i];
					miniBone[i] = nullptr;
				}
				else {
					miniBone[i]->update();
					miniBone[i]->draw();
				}
			}
		}

		// �÷��̾� ���
		player.Draw(memdc);

		// ��ų �߰� ������Ʈ ���
		for (Node_Object* p = head; p->next != NULL; p = p->next) {
			p->next->data.Draw(memdc);
		}
		//��� ���
		{
			HFONT hFont, oldFont;
			SetTextColor(memdc, RGB(241, 242, 70));
			SetBkMode(memdc, TRANSPARENT);
			hFont = CreateFont(75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Papyrus");
			oldFont = (HFONT)SelectObject(memdc, hFont);
			swprintf_s(moneyStr, 10, L"%dG\n", money);
			DrawText(memdc, moneyStr, lstrlen(moneyStr), &moneyRect, DT_RIGHT | DT_BOTTOM | DT_SINGLELINE);
			SelectObject(memdc, oldFont); DeleteObject(hFont);
			SetTextColor(memdc, RGB(255, 255, 255));
		}


		//ī�� ���
		for (int i = 0; i < handCardCount; i++) {
			if (i == selectCard)
				handCard[i]->closeDraw();
			else if (i == clickSelect)
				handCard[i]->dragDraw();
			else
				handCard[i]->handDraw();
		}

		if (prevLevel != level) {
			showShop(memdc);
		}
		//static bool test = true;
		//if (test) {
		//	test = false;
		//}
	}

	SelectObject(memdc, oldBit1); DeleteDC(memdc);
	ReleaseDC(hWnd, hDC);
}

void setCardTripod(int cardEnum) {
	for (int i = 0; i < cardCount; i++)
	{
		if(card[i]->cardname == cardEnum){
			card[i]->__init__();
		}
	}
}

void hitCastle(int damage) {
	castleMovement = 1;
	castleHp -= damage;
}

void getExp(int experi) {
	if (experi + experience > experienceBar[level]) {
		level++;
		if (experi + experience - experienceBar[level - 1] >= experienceBar[level]) {
			getExp(experi + experience - experienceBar[level - 1]);
		}
		else {
			if (experi > experience)
				experience = experi - experience;
			else
				experience = experience - experi;
		}
	}
	else if (experi + experience == experienceBar[level]) {
		experience = 0;
		level++;
	}
	else {
		experience += experi;
	}
}

void getMoney(int _money) {
	money += _money;
}

void plusUltimate() {
	ultimate += 10;
	if (ultimate > ULTIMATESKILL)
		ultimate = ULTIMATESKILL;
}

void updateEnemy(int& wave) {
	static int timerCount = 0;
	static int spawnTerm = 90;
	if (wave == 1) {
		if (++timerCount % spawnTerm == 0) {
			for (int i = 0; i < MAXWOLF; i++)
			{
				if (wolf[i] == nullptr) {
					wolf[i] = new Wolf;
					if (--spawnTerm < 60) {
						wave++;
						timerCount = 0;
						spawnTerm = 90;
					}
					break;
				}
			}
		}
	}
	else if (wave == 2) {
		if (++timerCount % spawnTerm == 0) {
			if (getRand(2)) {
				for (int i = 0; i < MAXWOLF; i++)
				{
					if (wolf[i] == nullptr) {
						wolf[i] = new Wolf;
						if (--spawnTerm < 600) {
							wave++;
							timerCount = 0;
							spawnTerm = 90;
							papyrus = Papyrus();
						}
						break;
					}
				}
			}
			else {
				for (int i = 0; i < MAXBAT; i++)
				{
					if (bat[i] == nullptr) {
						bat[i] = new Bat;
						if (--spawnTerm < 600) {
							wave++;
							timerCount = 0;
							spawnTerm = 90;
							papyrus = Papyrus();
						}
						break;
					}
				}
			}
		}
	}
	else {
		
	}
}