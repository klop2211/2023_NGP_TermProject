#include "stdafx.h"
#include "Shop.h"
#include "Random.h"
#include "OtherCard.h"
#include "Player.h"

Shop::Shop(HWND& m_hWnd, HINSTANCE& Inst) :
	m_hWnd(m_hWnd),
	m_hInst(Inst)
{
	m_cImg.Load(TEXT("상점관련\\상점UI.png"));
	m_cBuyButtonImg.Load(TEXT("상점관련\\상점버튼.png"));

	m_hFreeButton = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼Free.bmp"), 
	IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
}

Shop::~Shop()
{
	m_cImg.Destroy();
	m_cBuyButtonImg.Destroy();
}

void Shop::StartShop(HDC& memdc)
{
	HFONT hFont, oldFont;
	CImage m_cBuyButtonImg, tri;
	HDC bitDC;
	HBITMAP hBit, oldBit;

	RECT textRect;

	m_cImg.Draw(memdc, 0, 0, WINWIDTH, WINHEIGHT,
		0, 0, WINWIDTH, WINHEIGHT);

	// SetRandValue();

	// 선택된 카드들 상점에 띄우기
	hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"");
	oldFont = (HFONT)SelectObject(memdc, hFont);
	SetBkMode(memdc, TRANSPARENT);
	SetTextColor(memdc, RGB(255, 255, 255));
	for (int i = 0; i < 3; i++)
	{
		textRect = { 475 + 300 * i, 259, 474 + 300 * i + 75,  259 + 75 };

		m_cSkills[i].Draw(memdc, 474 + 300 * i, 360, 75, 75, 0, 0, 100, 100);
		DrawText(memdc, m_tStr[i], lstrlen(m_tStr[i]), &textRect, DT_BOTTOM | DT_SINGLELINE | DT_CENTER);
	}

	SendMessage(m_hButton[0], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hFreeButton);
	SendMessage(m_hButton[1], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hFreeButton);
	SendMessage(m_hButton[2], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hFreeButton);

	SelectObject(memdc, oldFont); DeleteObject(hFont);

}

void Shop::ShowShop(HDC& memdc, Player* player)
{
	CImage buyButton, skill;// , tri;
	HWND hButton[4];
	HDC bitDC;
	HBITMAP hBit[4] = { NULL };// oldBit;
	static RECT textRect[3] = { {425,450,600,600},
								{725,450,900,600},
								{1025,450,1200,600} };

	m_cImg.Draw(memdc, 0, 0, WINWIDTH, WINHEIGHT,
		0, 0, WINWIDTH, WINHEIGHT);
	//buyButton.Load(TEXT("상점관련//상점버튼.png"));
	hButton[0] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 450, 650, 135, 55,
		m_hWnd, (HMENU)IDC_BUTTON_BUY1, m_hInst, NULL);
	hButton[1] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 750, 650, 135, 55,
		m_hWnd, (HMENU)IDC_BUTTON_BUY2, m_hInst, NULL);
	hButton[2] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 1050, 650, 135, 55,
		m_hWnd, (HMENU)IDC_BUTTON_BUY3, m_hInst, NULL);
	hButton[3] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 1090, 130, 135, 55,
		m_hWnd, (HMENU)IDC_BUTTON_BUY4, m_hInst, NULL);
	hBit[3] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//나가기.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	SendMessage(hButton[3], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBit[3]);

	//m_iRandValue[0] = RandomGen::GetRand(CARDVARIABLE);
	for (int i = 0; i < 3; i++)
	{
		bool keepIn = true;
		while (keepIn) {
			keepIn = false;
			m_iRandValue[i] = RandomGen::GetRand(CARDVARIABLE);
			for (int j = 0; j < 3; j++)
			{
				if ((i != j && m_iRandValue[i] == m_iRandValue[j]))
					keepIn = true;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		int rand10 = 99;
		int triRand;

		if (player->GetCardCount() < 30)
			rand10 = RandomGen::GetRand(100);

		switch (m_iRandValue[i])
		{
		case (int)CardName::N_rhlddufvk:
			skill.Load(TEXT(".//카드관련//스킬초상화//굉열파.png"));
			if (rand10 >= CARDSPAWNRAND) {
				int* tripord = player->GetTripord()[(int)CardName::N_rhlddufvk];
				Rhlddufvk* temp = new Rhlddufvk(tripord);
				if (tripord[3] == 0 || tripord[(int)TriIndex::I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					m_iCardPrice[i] = 5;
				}
				else if (tripord[1] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(2) + 1;
					tripord[2] = m_iTriNum[i];
					temp->setTier3();
					tripord[2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr(3), lstrlen(temp->GetStr(3)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 30;
				}
				else if (tripord[0] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier2] = m_iTriNum[i];
					temp->setTier2();
					tripord[(int)TriIndex::I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier2), lstrlen(temp->GetStr((int)CardRect::R_tier2)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 20;
				}
				else {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier1] = m_iTriNum[i];
					temp->setTier1();
					tripord[(int)TriIndex::I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier1), lstrlen(temp->GetStr((int)CardRect::R_tier1)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				m_iCardPrice[i] = 5;
			}
			break;
		case (int)CardName::N_sktjsckd:
			skill.Load(TEXT(".//카드관련//스킬초상화//나선창.png"));
			if (rand10 >= CARDSPAWNRAND) {
				int* tripord = player->GetTripord()[(int)CardName::N_sktjsckd];
				Sktjsckd* temp = new Sktjsckd(tripord);
				if (tripord[3] == 0 || tripord[(int)TriIndex::I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					m_iCardPrice[i] = 5;
				}
				else if (tripord[1] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(2) + 1;
					tripord[2] = m_iTriNum[i];
					temp->setTier3();
					tripord[2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr(3), lstrlen(temp->GetStr(3)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 30;
				}
				else if (tripord[0] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier2] = m_iTriNum[i];
					temp->setTier2();
					tripord[(int)TriIndex::I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier2), lstrlen(temp->GetStr((int)CardRect::R_tier2)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 20;
				}
				else {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier1] = m_iTriNum[i];
					temp->setTier1();
					tripord[(int)TriIndex::I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier1), lstrlen(temp->GetStr((int)CardRect::R_tier1)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				m_iCardPrice[i] = 5;
			}
			break;
		case (int)CardName::N_dbtjdrkdcjs:
			skill.Load(TEXT(".//카드관련//스킬초상화//유성강천.png"));
			if (rand10 >= CARDSPAWNRAND) {
				int* tripord = player->GetTripord()[(int)CardName::N_dbtjdrkdcjs];
				Dbtjdrkdcjs* temp = new Dbtjdrkdcjs(tripord);
				if (tripord[3] == 0 || tripord[(int)TriIndex::I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					m_iCardPrice[i] = 5;
				}
				else if (tripord[1] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(2) + 1;
					tripord[2] = m_iTriNum[i];
					temp->setTier3();
					tripord[2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr(3), lstrlen(temp->GetStr(3)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 30;
				}
				else if (tripord[0] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier2] = m_iTriNum[i];
					temp->setTier2();
					tripord[(int)TriIndex::I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier2), lstrlen(temp->GetStr((int)CardRect::R_tier2)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 20;
				}
				else {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier1] = m_iTriNum[i];
					temp->setTier1();
					tripord[(int)TriIndex::I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier1), lstrlen(temp->GetStr((int)CardRect::R_tier1)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				m_iCardPrice[i] = 5;
			}
			break;
		case (int)CardName::N_wjrfydvh:
			skill.Load(TEXT(".//카드관련//스킬초상화//적룡포.png"));
			if (rand10 >= CARDSPAWNRAND) {
				int* tripord = player->GetTripord()[(int)CardName::N_wjrfydvh];
				Wjrfydvh* temp = new Wjrfydvh(tripord);
				if (tripord[3] == 0 || tripord[(int)TriIndex::I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					m_iCardPrice[i] = 5;
				}
				else if (tripord[1] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(2) + 1;
					tripord[2] = m_iTriNum[i];
					temp->setTier3();
					tripord[2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr(3), lstrlen(temp->GetStr(3)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 30;
				}
				else if (tripord[0] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier2] = m_iTriNum[i];
					temp->setTier2();
					tripord[(int)TriIndex::I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier2), lstrlen(temp->GetStr((int)CardRect::R_tier2)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 20;
				}
				else {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier1] = m_iTriNum[i];
					temp->setTier1();
					tripord[(int)TriIndex::I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier1), lstrlen(temp->GetStr((int)CardRect::R_tier1)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				m_iCardPrice[i] = 5;
			}
			break;
		case (int)CardName::N_aodfyddufvk:
			skill.Load(TEXT(".//카드관련//스킬초상화//맹룡열파.png"));
			if (rand10 >= CARDSPAWNRAND) {
				int* tripord = player->GetTripord()[(int)CardName::N_aodfyddufvk];
				Aodfyddufvk* temp = new Aodfyddufvk(tripord);
				if (tripord[3] == 0 || tripord[(int)TriIndex::I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					m_iCardPrice[i] = 5;
				}
				else if (tripord[1] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(2) + 1;
					tripord[2] = m_iTriNum[i];
					temp->setTier3();
					tripord[2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr(3), lstrlen(temp->GetStr(3)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 30;
				}
				else if (tripord[0] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier2] = m_iTriNum[i];
					temp->setTier2();
					tripord[(int)TriIndex::I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier2), lstrlen(temp->GetStr((int)CardRect::R_tier2)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 20;
				}
				else {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier1] = m_iTriNum[i];
					temp->setTier1();
					tripord[(int)TriIndex::I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier1), lstrlen(temp->GetStr((int)CardRect::R_tier1)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				m_iCardPrice[i] = 5;
			}
			break;
		case (int)CardName::N_qksdnjftja:
			skill.Load(TEXT(".//카드관련//스킬초상화//반월섬.png"));
			if (rand10 >= CARDSPAWNRAND) {
				int* tripord = player->GetTripord()[(int)CardName::N_qksdnjftja];
				Qksdnjftja* temp = new Qksdnjftja(tripord);
				if (tripord[3] == 0 || tripord[(int)TriIndex::I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					m_iCardPrice[i] = 5;
				}
				else if (tripord[1] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(2) + 1;
					tripord[2] = m_iTriNum[i];
					temp->setTier3();
					tripord[2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr(3), lstrlen(temp->GetStr(3)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 30;
				}
				else if (tripord[0] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier2] = m_iTriNum[i];
					temp->setTier2();
					tripord[(int)TriIndex::I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier2), lstrlen(temp->GetStr((int)CardRect::R_tier2)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 20;
				}
				else {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier1] = m_iTriNum[i];
					temp->setTier1();
					tripord[(int)TriIndex::I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier1), lstrlen(temp->GetStr((int)CardRect::R_tier1)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				m_iCardPrice[i] = 5;
			}
			break;
		case (int)CardName::N_dusghkstja:
			skill.Load(TEXT(".//카드관련//스킬초상화//연환섬.png"));
			if (rand10 >= CARDSPAWNRAND) {
				int* tripord = player->GetTripord()[(int)CardName::N_dusghkstja];
				Dusghkstja* temp = new Dusghkstja(tripord);
				if (tripord[3] == 0 || tripord[(int)TriIndex::I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					m_iCardPrice[i] = 5;
				}
				else if (tripord[1] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(2) + 1;
					tripord[2] = m_iTriNum[i];
					temp->setTier3();
					tripord[2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr(3), lstrlen(temp->GetStr(3)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 30;
				}
				else if (tripord[0] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier2] = m_iTriNum[i];
					temp->setTier2();
					tripord[(int)TriIndex::I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier2), lstrlen(temp->GetStr((int)CardRect::R_tier2)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 20;
				}
				else {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier1] = m_iTriNum[i];
					temp->setTier1();
					tripord[(int)TriIndex::I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier1), lstrlen(temp->GetStr((int)CardRect::R_tier1)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				m_iCardPrice[i] = 5;
			}
			break;
		case (int)CardName::N_cjdfydwls:
			skill.Load(TEXT(".//카드관련//스킬초상화//청룡진.png"));
			if (rand10 >= CARDSPAWNRAND) {
				int* tripord = player->GetTripord()[(int)CardName::N_cjdfydwls];
				Cjdfydwls* temp = new Cjdfydwls(tripord);
				if (tripord[3] == 0 || tripord[(int)TriIndex::I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					m_iCardPrice[i] = 5;
				}
				else if (tripord[1] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(2) + 1;
					tripord[2] = m_iTriNum[i];
					temp->setTier3();
					tripord[2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr(3), lstrlen(temp->GetStr(3)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 30;
				}
				else if (tripord[0] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier2] = m_iTriNum[i];
					temp->setTier2();
					tripord[(int)TriIndex::I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier2), lstrlen(temp->GetStr((int)CardRect::R_tier2)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 20;
				}
				else {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier1] = m_iTriNum[i];
					temp->setTier1();
					tripord[(int)TriIndex::I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier1), lstrlen(temp->GetStr((int)CardRect::R_tier1)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				m_iCardPrice[i] = 5;
			}
			break;
		case (int)CardName::N_cjdfydcnftn:
			skill.Load(TEXT(".//카드관련//스킬초상화//청룡출수.png"));
			if (rand10 >= CARDSPAWNRAND) {
				int* tripord = player->GetTripord()[(int)CardName::N_cjdfydcnftn];
				Cjdfydcnftn* temp = new Cjdfydcnftn(tripord);
				if (tripord[3] == 0 || tripord[(int)TriIndex::I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					m_iCardPrice[i] = 5;
				}
				else if (tripord[1] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(2) + 1;
					tripord[2] = m_iTriNum[i];
					temp->setTier3();
					tripord[2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr(3), lstrlen(temp->GetStr(3)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 30;
				}
				else if (tripord[0] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier2] = m_iTriNum[i];
					temp->setTier2();
					tripord[(int)TriIndex::I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier2), lstrlen(temp->GetStr((int)CardRect::R_tier2)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 20;
				}
				else {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier1] = m_iTriNum[i];
					temp->setTier1();
					tripord[(int)TriIndex::I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier1), lstrlen(temp->GetStr((int)CardRect::R_tier1)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				m_iCardPrice[i] = 5;
			}
			break;
		case (int)CardName::N_ghltjsckd:
			skill.Load(TEXT(".//카드관련//스킬초상화//회선창.png"));
			if (rand10 >= CARDSPAWNRAND) {
				int* tripord = player->GetTripord()[(int)CardName::N_ghltjsckd];
				Ghltjsckd* temp = new Ghltjsckd(tripord);
				if (tripord[3] == 0 || tripord[(int)TriIndex::I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					m_iCardPrice[i] = 5;
				}
				else if (tripord[1] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(2) + 1;
					tripord[2] = m_iTriNum[i];
					temp->setTier3();
					tripord[2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr(3), lstrlen(temp->GetStr(3)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 30;
				}
				else if (tripord[0] != 0) {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier2] = m_iTriNum[i];
					temp->setTier2();
					tripord[(int)TriIndex::I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier2), lstrlen(temp->GetStr((int)CardRect::R_tier2)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 20;
				}
				else {
					m_iTriNum[i] = RandomGen::GetRand(3) + 1;
					tripord[(int)TriIndex::I_Tier1] = m_iTriNum[i];
					temp->setTier1();
					tripord[(int)TriIndex::I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->GetImg()[(int)CardRect::R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->GetStr((int)CardRect::R_tier1), lstrlen(temp->GetStr((int)CardRect::R_tier1)), &textRect[i], DT_LEFT | DT_WORDBREAK);
					m_iCardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(m_hInst, TEXT("상점관련//상점버튼5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				m_iCardPrice[i] = 5;
			}
			break;
			//case (int)CardName::N_dmsgkdbtjdxks:
			//	skill.Load(TEXT(".//카드관련//스킬초상화//은하유성탄.png"));
			//	skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
			//		0, 0, 100, 100);
			//	break;
		default:
			break;
		}
		skill.Destroy();
		SendMessage(hButton[i], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBit[i]);
	}


	//SendMessage(hButton[0], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBit);
	//SendMessage(hButton[1], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBit);
	//SendMessage(hButton[2], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBit);
}

void Shop::OnProcessingCommandMessage(HWND hWnd, WPARAM wParam, Player* player)
{
	bool startTimer = false;
	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_BUY1:
		if (player->GetMoney() >= m_iCardPrice[0]) {
			startTimer = true;
			if (m_iCardPrice[0] == 5 || m_iCardPrice[0] == 0) {
				player->GetTripord()[m_iRandValue[0]][3] = 1;
				player->MakeCard(m_iRandValue[0]);
			}
			else {
				if (m_iCardPrice[0] == 10)
					player->GetTripord()[m_iRandValue[0]][0] = m_iTriNum[0];
				else if (m_iCardPrice[0] == 20)
					player->GetTripord()[m_iRandValue[0]][1] = m_iTriNum[0];
				else if (m_iCardPrice[0] == 30)
					player->GetTripord()[m_iRandValue[0]][2] = m_iTriNum[0];

				player->SetCardTripod(m_iRandValue[0]);
			}
			player->MinusMoney(m_iCardPrice[0]);

			SetRandValue();
		}
		break;
	case IDC_BUTTON_BUY2:
		if (player->GetMoney() >= m_iCardPrice[1]) {
			startTimer = true;
			if (m_iCardPrice[1] == 5 || m_iCardPrice[1] == 0) {
				player->GetTripord()[m_iRandValue[1]][3] = 1;
				player->MakeCard(m_iRandValue[1]);
			}
			else {
				if (m_iCardPrice[1] == 10)
					player->GetTripord()[m_iRandValue[1]][0] = m_iTriNum[1];
				else if (m_iCardPrice[1] == 20)
					player->GetTripord()[m_iRandValue[1]][1] = m_iTriNum[1];
				else if (m_iCardPrice[1] == 30)
					player->GetTripord()[m_iRandValue[1]][2] = m_iTriNum[1];

				player->SetCardTripod(m_iRandValue[1]);
			}
			player->MinusMoney(m_iCardPrice[1]);

			SetRandValue();
		}
		break;
	case IDC_BUTTON_BUY3:
		if (player->GetMoney() >= m_iCardPrice[2]) {
			startTimer = true;
			if (m_iCardPrice[2] == 5 || m_iCardPrice[2] == 0) {
				player->GetTripord()[m_iRandValue[2]][3] = 1;
				player->MakeCard(m_iRandValue[2]);
			}
			else {
				if (m_iCardPrice[2] == 10)
					player->GetTripord()[m_iRandValue[2]][0] = m_iTriNum[2];
				else if (m_iCardPrice[2] == 20)
					player->GetTripord()[m_iRandValue[2]][1] = m_iTriNum[2];
				else if (m_iCardPrice[2] == 30)
					player->GetTripord()[m_iRandValue[2]][2] = m_iTriNum[2];

				player->SetCardTripod(m_iRandValue[2]);
			}
			player->MinusMoney(m_iCardPrice[2]);

			SetRandValue();
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
	}
}

void Shop::SetRandValue()
{

	for (int i = 0; i < 3; i++)
	{
		m_iRandValue[i] = -1;
		m_iCardPrice[i] = 0;
		m_cSkills[i].Destroy();
	}

	// 상점에 띄울 카드 3개 선택
	m_iRandValue[0] = RandomGen::GetRand(CARDVARIABLE);
	for (int i = 1; i < 3; i++)
	{
		bool keepIn = true;
		while (keepIn) {
			keepIn = false;
			m_iRandValue[i] = RandomGen::GetRand(CARDVARIABLE);
			for (int j = 0; j < 3; j++)
			{
				if (i != j && m_iRandValue[i] == m_iRandValue[j])
					keepIn = true;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		switch (m_iRandValue[i])
		{
		case (int)CardName::N_rhlddufvk:
			m_cSkills[i].Load(TEXT("카드관련//스킬초상화//굉열파.png"));
			wsprintf(m_tStr[i], L"굉열파");
			break;
		case (int)CardName::N_sktjsckd:
			m_cSkills[i].Load(TEXT("카드관련//스킬초상화//나선창.png"));
			wsprintf(m_tStr[i], L"나선창");
			break;
		case (int)CardName::N_dbtjdrkdcjs:
			m_cSkills[i].Load(TEXT("카드관련//스킬초상화//유성강천.png"));
			wsprintf(m_tStr[i], L"유성강천");
			break;
		case (int)CardName::N_wjrfydvh:
			m_cSkills[i].Load(TEXT("카드관련//스킬초상화//적룡포.png"));
			wsprintf(m_tStr[i], L"적룡포");
			break;
		case (int)CardName::N_aodfyddufvk:
			m_cSkills[i].Load(TEXT("카드관련//스킬초상화//맹룡열파.png"));
			wsprintf(m_tStr[i], L"맹룡열파");
			break;
		case (int)CardName::N_qksdnjftja:
			m_cSkills[i].Load(TEXT("카드관련//스킬초상화//반월섬.png"));
			wsprintf(m_tStr[i], L"반월섬");
			break;
		case (int)CardName::N_dusghkstja:
			m_cSkills[i].Load(TEXT("카드관련//스킬초상화//연환섬.png"));
			wsprintf(m_tStr[i], L"연환섬");
			break;
		case (int)CardName::N_cjdfydwls:
			m_cSkills[i].Load(TEXT("카드관련//스킬초상화//청룡진.png"));
			wsprintf(m_tStr[i], L"청룡진");
			break;
		case (int)CardName::N_cjdfydcnftn:
			m_cSkills[i].Load(TEXT("카드관련//스킬초상화//청룡출수.png"));
			wsprintf(m_tStr[i], L"청룡출수");
			break;
		case (int)CardName::N_ghltjsckd:
			m_cSkills[i].Load(TEXT("카드관련//스킬초상화//회선창.png"));
			wsprintf(m_tStr[i], L"회선창");
			break;
		default:
			break;
		}
	}

	m_hButton[0] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 450, 650, 135, 55,
		m_hWnd, (HMENU)IDC_BUTTON_BUY1, m_hInst, NULL);
	m_hButton[1] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 750, 650, 135, 55,
		m_hWnd, (HMENU)IDC_BUTTON_BUY2, m_hInst, NULL);
	m_hButton[2] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 1050, 650, 135, 55,
		m_hWnd, (HMENU)IDC_BUTTON_BUY3, m_hInst, NULL);
}
