#pragma once

void startShop(HDC hDC, HDC memdc) {
	KillTimer(hWnd, 0);
	HFONT hFont, oldFont;
	CImage shop, buyButton, skill, tri;
	HWND hButton[3];
	HDC bitDC;
	HBITMAP hBit, oldBit;

	RECT textRect;
	
	for (int i = 0; i < 3; i++)
	{
		randValue[i] = -1;
		cardPrice[i] = 0;
	}
	
	shop.Load(TEXT(".//��������//����UI.png"));
	shop.Draw(memdc, 0, 0, WINWIDTH, WINHEIGHT,
		0, 0, WINWIDTH, WINHEIGHT);

	randValue[0] = getRand(CARDVARIABLE);
	for (int i = 1; i < 3; i++)
	{
		bool keepIn = true;
		while (keepIn) {
			keepIn = false;
			randValue[i] = getRand(CARDVARIABLE);
			for (int j = 0; j < 3; j++)
			{
				if (i != j && randValue[i] == randValue[j])
					keepIn = true;
			}
		}
	}

	hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"");
	oldFont = (HFONT)SelectObject(memdc, hFont);
	SetBkMode(memdc, TRANSPARENT);
	SetTextColor(memdc, RGB(255, 255, 255));
	for (int i = 0; i < 3; i++)
	{
		textRect = { 475 + 300 * i, 259, 474 + 300 * i + 75,  259 + 75 };
		switch (randValue[i])
		{
			case N_rhlddufvk:
				skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������.png"));
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				DrawText(memdc, L"������", lstrlen(L"������"), &textRect, DT_BOTTOM | DT_SINGLELINE | DT_CENTER);
				break;
			case N_sktjsckd:
				skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//����â.png"));
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				DrawText(memdc, L"����â", lstrlen(L"����â"), &textRect, DT_BOTTOM | DT_SINGLELINE | DT_CENTER);
				break;
			case N_dbtjdrkdcjs:
				skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������õ.png"));
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				DrawText(memdc, L"������õ", lstrlen(L"������õ"), &textRect, DT_BOTTOM | DT_SINGLELINE | DT_CENTER);
				break;
			case N_wjrfydvh:
				skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������.png"));
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				DrawText(memdc, L"������", lstrlen(L"������"), &textRect, DT_BOTTOM | DT_SINGLELINE | DT_CENTER);
				break;
			case N_aodfyddufvk:
				skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//�ͷ濭��.png"));
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				DrawText(memdc, L"�ͷ濭��", lstrlen(L"�ͷ濭��"), &textRect, DT_BOTTOM | DT_SINGLELINE | DT_CENTER);
				break;
			case N_qksdnjftja:
				skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//�ݿ���.png"));
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				DrawText(memdc, L"�ݿ���", lstrlen(L"�ݿ���"), &textRect, DT_BOTTOM | DT_SINGLELINE | DT_CENTER);
				break;
			case N_dusghkstja:
				skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//��ȯ��.png"));
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				DrawText(memdc, L"��ȯ��", lstrlen(L"��ȯ��"), &textRect, DT_BOTTOM | DT_SINGLELINE | DT_CENTER);
				break;
			case N_cjdfydwls:
				skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//û����.png"));
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				DrawText(memdc, L"û����", lstrlen(L"û����"), &textRect, DT_BOTTOM | DT_SINGLELINE | DT_CENTER);
				break;
			case N_cjdfydcnftn:
				skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//û�����.png"));
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				DrawText(memdc, L"û�����", lstrlen(L"û�����"), &textRect, DT_BOTTOM | DT_SINGLELINE | DT_CENTER);
				break;
			case N_ghltjsckd:
				skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//ȸ��â.png"));
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				DrawText(memdc, L"ȸ��â", lstrlen(L"ȸ��â"), &textRect, DT_BOTTOM | DT_SINGLELINE | DT_CENTER);
				break;
			/*case N_dmsgkdbtjdxks:
				skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//��������ź.png"));
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				break;*/
		default:
			break;
		}
		skill.Destroy();
	}

	buyButton.Load(TEXT(".//��������//������ư.png"));
	hBit = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ưFree.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	hButton[0] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 450, 650, 135, 55,
		hWnd, (HMENU)IDC_BUTTON_BUY1, g_hlnst, NULL);
	hButton[1] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 750, 650, 135, 55,
		hWnd, (HMENU)IDC_BUTTON_BUY2, g_hlnst, NULL);
	hButton[2] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 1050, 650, 135, 55,
		hWnd, (HMENU)IDC_BUTTON_BUY3, g_hlnst, NULL);

	SendMessage(hButton[0], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBit);
	SendMessage(hButton[1], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBit);
	SendMessage(hButton[2], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBit);

	SelectObject(memdc, oldFont); DeleteObject(hFont);
}




void showShop(HDC memdc) {
	KillTimer(hWnd, 0);
	CImage shop, buyButton, skill;// , tri;
	HWND hButton[4];
	HDC bitDC;
	HBITMAP hBit[4] = { NULL };// oldBit;
	static RECT textRect[3] = { {425,450,600,600},
								{725,450,900,600},
								{1025,450,1200,600} };

	for (int i = 0; i < 3; i++)
	{
		randValue[i] = -1;
		cardPrice[i] = 0;
	}

	shop.Load(TEXT(".//��������//����UI.png"));
	shop.Draw(memdc, 0, 0, WINWIDTH, WINHEIGHT,
		0, 0, WINWIDTH, WINHEIGHT);
	//buyButton.Load(TEXT(".//��������//������ư.png"));
	hButton[0] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 450, 650, 135, 55,
		hWnd, (HMENU)IDC_BUTTON_BUY1, g_hlnst, NULL);
	hButton[1] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 750, 650, 135, 55,
		hWnd, (HMENU)IDC_BUTTON_BUY2, g_hlnst, NULL);
	hButton[2] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 1050, 650, 135, 55,
		hWnd, (HMENU)IDC_BUTTON_BUY3, g_hlnst, NULL);
	hButton[3] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 1090, 130, 135, 55,
		hWnd, (HMENU)IDC_BUTTON_BUY4, g_hlnst, NULL);
	hBit[3] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	SendMessage(hButton[3], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBit[3]);

	//randValue[0] = getRand(CARDVARIABLE);
	for (int i = 0; i < 3; i++)
	{
		bool keepIn = true;
		while (keepIn) {
			keepIn = false;
			randValue[i] = getRand(CARDVARIABLE);
			for (int j = 0; j < 3; j++)
			{
				if ((i != j && randValue[i] == randValue[j]))
					keepIn = true;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		int rand10 = 99;
		int triRand;

		if(cardCount < 30)
			rand10 = getRand(100);

		switch (randValue[i])
		{
		case N_rhlddufvk:
			skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������.png"));
			if (rand10 >= CARDSPAWNRAND) {
				Rhlddufvk* temp = new Rhlddufvk();
				if (Tripord[N_rhlddufvk][3] == 0 || Tripord[randValue[i]][I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					cardPrice[i] = 5;
				}
				else if (Tripord[N_rhlddufvk][1] != 0) {
					triNum[i] = getRand(2) + 1;
					Tripord[N_rhlddufvk][2] = triNum[i];
					temp->setTier3();
					Tripord[N_rhlddufvk][2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[3], lstrlen(temp->str[3]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 30;
				}
				else if (Tripord[N_rhlddufvk][0] != 0) {
					triNum[i] = getRand(3) + 1;
					Tripord[N_rhlddufvk][I_Tier2] = triNum[i];
					temp->setTier2();
					Tripord[N_rhlddufvk][I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier2], lstrlen(temp->str[R_tier2]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 20;
				}
				else {
					triNum[i] = getRand(3) + 1;
					Tripord[N_rhlddufvk][I_Tier1] = triNum[i];
					temp->setTier1();
					Tripord[N_rhlddufvk][I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier1], lstrlen(temp->str[R_tier1]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				cardPrice[i] = 5;
			}
			break;
		case N_sktjsckd:
			skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//����â.png"));
			if (rand10 >= CARDSPAWNRAND) {
				Sktjsckd* temp = new Sktjsckd();
				if (Tripord[N_sktjsckd][3] == 0 || Tripord[randValue[i]][I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					cardPrice[i] = 5;
				}
				else if (Tripord[N_sktjsckd][1] != 0) {
					triNum[i] = getRand(2) + 1;
					Tripord[N_sktjsckd][2] = triNum[i];
					temp->setTier3();
					Tripord[N_sktjsckd][2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[3], lstrlen(temp->str[3]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 30;
				}
				else if (Tripord[N_sktjsckd][0] != 0) {
					triNum[i] = getRand(3) + 1;
					Tripord[N_sktjsckd][I_Tier2] = triNum[i];
					temp->setTier2();
					Tripord[N_sktjsckd][I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier2], lstrlen(temp->str[R_tier2]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 20;
				}
				else {
					triNum[i] = getRand(3) + 1;
					Tripord[N_sktjsckd][I_Tier1] = triNum[i];
					temp->setTier1();
					Tripord[N_sktjsckd][I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier1], lstrlen(temp->str[R_tier1]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				cardPrice[i] = 5;
			}
			break;
		case N_dbtjdrkdcjs:
			skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������õ.png"));
			if (rand10 >= CARDSPAWNRAND) {
				Dbtjdrkdcjs* temp = new Dbtjdrkdcjs();
				if (Tripord[N_dbtjdrkdcjs][3] == 0 || Tripord[randValue[i]][I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					cardPrice[i] = 5;
				}
				else if (Tripord[N_dbtjdrkdcjs][1] != 0) {
					triNum[i] = getRand(2) + 1;
					Tripord[N_dbtjdrkdcjs][2] = triNum[i];
					temp->setTier3();
					Tripord[N_dbtjdrkdcjs][2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[3], lstrlen(temp->str[3]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 30;
				}
				else if (Tripord[N_dbtjdrkdcjs][0] != 0) {
					triNum[i] = getRand(3) + 1;
					Tripord[N_dbtjdrkdcjs][I_Tier2] = triNum[i];
					temp->setTier2();
					Tripord[N_dbtjdrkdcjs][I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier2], lstrlen(temp->str[R_tier2]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 20;
				}
				else {
					triNum[i] = getRand(3) + 1;
					Tripord[N_dbtjdrkdcjs][I_Tier1] = triNum[i];
					temp->setTier1();
					Tripord[N_dbtjdrkdcjs][I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier1], lstrlen(temp->str[R_tier1]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				cardPrice[i] = 5;
			}
			break;
		case N_wjrfydvh:
			skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������.png"));
			if (rand10 >= CARDSPAWNRAND) {
				Wjrfydvh* temp = new Wjrfydvh();
				if (Tripord[N_wjrfydvh][3] == 0 || Tripord[randValue[i]][I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					cardPrice[i] = 5;
				}
				else if (Tripord[N_wjrfydvh][1] != 0) {
					triNum[i] = getRand(2) + 1;
					Tripord[N_wjrfydvh][2] = triNum[i];
					temp->setTier3();
					Tripord[N_wjrfydvh][2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[3], lstrlen(temp->str[3]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 30;
				}
				else if (Tripord[N_wjrfydvh][0] != 0) {
					triNum[i] = getRand(3) + 1;
					Tripord[N_wjrfydvh][I_Tier2] = triNum[i];
					temp->setTier2();
					Tripord[N_wjrfydvh][I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier2], lstrlen(temp->str[R_tier2]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 20;
				}
				else {
					triNum[i] = getRand(3) + 1;
					Tripord[N_wjrfydvh][I_Tier1] = triNum[i];
					temp->setTier1();
					Tripord[N_wjrfydvh][I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier1], lstrlen(temp->str[R_tier1]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				cardPrice[i] = 5;
			}
			break;
		case N_aodfyddufvk:
			skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//�ͷ濭��.png"));
			if (rand10 >= CARDSPAWNRAND) {
				Aodfyddufvk* temp = new Aodfyddufvk();
				if (Tripord[N_aodfyddufvk][3] == 0 || Tripord[randValue[i]][I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					cardPrice[i] = 5;
				}
				else if (Tripord[N_aodfyddufvk][1] != 0) {
					triNum[i] = getRand(2) + 1;
					Tripord[N_aodfyddufvk][2] = triNum[i];
					temp->setTier3();
					Tripord[N_aodfyddufvk][2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[3], lstrlen(temp->str[3]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 30;
				}
				else if (Tripord[N_aodfyddufvk][0] != 0) {
					triNum[i] = getRand(3) + 1;
					Tripord[N_aodfyddufvk][I_Tier2] = triNum[i];
					temp->setTier2();
					Tripord[N_aodfyddufvk][I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier2], lstrlen(temp->str[R_tier2]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 20;
				}
				else {
					triNum[i] = getRand(3) + 1;
					Tripord[N_aodfyddufvk][I_Tier1] = triNum[i];
					temp->setTier1();
					Tripord[N_aodfyddufvk][I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier1], lstrlen(temp->str[R_tier1]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				cardPrice[i] = 5;
			}
			break;
		case N_qksdnjftja:
			skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//�ݿ���.png"));
			if (rand10 >= CARDSPAWNRAND) {
				Qksdnjftja* temp = new Qksdnjftja();
				if (Tripord[N_qksdnjftja][3] == 0 || Tripord[randValue[i]][I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					cardPrice[i] = 5;
				}
				else if (Tripord[N_qksdnjftja][1] != 0) {
					triNum[i] = getRand(2) + 1;
					Tripord[N_qksdnjftja][2] = triNum[i];
					temp->setTier3();
					Tripord[N_qksdnjftja][2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[3], lstrlen(temp->str[3]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 30;
				}
				else if (Tripord[N_qksdnjftja][0] != 0) {
					triNum[i] = getRand(3) + 1;
					Tripord[N_qksdnjftja][I_Tier2] = triNum[i];
					temp->setTier2();
					Tripord[N_qksdnjftja][I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier2], lstrlen(temp->str[R_tier2]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 20;
				}
				else {
					triNum[i] = getRand(3) + 1;
					Tripord[N_qksdnjftja][I_Tier1] = triNum[i];
					temp->setTier1();
					Tripord[N_qksdnjftja][I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier1], lstrlen(temp->str[R_tier1]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				cardPrice[i] = 5;
			}
			break;
		case N_dusghkstja:
			skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//��ȯ��.png"));
			if (rand10 >= CARDSPAWNRAND) {
				Dusghkstja* temp = new Dusghkstja();
				if (Tripord[N_dusghkstja][3] == 0 || Tripord[randValue[i]][I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					cardPrice[i] = 5;
				}
				else if (Tripord[N_dusghkstja][1] != 0) {
					triNum[i] = getRand(2) + 1;
					Tripord[N_dusghkstja][2] = triNum[i];
					temp->setTier3();
					Tripord[N_dusghkstja][2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[3], lstrlen(temp->str[3]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 30;
				}
				else if (Tripord[N_dusghkstja][0] != 0) {
					triNum[i] = getRand(3) + 1;
					Tripord[N_dusghkstja][I_Tier2] = triNum[i];
					temp->setTier2();
					Tripord[N_dusghkstja][I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier2], lstrlen(temp->str[R_tier2]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 20;
				}
				else {
					triNum[i] = getRand(3) + 1;
					Tripord[N_dusghkstja][I_Tier1] = triNum[i];
					temp->setTier1();
					Tripord[N_dusghkstja][I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier1], lstrlen(temp->str[R_tier1]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				cardPrice[i] = 5;
			}
			break;
		case N_cjdfydwls:
			skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//û����.png"));
			if (rand10 >= CARDSPAWNRAND) {
				Cjdfydwls* temp = new Cjdfydwls();
				if (Tripord[N_cjdfydwls][3] == 0 || Tripord[randValue[i]][I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					cardPrice[i] = 5;
				}
				else if (Tripord[N_cjdfydwls][1] != 0) {
					triNum[i] = getRand(2) + 1;
					Tripord[N_cjdfydwls][2] = triNum[i];
					temp->setTier3();
					Tripord[N_cjdfydwls][2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[3], lstrlen(temp->str[3]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 30;
				}
				else if (Tripord[N_cjdfydwls][0] != 0) {
					triNum[i] = getRand(3) + 1;
					Tripord[N_cjdfydwls][I_Tier2] = triNum[i];
					temp->setTier2();
					Tripord[N_cjdfydwls][I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier2], lstrlen(temp->str[R_tier2]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 20;
				}
				else {
					triNum[i] = getRand(3) + 1;
					Tripord[N_cjdfydwls][I_Tier1] = triNum[i];
					temp->setTier1();
					Tripord[N_cjdfydwls][I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier1], lstrlen(temp->str[R_tier1]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				cardPrice[i] = 5;
			}
			break;
		case N_cjdfydcnftn:
			skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//û�����.png"));
			if (rand10 >= CARDSPAWNRAND) {
				Cjdfydcnftn* temp = new Cjdfydcnftn();
				if (Tripord[N_cjdfydcnftn][3] == 0 || Tripord[randValue[i]][I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					cardPrice[i] = 5;
				}
				else if (Tripord[N_cjdfydcnftn][1] != 0) {
					triNum[i] = getRand(2) + 1;
					Tripord[N_cjdfydcnftn][2] = triNum[i];
					temp->setTier3();
					Tripord[N_cjdfydcnftn][2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[3], lstrlen(temp->str[3]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 30;
				}
				else if (Tripord[N_cjdfydcnftn][0] != 0) {
					triNum[i] = getRand(3) + 1;
					Tripord[N_cjdfydcnftn][I_Tier2] = triNum[i];
					temp->setTier2();
					Tripord[N_cjdfydcnftn][I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier2], lstrlen(temp->str[R_tier2]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 20;
				}
				else {
					triNum[i] = getRand(3) + 1;
					Tripord[N_cjdfydcnftn][I_Tier1] = triNum[i];
					temp->setTier1();
					Tripord[N_cjdfydcnftn][I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier1], lstrlen(temp->str[R_tier1]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				cardPrice[i] = 5;
			}
			break;
		case N_ghltjsckd:
			skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//ȸ��â.png"));
			if (rand10 >= CARDSPAWNRAND) {
				Ghltjsckd* temp = new Ghltjsckd();
				if (Tripord[N_ghltjsckd][3] == 0 || Tripord[randValue[i]][I_Tier3] != 0) {
					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
						0, 0, 100, 100);
					cardPrice[i] = 5;
				}
				else if (Tripord[N_ghltjsckd][1] != 0) {
					triNum[i] = getRand(2) + 1;
					Tripord[N_ghltjsckd][2] = triNum[i];
					temp->setTier3();
					Tripord[N_ghltjsckd][2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư30G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[3].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[3], lstrlen(temp->str[3]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 30;
				}
				else if (Tripord[N_ghltjsckd][0] != 0) {
					triNum[i] = getRand(3) + 1;
					Tripord[N_ghltjsckd][I_Tier2] = triNum[i];
					temp->setTier2();
					Tripord[N_ghltjsckd][I_Tier2] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư20G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier2].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier2], lstrlen(temp->str[R_tier2]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 20;
				}
				else {
					triNum[i] = getRand(3) + 1;
					Tripord[N_ghltjsckd][I_Tier1] = triNum[i];
					temp->setTier1();
					Tripord[N_ghltjsckd][I_Tier1] = 0;

					hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư10G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
					skill.Draw(memdc, 474 + 300 * i, 259, 75, 75,
						0, 0, 100, 100);
					temp->img[R_tier1].Draw(memdc, 484 + 300 * i, 360, 56, 56,
						0, 0, 56, 56);
					DrawText(memdc, temp->str[R_tier1], lstrlen(temp->str[R_tier1]), &textRect[i], DT_LEFT | DT_WORDBREAK);
					cardPrice[i] = 10;
				}
				delete temp;
			}
			else {
				hBit[i] = (HBITMAP)LoadImage(g_hlnst, TEXT(".//��������//������ư5G.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				skill.Draw(memdc, 474 + 300 * i, 360, 75, 75,
					0, 0, 100, 100);
				cardPrice[i] = 5;
			}
			break;
		//case N_dmsgkdbtjdxks:
		//	skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//��������ź.png"));
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