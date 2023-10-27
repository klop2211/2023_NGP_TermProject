#pragma once

class Card {
public:
	POINT point;
	CImage img[4];			//ī��, Ʈ��3��
	CImage effect, skill;
	RECT rect[4];
	TCHAR nameStr[11];
	TCHAR str[4][100];
	bool isValid, cheep;
	CardName cardname;
	int damage, Mana, destruction, neutralization;
	//���ؼ�ġ ���� ���ļ�ġ ����ȭ��ġ

	//Card() {}
	Card() {
		rect[R_main] = { 30,160,277,245 };
		rect[R_tier1] = { 60,265,300,305 };//240/40
		rect[R_tier2] = { 60,355,300,395 };//240/40
		rect[R_tier3] = { 60,440,300,480 };//240/40
		isValid = true, cheep = false;
	}

	~Card() {
		for (int i = 0; i < 4; i++)
		{
			if (img[i] != nullptr)
				img[i].Destroy();
		}
		if (skill != nullptr)
			skill.Destroy();
		if (effect != nullptr)
			effect.Destroy();
	}

	void handDraw() {
		HBRUSH hBrush, oldBrush;
		RECT rect = { point.x, point.y, point.x + 187, point.y + 35 };
		TCHAR manaStr[3];

		hBrush = CreateSolidBrush(RGB(14, 15, 16));
		oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
		Rectangle(memdc, point.x, point.y, point.x + 187, point.y + 300);
		SelectObject(memdc, oldBrush); DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(25, 28, 33));
		oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
		Rectangle(memdc, point.x, point.y, point.x + 187, point.y + 35);
		SelectObject(memdc, oldBrush); DeleteObject(hBrush);

		SetBkMode(memdc, TRANSPARENT);
		SetTextColor(memdc, RGB(255, 255, 255));
		DrawText(memdc, nameStr, lstrlen(nameStr), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		//SetTextColor(memdc, RGB(0, 0, 0));
		skill.Draw(memdc, point.x + 96 - 40, point.y + 40, 80, 80, 0, 0, 100, 100);
		manaImg[0].Draw(memdc, point.x + 160, point.y, 27, 30, 0, 0, 102, 115);
		rect = { point.x + 160, point.y, point.x + 160 + 27, point.y + 30 };
		swprintf_s(manaStr, 3, L"%d", Mana);
		DrawText(memdc, manaStr, lstrlen(manaStr), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}

	void closeDraw() {
		int tempX = point.x - (CARDWIDTH - CARDMINIWIDTH) / 2;
		int tempY = point.y - CARDHEIGHT;
		mainDraw(tempX, tempY);
	}

	void dragDraw() {
		int tempX = point.x - (CARDWIDTH - CARDMINIWIDTH) / 2;
		int tempY = point.y;
		mainDraw(tempX, tempY);
	}

	void mainDraw(int tempX, int tempY) {
		SetTextColor(memdc, RGB(205, 205, 205));
		RECT temp;
		HFONT hFont, oldFont;
		RECT manaRect;
		TCHAR manaStr[3];

		img[0].Draw(memdc, tempX, tempY, CARDWIDTH, CARDHEIGHT,
			0, 0, CARDWIDTH, CARDHEIGHT);
		temp = { rect[R_main].left + tempX, rect[R_main].top + tempY, rect[R_main].right + tempX, rect[R_main].bottom + tempY };
		DrawText(memdc, str[R_main], lstrlen(str[R_main]), &temp, DT_LEFT | DT_WORDBREAK);

		hFont = CreateFont(13, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"");
		oldFont = (HFONT)SelectObject(memdc, hFont);

		if (img[R_tier1] != nullptr) {
			img[R_tier1].Draw(memdc, tempX + 7, tempY + 264, 44, 44,
				0, 0, 56, 56);
			temp = { rect[R_tier1].left + tempX, rect[R_tier1].top + tempY, rect[R_tier1].right + tempX, rect[R_tier1].bottom + tempY };
			DrawText(memdc, str[R_tier1], lstrlen(str[R_tier1]), &temp, DT_LEFT | DT_WORDBREAK);

		}
		if (img[R_tier2] != nullptr) {
			img[R_tier2].Draw(memdc, tempX + 8, tempY + 351, 45, 45,
				0, 0, 56, 56);
			temp = { rect[R_tier2].left + tempX, rect[R_tier2].top + tempY, rect[R_tier2].right + tempX, rect[R_tier2].bottom + tempY };
			DrawText(memdc, str[R_tier2], lstrlen(str[R_tier2]), &temp, DT_LEFT | DT_WORDBREAK);

		}
		if (img[R_tier3] != nullptr) {
			img[R_tier3].Draw(memdc, tempX + 8, tempY + 435, 45, 45,
				0, 0, 56, 56);
			temp = { rect[R_tier3].left + tempX, rect[R_tier3].top + tempY, rect[R_tier3].right + tempX, rect[R_tier3].bottom + tempY };
			DrawText(memdc, str[R_tier3], lstrlen(str[R_tier3]), &temp, DT_LEFT | DT_WORDBREAK);
		}

		SetTextColor(memdc, RGB(255, 255, 255));
		manaRect = { tempX + CARDWIDTH - 43, tempY , tempX + CARDWIDTH,  tempY + 49};
		swprintf_s(manaStr, 3, L"%d", Mana);
		manaImg[0].Draw(memdc, manaRect);
		DrawText(memdc, manaStr, lstrlen(manaStr), &manaRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		SelectObject(memdc, oldFont); DeleteObject(hFont);
	}

	virtual void __init__() { }
	virtual bool getOnce() { return NULL; }
};

//====================================����============================================

class Wjrfydvh : public Card {
public:

	Wjrfydvh() : Card() {
		__init__();
	}

	void setTier1() {
		switch (Tripord[N_wjrfydvh][0])
		{
		case 1:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//�����غ�1.jpg"));
			lstrcpy(str[1], L"���� �غ�\n��¡ �ӵ��� �����Ѵ�.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//�����ӵ�1.jpg"));
			lstrcpy(str[1], L"��Ÿ� ����\n���� ��Ÿ��� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
			lstrcpy(str[1], L"�޼� Ÿ��\n������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_wjrfydvh][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//��������2.jpg"));
			lstrcpy(str[2], L"���� ����\n�Ҹ�Ǵ� ������ ���ҽ�Ų��.\n");
			cheep = true;
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ձ�.jpg"));
			lstrcpy(str[2], L"ī�� �̱�\n������ ����ī�带 �̴´�.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ı���ȭ2.jpg"));
			lstrcpy(str[2], L"�����ı� ��ȭ\n.���� �ı� ��ġ�� +1��ŭ ���� ��Ų��\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_wjrfydvh][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//ġ����������.jpg"));
			lstrcpy(str[3], L"ġ������ ����\n������ �����Ե� ���ظ� ������.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//��������3.jpg"));
			lstrcpy(str[3], L"���� ����\n������ ������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void __init__() {
		for (int i = 0; i < 4; i++)
		{
			if (img[i] != nullptr)
				img[i].Destroy();
		}
		if (skill != nullptr)
			skill.Destroy();
		if (effect != nullptr)
			effect.Destroy();

		if (Tripord[N_wjrfydvh][2] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//������3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_wjrfydvh][1] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//������2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_wjrfydvh][0] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//������1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//ī�����//ī��//������.jpg"));

		cardname = N_wjrfydvh;
		Mana = 8 - cheep, damage = 15, neutralization = 5, destruction = 1;

		lstrcpy(nameStr, L"������");
		skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������.png"));
		swprintf_s(str[R_main], 100, L"�ڼ��� ��� ������ �� �������� â�� �� %d�� ���ظ� �ش�.\n�����ı� : %d\0", damage, destruction);
	}
};

class Sktjsckd : public Card {
public:
	Sktjsckd() : Card() {
		__init__();
	}

	void setTier1() {
		switch (Tripord[N_sktjsckd][0])
		{
		case 1:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//����Ưȭ.jpg"));
			lstrcpy(str[1], L"���� Ưȭ\n�Ϲ� ������ ������ ���ذ� �����Ѵ�.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//Ź���ѱ⵿��.jpg"));
			lstrcpy(str[1], L"Ź���� �⵿��\n��� �� �̵��ӵ��� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//ȭ������1.jpg"));
			lstrcpy(str[1], L"������ ����\n������ �������� �߰� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_sktjsckd][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ձ�.jpg"));
			lstrcpy(str[2], L"���� ����\n�� ��ų�� 1ȸ �� ����Ѵ�.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//����Ÿ��.jpg"));
			lstrcpy(str[2], L"���� Ÿ��\n������ ������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ձ�.jpg"));
			lstrcpy(str[2], L"ī�� �̱�\n������ ����ī�带 �̴´�\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_sktjsckd][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����ȭ.jpg"));
			lstrcpy(str[3], L"��� ��ȭ\n��ų�� ��Ÿ��� �����Ѵ�.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//ġ����������.jpg"));
			lstrcpy(str[3], L"��ȭ�� â\n�������� ����������, �ʳ����� ���󰡴� â�� ������.\n");
			break;
		default:
			break;
		}
	}

	void __init__() {
		for (int i = 0; i < 4; i++)
		{
			if (img[i] != nullptr)
				img[i].Destroy();
		}
		if (skill != nullptr)
			skill.Destroy();
		if (effect != nullptr)
			effect.Destroy();
		if (Tripord[N_sktjsckd][2] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//����â3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_sktjsckd][1] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//����â2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_sktjsckd][0] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//����â1.png"));
			setTier1();
		}
		else {
			img[0].Load(TEXT(".//ī�����//ī��//����â.jpg"));
		}
		cardname = N_sktjsckd;
		Mana = 1, damage = 7, neutralization = 5, destruction = 0;

		lstrcpy(nameStr, L"����â");
		skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//����â.png"));
		swprintf_s(str[R_main], 100, L"â���� �����ϰ� �� %d�� ���ظ� �ش�.\n\0", damage);
	}
};

class Rhlddufvk : public Card {
public:
	Rhlddufvk() : Card() {
		__init__();
	}

	void setTier1() {
		switch (Tripord[N_rhlddufvk][0])
		{
		case 1:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//�����ı���ȭ1.jpg"));
			lstrcpy(str[1], L"�����ı� ��ȭ\n���� �ı� ��ġ�� +1��ŭ ���� ��Ų��.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//�����غ�1.jpg"));
			lstrcpy(str[1], L"���� �ӵ� ����\n���� �ӵ��� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//Ź���ѱ⵿��.jpg"));
			lstrcpy(str[1], L"Ź���� �⵿��\n��� �� �̵��ӵ��� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_rhlddufvk][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//ȭ��ȸ��.jpg"));
			lstrcpy(str[2], L"ȭ�� ȸ��\n������ ������ ȭ���� �ο��Ѵ�.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//������.jpg"));
			lstrcpy(str[2], L"���� ���\n������ ���� â ������ ���ĳ���.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//����Ÿ��.jpg"));
			lstrcpy(str[2], L"������ ����\n������ ������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_rhlddufvk][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//���ݺ���.jpg"));
			lstrcpy(str[3], L"���� ��ȭ\n��¡ ��ų�� �ٲ�� �ִ� ���ؿ� ��Ÿ��� �����Ѵ�.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//��������3.jpg"));
			lstrcpy(str[3], L"���� ����\n�Ҹ�Ǵ� ������ ���ҽ�Ų��.\n");
			cheep = true;
			break;
		default:
			break;
		}
	}

	void __init__() {
		for (int i = 0; i < 4; i++)
		{
			//if (img[i] != nullptr)
				img[i].Destroy();
		}
		if (skill != nullptr)
			skill.Destroy();
		if (effect != nullptr)
			effect.Destroy();

		if (Tripord[N_rhlddufvk][2] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//������3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_rhlddufvk][1] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//������2.png"));
			setTier1();
			setTier2();
		}
		else if (Tripord[N_rhlddufvk][0] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//������1.png"));
			setTier1();
		}
		else {
			img[0].Load(TEXT(".//ī�����//ī��//������.jpg"));
		}

		cardname = N_rhlddufvk;
		Mana = 3 - cheep, damage = 10, neutralization = 5, destruction = 1;

		lstrcpy(nameStr, L"������");
		skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������.png"));
		swprintf_s(str[R_main], 100, L"â�� �⸦ ��� ����� ������ %d���ظ� �ش�.\n�����ı� : %d\0", damage, destruction);
	}
};

class Dbtjdrkdcjs : public Card {
public:

	Dbtjdrkdcjs() : Card() {
		__init__();
	}

	void setTier1() {
		switch (Tripord[N_dbtjdrkdcjs][0])
		{
		case 1:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//�����غ�1.jpg"));
			lstrcpy(str[1], L"���� ����\n���� �ӵ��� �����Ѵ�.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//����Ưȭ.jpg"));
			lstrcpy(str[1], L"���� Ưȭ\n�Ϲ� ������ ������ ���ذ� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//��������1.jpg"));
			lstrcpy(str[1], L"���� ����\n������ ������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_dbtjdrkdcjs][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//����ȿ��.jpg"));
			lstrcpy(str[2], L"���� ����\n������ ���� ������Ų��.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//ȭ��ȸ��.jpg"));
			lstrcpy(str[2], L"ȭ�� ����\n���� ��ġ�� ȭ���� �ο��ϴ� ȭ�����븦 �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ı�.jpg"));
			lstrcpy(str[2], L"���� ����\n���� �׵θ��� ���� ������ ���� ���� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_dbtjdrkdcjs][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����Ѹ�����.jpg"));
			lstrcpy(str[3], L"��ȭ ����\n���� �� �¿�� â�� ��������.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//ġ����������.jpg"));
			lstrcpy(str[3], L"���� ��â\n������ ���� ������, â�� �ϴÿ��� �������� �Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void __init__() {
		for (int i = 0; i < 4; i++)
		{
			if (img[i] != nullptr)
				img[i].Destroy();
		}
		if (skill != nullptr)
			skill.Destroy();
		if (effect != nullptr)
			effect.Destroy();

		if (Tripord[N_dbtjdrkdcjs][2] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//������õ3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_dbtjdrkdcjs][1] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//������õ2.png"));
			setTier1();
			setTier2();
		}
		else if (Tripord[N_dbtjdrkdcjs][0] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//������õ1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//ī�����//ī��//������õ.jpg"));

		cardname = N_dbtjdrkdcjs;
		Mana = 7, damage = 12, neutralization = 5, destruction = 0;

		lstrcpy(nameStr, L"������õ");
		skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������õ.png"));
		swprintf_s(str[R_main], 100, L"���� �����Ͽ� ���� �Ⱦ� ����ĸ� ������ %d�� ���ظ� �ش�.\n\0", damage);
	}
};

//==========================����======================================

class Aodfyddufvk : public Card {
public:
	Aodfyddufvk() : Card() {
		__init__();
	}

	void setTier1() {
		switch (Tripord[N_aodfyddufvk][0])
		{
		case 1:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//��������.jpg"));
			lstrcpy(str[1], L"���� ����\n���� ������ �����Ѵ�.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//������.jpg"));
			lstrcpy(str[1], L"������\n������ �ִ� ����ȭ�� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
			lstrcpy(str[1], L"�޼� Ÿ��\n������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_aodfyddufvk][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����غ�2.jpg"));
			lstrcpy(str[2], L"���� �ӵ� ����\n���� �ӵ��� �����Ѵ�.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//�ñ�ȸ��.jpg"));
			lstrcpy(str[2], L"���Ӽ� �ο�\n������ ������ ������ �ο��Ѵ�.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//ȭ��ȸ��.jpg"));
			lstrcpy(str[2], L"ȭ�Ӽ� �ο�\n������ ������ ȭ���� �ο��Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_aodfyddufvk][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����ձ�3.jpg"));
			lstrcpy(str[3], L"���� ����\n�� ��ų�� 1ȸ �� ����Ѵ�.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//��������3.jpg"));
			lstrcpy(str[3], L"���� ����\n�Ҹ�Ǵ� ������ ���ҽ�Ų��.\n");
			cheep = true;
			break;
		default:
			break;
		}
	}

	void __init__() {
		for (int i = 0; i < 4; i++)
		{
			if (img[i] != nullptr)
				img[i].Destroy();
		}
		if (skill != nullptr)
			skill.Destroy();
		if (effect != nullptr)
			effect.Destroy();

		if (Tripord[N_aodfyddufvk][2] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//�ͷ濭��3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_aodfyddufvk][1] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//�ͷ濭��2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_aodfyddufvk][0] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//�ͷ濭��1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//ī�����//ī��//�ͷ濭��.jpg"));

		cardname = N_aodfyddufvk;
		Mana = 6 - cheep, damage = 10, neutralization = 15, destruction = 0;

		lstrcpy(nameStr, L"�ͷ濭��");
		skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//�ͷ濭��.png"));
		swprintf_s(str[R_main], 100, L"���� ū â���� �ٲ�� ũ�� �ֵѷ� %d�� ���ظ� �ش�.\n����ȭ : ��\0", damage);
	}
};

class Qksdnjftja : public Card {
public:
	Qksdnjftja() : Card() {
		__init__();
	}

	void setTier1() {
		switch (Tripord[N_qksdnjftja][0])
		{
		case 1:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//�����ı���ȭ1.jpg"));
			lstrcpy(str[1], L"�����ı� ��ȭ\n���� �ı� ��ġ�� +1��ŭ ���� ��Ų��.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
			lstrcpy(str[1], L"�޼� Ÿ��\n������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//Ź���ѱ⵿��.jpg"));
			lstrcpy(str[1], L"Ź���� �⵿��\n��ų�� ���� �Ÿ��� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_qksdnjftja][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//������2.jpg"));
			lstrcpy(str[2], L"������\n������ �ִ� ����ȭ�� �����Ѵ�.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//����Ÿ��.jpg"));
			lstrcpy(str[2], L"���� Ÿ��\n������ ������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//��������2.jpg"));
			lstrcpy(str[2], L"���� ����\n�Ҹ�Ǵ� ������ ���ҽ�Ų��.\n");
			cheep = true;
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_qksdnjftja][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����Ѹ�����.jpg"));
			lstrcpy(str[3], L"�а� ������\n���� �������� �����ϸ� �Ϲݸ��� ������.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//���̼��ϰ�.jpg"));
			lstrcpy(str[3], L"ȸ���� ����\n������ ������ ȸ������ �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}
	void __init__() {
		for (int i = 0; i < 4; i++)
		{
			if (img[i] != nullptr)
				img[i].Destroy();
		}
		if (skill != nullptr)
			skill.Destroy();
		if (effect != nullptr)
			effect.Destroy();

		if (Tripord[N_qksdnjftja][2] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//�ݿ���3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_qksdnjftja][1] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//�ݿ���2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_qksdnjftja][0] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//�ݿ���1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//ī�����//ī��//�ݿ���.jpg"));

		cardname = N_qksdnjftja;
		Mana = 7 - cheep, damage = 12, neutralization = 20; destruction = 2;

		lstrcpy(nameStr, L"�ݿ���");
		skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//�ݿ���.png"));
		swprintf_s(str[R_main], 100, L"�������� ��â�� �ٴڿ� ���鼭 �̵��Ͽ� %d�� ���ظ� �ش�.\n����ȭ : �߻�\0", damage);
	}

};

class Dusghkstja : public Card {
public:
	Dusghkstja() : Card() {
		__init__();
	}

	void setTier1() {
		switch (Tripord[N_dusghkstja][0])
		{
		case 1:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
			lstrcpy(str[1], L"�޼� Ÿ��\n�������� ������, ������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//Ź���ѱ⵿��.jpg"));
			lstrcpy(str[1], L"Ź���� �⵿��\n��ų�� ���� �Ÿ��� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//ȭ������1.jpg"));
			lstrcpy(str[1], L"������ ����\n������ �������� �߰� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_dusghkstja][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����غ�2.jpg"));
			lstrcpy(str[2], L"���� �ӵ� ����\n���� �ӵ��� �����Ѵ�.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//������.jpg"));
			lstrcpy(str[2], L"������\n������ �ִ� ����ȭ�� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//�ı��ϴ�â.jpg"));
			lstrcpy(str[2], L"�ı��ϴ� â\n������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_dusghkstja][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����Ѹ�����.jpg"));
			lstrcpy(str[3], L"ī�� �̱�\nī�带 �� �� ������, �Ҹ�Ǵ� ������ ������Ų��.\n");
			cheep = true;
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//������â.jpg"));
			lstrcpy(str[3], L"�˱� ����\n������ �˱⸦ ����������, �Ҹ�Ǵ� ������ ������Ų��.\n");
			cheep = true;
			break;
		default:
			break;
		}
	}

	void __init__() {
		for (int i = 0; i < 4; i++)
		{
			if (img[i] != nullptr)
				img[i].Destroy();
		}
		if (skill != nullptr)
			skill.Destroy();
		if (effect != nullptr)
			effect.Destroy();

		if (Tripord[N_dusghkstja][2] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//��ȯ��3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_dusghkstja][1] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//��ȯ��2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_dusghkstja][0] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//��ȯ��1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//ī�����//ī��//��ȯ��.jpg"));

		cardname = N_dusghkstja;
		Mana = 2 + cheep, damage = 6, neutralization = 5, destruction = 1;

		lstrcpy(nameStr, L"��ȯ��");
		skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//��ȯ��.png"));
		swprintf_s(str[R_main], 100, L"â�� ���� �÷�ģ �� ������ �����Ͽ� ����������Ͽ� %d�� ���ظ� �ش�.\n�����ı� : %d\0", damage, destruction);
	}
};

class Cjdfydwls : public Card {
public:
	Cjdfydwls() : Card() {
		__init__();
	}

	void setTier1() {
		switch (Tripord[N_cjdfydwls][0])
		{
		case 1:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//������.jpg"));
			lstrcpy(str[1], L"������\n������ �ִ� ����ȭ�� �����Ѵ�.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
			lstrcpy(str[1], L"�޼� Ÿ��\n������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//��������.jpg"));
			lstrcpy(str[1], L"���� ����\n���� ������ �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_cjdfydwls][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//����ġ��â.jpg"));
			lstrcpy(str[2], L"â ��ȯ\nâ�� ���� �ʴ� ��� â�� ��ȯ�Ͽ� ������.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//���߰���.jpg"));
			lstrcpy(str[2], L"���� ����\n���� ������ ����������, �������� ũ�� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ı�.jpg"));
			lstrcpy(str[2], L"��Ӽ� �ο�\n���� ������ ���� ���� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_cjdfydwls][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����ձ�3.jpg"));
			lstrcpy(str[3], L"ī�� �̱�\nī�带 �� �� �̴´�.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//��������3.jpg"));
			lstrcpy(str[3], L"���� ����\n�Ҹ�Ǵ� ������ ���ҽ�Ų��.\n");
			cheep = true;
			break;
		default:
			break;
		}
	}

	void __init__() {
		for (int i = 0; i < 4; i++)
		{
			if (img[i] != nullptr)
				img[i].Destroy();
		}
		if (skill != nullptr)
			skill.Destroy();
		if (effect != nullptr)
			effect.Destroy();

		if (Tripord[N_cjdfydwls][2] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//û����3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_cjdfydwls][1] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//û����2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_cjdfydwls][0] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//û����1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//ī�����//ī��//û����.jpg"));

		cardname = N_cjdfydwls;
		Mana = 1 - cheep, damage = 5, neutralization = 5, destruction = 1;

		lstrcpy(nameStr, L"û����");
		skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//û����.png"));
		swprintf_s(str[R_main], 100, L"���ڸ����� â�� ���ϰ� ������� ����İ� ���� %d�� ���ظ� �ش�.\n�����ı� : %d\0", damage, destruction);
	}
};

class Cjdfydcnftn : public Card {
public:
	Cjdfydcnftn() : Card() {
		__init__();
	}

	void setTier1() {
		switch (Tripord[N_cjdfydcnftn][0])
		{
		case 1:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
			lstrcpy(str[1], L"�޼� Ÿ��\n������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//ġ�����ΰ���.jpg"));
			lstrcpy(str[1], L"���� ��ȭ\n������ ���� ������, �������� ũ�� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//Ź���ѱ⵿��.jpg"));
			lstrcpy(str[1], L"Ź���� �⵿��\n��� �� �̵��ӵ��� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_cjdfydcnftn][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//�������.jpg"));
			lstrcpy(str[2], L"ǳ�Ӽ� �ο�\n�� �Ʒ� ���� �������.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//ȭ������2.jpg"));
			lstrcpy(str[2], L"������ ����\n������ �������� �߰� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//����Ÿ��.jpg"));
			lstrcpy(str[2], L"���� ����\n���� ������ �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_cjdfydcnftn][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//���ݺ���.jpg"));
			lstrcpy(str[3], L"â ��ġ\nȸ���ϴ� â�� ��ġ�Ѵ�.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//���̼��ϰ�.jpg"));
			lstrcpy(str[3], L"����\n���� �� ���ΰ� ������ ���� ���� â�� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void __init__() {
		for (int i = 0; i < 4; i++)
		{
			if (img[i] != nullptr)
				img[i].Destroy();
		}
		if (skill != nullptr)
			skill.Destroy();
		if (effect != nullptr)
			effect.Destroy();

		if (Tripord[N_cjdfydcnftn][2] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//û�����3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_cjdfydcnftn][1] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//û�����2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_cjdfydcnftn][0] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//û�����1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//ī�����//ī��//û�����.jpg"));

		cardname = N_cjdfydcnftn;
		Mana = 3, damage = 5, neutralization = 15, destruction = 0;

		lstrcpy(nameStr, L"û�����");
		skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//û�����.png"));
		swprintf_s(str[R_main], 100, L"�������� ������ �� â�� ������ �ֵѷ� %d�� ���ظ� �ش�.\n����ȭ : ��\0", damage);
	}
};

class Ghltjsckd : public Card {
public:
	bool once;
	Ghltjsckd() : Card() {
		once = false;
		__init__();
	}

	Ghltjsckd(bool a) : Card() {
		once = true;
		__init__();
	}

	void setTier1() {
		switch (Tripord[N_ghltjsckd][0])
		{
		case 1:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//Ź���ѱ⵿��.jpg"));
			lstrcpy(str[1], L"Ź���� �⵿��\n��� �� �̵��ӵ��� �����Ѵ�.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
			lstrcpy(str[1], L"�޼� Ÿ��\n������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//ī�����//Ʈ��//ȸ���÷�ġ��.jpg"));
			lstrcpy(str[1], L"���� ������\n1ȸ�� ȸ���Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_ghltjsckd][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ı�.jpg"));
			lstrcpy(str[2], L"���� �ٶ�\n������ ������ ���� ������.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//����Ÿ��.jpg"));
			lstrcpy(str[2], L"���� Ÿ��\n������ ������ �ִ� ���ذ� �����Ѵ�.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//ī�����//Ʈ��//ȭ������2.jpg"));
			lstrcpy(str[2], L"������ ����\n������ �������� �߰� �����Ѵ�.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_ghltjsckd][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//����ȸ��.jpg"));
			lstrcpy(str[3], L"���� ����\n�� ī�带 1ȸ �����´�.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����ձ�3.jpg"));
			lstrcpy(str[3], L"ī�� �̱�\n������ ������ ���� ī�带 1�� �̴´�.\n");
			break;
		default:
			break;
		}
	}

	bool getOnce() { return once; };

	void __init__() {
		for (int i = 0; i < 4; i++)
		{
			if (img[i] != nullptr)
				img[i].Destroy();
		}
		if (skill != nullptr)
			skill.Destroy();
		if (effect != nullptr)
			effect.Destroy();

		if (Tripord[N_ghltjsckd][2] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//ȸ��â3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_ghltjsckd][1] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//ȸ��â2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_ghltjsckd][0] != 0) {
			img[0].Load(TEXT(".//ī�����//ī��//ȸ��â1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//ī�����//ī��//ȸ��â.jpg"));

		cardname = N_ghltjsckd;
		Mana = 5, damage = 9, neutralization = 10, destruction = 0;

		lstrcpy(nameStr, L"ȸ��â");
		skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//ȸ��â.png"));
		swprintf_s(str[R_main], 100, L"�������� ȸ���Ͽ� %d�� ���ظ� �ش�.\n����ȭ : ��\0", damage);
	}
};

class Dmsgkdbtjdxks : public Card {
public:
	Dmsgkdbtjdxks() : Card() {
		//if (Tripord[N_dmsgkdbtjdxks][2] != 0)
		//	img[0].Load(TEXT(".//ī�����//ī��//��������ź3.png"));
		//else if (Tripord[N_dmsgkdbtjdxks][1] != 0)
		//	img[0].Load(TEXT(".//ī�����//ī��//��������ź2.png"));
		//else if (Tripord[N_dmsgkdbtjdxks][0] != 0)
		//	img[0].Load(TEXT(".//ī�����//ī��//��������ź1.png"));
		//else
			img[0].Load(TEXT(".//ī�����//ī��//��������ź.jpg"));

		cardname = N_dmsgkdbtjdxks;
		Mana = 10, damage = 20, neutralization = 40, destruction = 2;

		lstrcpy(nameStr, L"��������ź");
		skill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//��������ź.png"));
		swprintf_s(str[R_main], 100, L"���� ������ �� â�� ������. â�� ���� �������� %d�� ���ظ� �ְ� ������ �����Ѵ�.\n�����ı� : %d, ����ȭ : �ֻ�\0", damage, destruction);
	}
};

Card* card[30] = { nullptr };
Card* handCard[7] = {nullptr};
int cardCount = 0;
int deadCardCount = 0;

//�տ� �ִ� ī�� ��
int handCardCount = 0;


void makeCard(int randomValue) {
	Card* temp = nullptr;
	Card* temp1 = nullptr;
	switch (randomValue)
	{
	case N_rhlddufvk:
		temp = new Rhlddufvk;
		temp1 = new Rhlddufvk;
		break;
	case N_sktjsckd:
		temp = new Sktjsckd;
		temp1 = new Sktjsckd;
		break;
	case N_dbtjdrkdcjs:
		temp = new Dbtjdrkdcjs;
		temp1 = new Dbtjdrkdcjs;
		break;
	case N_wjrfydvh:
		temp = new Wjrfydvh;
		temp1 = new Wjrfydvh;
		break;
	case N_aodfyddufvk:
		temp = new Aodfyddufvk;
		temp1 = new Aodfyddufvk;
		break;
	case N_qksdnjftja:
		temp = new Qksdnjftja;
		temp1 = new Qksdnjftja;
		break;
	case N_dusghkstja:
		temp = new Dusghkstja;
		temp1 = new Dusghkstja;
		break;
	case N_cjdfydwls:
		temp = new Cjdfydwls;
		temp1 = new Cjdfydwls;
		break;
	case N_cjdfydcnftn:
		temp = new Cjdfydcnftn;
		temp1 = new Cjdfydcnftn;
		break;
	case N_ghltjsckd:
		temp = new Ghltjsckd;
		temp1 = new Ghltjsckd;
		break;
	case N_dmsgkdbtjdxks:
		temp = new Dmsgkdbtjdxks;
		temp1 = new Dmsgkdbtjdxks;
		break;
	default:
		temp = nullptr;
		temp1 = nullptr;
		break;
	}

	card[cardCount++] = temp;
	card[cardCount++] = temp1;
}

void drawCard() {
	int randNum;
	bool keepIn = true;
	if(cardCount - (handCardCount + deadCardCount) != 0)
		while (keepIn) {
			//cardCount �̳��� ���� �ϳ��� �޾ƿ�
			randNum = getRand(cardCount);

			//true�� ���� �� �ִ�.
			if (card[randNum]->isValid == true) {
				handCard[handCardCount++] = card[randNum];
				card[randNum]->isValid = false;
				keepIn = false;
			}
		}
}

void drawCard(bool attention) {
	int cardIndex[30];
	if (attention) {//����ī�� ������
		int j = 0, index;
		for (int i = 0; i < cardCount; i++)
		{
			if (card[i]->cardname <= 3 && card[i]->isValid == true) {
				cardIndex[j] = i;
				j++;
			}
		}
		if (j != 0) {
			index = cardIndex[getRand(j)];
			handCard[handCardCount++] = card[index];
			card[index]->isValid = false;
		}
	}
	else {		//����ī�������
		int j = 0, index;
		for (int i = 0; i < cardCount; i++)
		{
			if (card[i]->cardname >= 4 && card[i]->isValid == true) {
				cardIndex[j] = i;
				j++;
			}
		}
		if (j != 0) {
			index = cardIndex[getRand(j)];
			handCard[handCardCount++] = card[index];
			card[index]->isValid = false;
		}
	}
}

void setCardPoint() {
	if (handCardCount * 187 > 900) {
		int cardTerm = 900 / handCardCount;
		for (int i = 0; i < handCardCount; i++)
		{
			handCard[i]->point.x = 300 + (cardTerm * i);
			handCard[i]->point.y = 800;
		}
	}
	else {
		int temp = handCardCount / 2;
		if (handCardCount % 2 == 0) {
			for (int i = 0; i < handCardCount; i++)
			{
				handCard[i]->point.x = 800 + (187 * (i - temp));
				handCard[i]->point.y = 800;
			}
		}
		else {
			for (int i = 0; i < handCardCount; i++)
			{
				handCard[i]->point.x = 800 - 187/2 + (187 * (i - temp));
				handCard[i]->point.y = 800;
			}
		}
	}
}



