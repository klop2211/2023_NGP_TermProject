#pragma once

class Card {
public:
	POINT point;
	CImage img[4];			//카드, 트포3개
	CImage effect, skill;
	RECT rect[4];
	TCHAR nameStr[11];
	TCHAR str[4][100];
	bool isValid, cheep;
	CardName cardname;
	int damage, Mana, destruction, neutralization;
	//피해수치 마나 부파수치 무력화수치

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

//====================================집중============================================

class Wjrfydvh : public Card {
public:

	Wjrfydvh() : Card() {
		__init__();
	}

	void setTier1() {
		switch (Tripord[N_wjrfydvh][0])
		{
		case 1:
			img[R_tier1].Load(TEXT(".//카드관련//트포//빠른준비1.jpg"));
			lstrcpy(str[1], L"빠른 준비\n차징 속도가 증가한다.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//카드관련//트포//반응속도1.jpg"));
			lstrcpy(str[1], L"사거리 증가\n공격 사거리가 증가한다.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
			lstrcpy(str[1], L"급소 타격\n적에게 주는 피해가 증가한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_wjrfydvh][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//카드관련//트포//마력조절2.jpg"));
			lstrcpy(str[2], L"마력 조절\n소모되는 마나를 감소시킨다.\n");
			cheep = true;
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//카드관련//트포//공격잇기.jpg"));
			lstrcpy(str[2], L"카드 뽑기\n무작위 난무카드를 뽑는다.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//카드관련//트포//부위파괴강화2.jpg"));
			lstrcpy(str[2], L"부위파괴 강화\n.부위 파괴 수치를 +1만큼 증가 시킨다\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_wjrfydvh][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//카드관련//트포//치명적인조준.jpg"));
			lstrcpy(str[3], L"치명적인 조준\n공중의 적에게도 피해를 입힌다.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//카드관련//트포//약점포착3.jpg"));
			lstrcpy(str[3], L"약점 포착\n보스급 적에게 주는 피해가 증가한다.\n");
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
			img[0].Load(TEXT(".//카드관련//카드//적룡포3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_wjrfydvh][1] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//적룡포2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_wjrfydvh][0] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//적룡포1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//카드관련//카드//적룡포.jpg"));

		cardname = N_wjrfydvh;
		Mana = 8 - cheep, damage = 15, neutralization = 5, destruction = 1;

		lstrcpy(nameStr, L"적룡포");
		skill.Load(TEXT(".//카드관련//스킬초상화//적룡포.png"));
		swprintf_s(str[R_main], 100, L"자세를 잡고 집중한 뒤 전방으로 창을 찔러 %d의 피해를 준다.\n부위파괴 : %d\0", damage, destruction);
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
			img[R_tier1].Load(TEXT(".//카드관련//트포//난무특화.jpg"));
			lstrcpy(str[1], L"난무 특화\n일반 적에게 입히는 피해가 증가한다.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//카드관련//트포//탁월한기동성.jpg"));
			lstrcpy(str[1], L"탁월한 기동성\n사용 후 이동속도가 증가한다.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//카드관련//트포//화력조절1.jpg"));
			lstrcpy(str[1], L"게이지 수급\n각성기 게이지를 추가 수급한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_sktjsckd][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//카드관련//트포//공격잇기.jpg"));
			lstrcpy(str[2], L"연속 공격\n이 스킬을 1회 더 사용한다.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//카드관련//트포//약점타격.jpg"));
			lstrcpy(str[2], L"약점 타격\n보스급 적에게 주는 피해가 증가한다.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//카드관련//트포//공격잇기.jpg"));
			lstrcpy(str[2], L"카드 뽑기\n무작위 난무카드를 뽑는다\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_sktjsckd][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//카드관련//트포//기술강화.jpg"));
			lstrcpy(str[3], L"기술 강화\n스킬의 사거리가 증가한다.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//카드관련//트포//치명적인조준.jpg"));
			lstrcpy(str[3], L"강화된 창\n데미지가 감소하지만, 맵끝까지 날라가는 창을 던진다.\n");
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
			img[0].Load(TEXT(".//카드관련//카드//나선창3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_sktjsckd][1] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//나선창2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_sktjsckd][0] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//나선창1.png"));
			setTier1();
		}
		else {
			img[0].Load(TEXT(".//카드관련//카드//나선창.jpg"));
		}
		cardname = N_sktjsckd;
		Mana = 1, damage = 7, neutralization = 5, destruction = 0;

		lstrcpy(nameStr, L"나선창");
		skill.Load(TEXT(".//카드관련//스킬초상화//나선창.png"));
		swprintf_s(str[R_main], 100, L"창으로 간결하게 찔러 %d의 피해를 준다.\n\0", damage);
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
			img[R_tier1].Load(TEXT(".//카드관련//트포//부위파괴강화1.jpg"));
			lstrcpy(str[1], L"부위파괴 강화\n부위 파괴 수치를 +1만큼 증가 시킨다.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//카드관련//트포//빠른준비1.jpg"));
			lstrcpy(str[1], L"공격 속도 증가\n공격 속도가 증가한다.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//카드관련//트포//탁월한기동성.jpg"));
			lstrcpy(str[1], L"탁월한 기동성\n사용 후 이동속도가 증가한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_rhlddufvk][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//카드관련//트포//화염회전.jpg"));
			lstrcpy(str[2], L"화염 회전\n적중한 적에게 화상을 부여한다.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//카드관련//트포//절대방어.jpg"));
			lstrcpy(str[2], L"절대 방어\n적중한 적을 창 끝까지 밀쳐낸다.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//카드관련//트포//약점타격.jpg"));
			lstrcpy(str[2], L"데미지 증가\n보스급 적에게 주는 피해가 증가한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_rhlddufvk][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//카드관련//트포//돌격베기.jpg"));
			lstrcpy(str[3], L"차지 강화\n차징 스킬로 바뀌고 주는 피해와 사거리가 증가한다.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//카드관련//트포//마력조절3.jpg"));
			lstrcpy(str[3], L"마력 조절\n소모되는 마나를 감소시킨다.\n");
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
			img[0].Load(TEXT(".//카드관련//카드//굉열파3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_rhlddufvk][1] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//굉열파2.png"));
			setTier1();
			setTier2();
		}
		else if (Tripord[N_rhlddufvk][0] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//굉열파1.png"));
			setTier1();
		}
		else {
			img[0].Load(TEXT(".//카드관련//카드//굉열파.jpg"));
		}

		cardname = N_rhlddufvk;
		Mana = 3 - cheep, damage = 10, neutralization = 5, destruction = 1;

		lstrcpy(nameStr, L"굉열파");
		skill.Load(TEXT(".//카드관련//스킬초상화//굉열파.png"));
		swprintf_s(str[R_main], 100, L"창에 기를 모아 가까운 적에게 %d피해를 준다.\n부위파괴 : %d\0", damage, destruction);
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
			img[R_tier1].Load(TEXT(".//카드관련//트포//빠른준비1.jpg"));
			lstrcpy(str[1], L"빠른 공격\n공격 속도가 증가한다.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//카드관련//트포//난무특화.jpg"));
			lstrcpy(str[1], L"난무 특화\n일반 적에게 입히는 피해가 증가한다.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//카드관련//트포//약점포착1.jpg"));
			lstrcpy(str[1], L"약점 포착\n보스급 적에게 주는 피해가 증가한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_dbtjdrkdcjs][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//카드관련//트포//기절효과.jpg"));
			lstrcpy(str[2], L"기절 공격\n적중한 적을 기절시킨다.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//카드관련//트포//화염회전.jpg"));
			lstrcpy(str[2], L"화염 지대\n착지 위치에 화상을 부여하는 화염지대를 생성한다.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//카드관련//트포//대지파괴.jpg"));
			lstrcpy(str[2], L"대지 생성\n착지 테두리에 적의 접근을 막는 벽을 생성한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_dbtjdrkdcjs][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//카드관련//트포//강력한마무리.jpg"));
			lstrcpy(str[3], L"강화 착지\n착지 후 좌우로 창이 떨어진다.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//카드관련//트포//치명적인조준.jpg"));
			lstrcpy(str[3], L"마술 투창\n점프를 하지 않으며, 창을 하늘에서 떨어지게 한다.\n");
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
			img[0].Load(TEXT(".//카드관련//카드//유성강천3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_dbtjdrkdcjs][1] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//유성강천2.png"));
			setTier1();
			setTier2();
		}
		else if (Tripord[N_dbtjdrkdcjs][0] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//유성강천1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//카드관련//카드//유성강천.jpg"));

		cardname = N_dbtjdrkdcjs;
		Mana = 7, damage = 12, neutralization = 5, destruction = 0;

		lstrcpy(nameStr, L"유성강천");
		skill.Load(TEXT(".//카드관련//스킬초상화//유성강천.png"));
		swprintf_s(str[R_main], 100, L"위로 점프하여 내리 꽂아 충격파를 일으켜 %d의 피해를 준다.\n\0", damage);
	}
};

//==========================난무======================================

class Aodfyddufvk : public Card {
public:
	Aodfyddufvk() : Card() {
		__init__();
	}

	void setTier1() {
		switch (Tripord[N_aodfyddufvk][0])
		{
		case 1:
			img[R_tier1].Load(TEXT(".//카드관련//트포//넓은공격.jpg"));
			lstrcpy(str[1], L"넓은 공격\n공격 범위가 증가한다.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//카드관련//트포//뇌진탕.jpg"));
			lstrcpy(str[1], L"뇌진탕\n적에게 주는 무력화가 증가한다.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
			lstrcpy(str[1], L"급소 타격\n적에게 주는 피해가 증가한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_aodfyddufvk][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//카드관련//트포//빠른준비2.jpg"));
			lstrcpy(str[2], L"공격 속도 증가\n공격 속도가 증가한다.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//카드관련//트포//냉기회전.jpg"));
			lstrcpy(str[2], L"수속성 부여\n적중한 적에게 빙결을 부여한다.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//카드관련//트포//화염회전.jpg"));
			lstrcpy(str[2], L"화속성 부여\n적중한 적에게 화상을 부여한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_aodfyddufvk][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//카드관련//트포//공격잇기3.jpg"));
			lstrcpy(str[3], L"연속 공격\n이 스킬을 1회 더 사용한다.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//카드관련//트포//마력조절3.jpg"));
			lstrcpy(str[3], L"마력 조절\n소모되는 마나를 감소시킨다.\n");
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
			img[0].Load(TEXT(".//카드관련//카드//맹룡열파3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_aodfyddufvk][1] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//맹룡열파2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_aodfyddufvk][0] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//맹룡열파1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//카드관련//카드//맹룡열파.jpg"));

		cardname = N_aodfyddufvk;
		Mana = 6 - cheep, damage = 10, neutralization = 15, destruction = 0;

		lstrcpy(nameStr, L"맹룡열파");
		skill.Load(TEXT(".//카드관련//스킬초상화//맹룡열파.png"));
		swprintf_s(str[R_main], 100, L"더욱 큰 창으로 바뀌고 크게 휘둘러 %d의 피해를 준다.\n무력화 : 중\0", damage);
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
			img[R_tier1].Load(TEXT(".//카드관련//트포//부위파괴강화1.jpg"));
			lstrcpy(str[1], L"부위파괴 강화\n부위 파괴 수치를 +1만큼 증가 시킨다.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
			lstrcpy(str[1], L"급소 타격\n적에게 주는 피해가 증가한다.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//카드관련//트포//탁월한기동성.jpg"));
			lstrcpy(str[1], L"탁월한 기동성\n스킬의 전진 거리가 증가한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_qksdnjftja][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//카드관련//트포//뇌진탕2.jpg"));
			lstrcpy(str[2], L"뇌진탕\n적에게 주는 무력화가 증가한다.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//카드관련//트포//약점타격.jpg"));
			lstrcpy(str[2], L"약점 타격\n보스급 적에게 주는 피해가 증가한다.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//카드관련//트포//마력조절2.jpg"));
			lstrcpy(str[2], L"마력 조절\n소모되는 마나를 감소시킨다.\n");
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
			img[R_tier3].Load(TEXT(".//카드관련//트포//강력한마무리.jpg"));
			lstrcpy(str[3], L"밀고 나가기\n보는 방향으로 돌진하며 일반몹을 끌고간다.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//카드관련//트포//날이선일격.jpg"));
			lstrcpy(str[3], L"회오리 생성\n마무리 공격이 회오리를 생성한다.\n");
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
			img[0].Load(TEXT(".//카드관련//카드//반월섬3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_qksdnjftja][1] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//반월섬2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_qksdnjftja][0] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//반월섬1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//카드관련//카드//반월섬.jpg"));

		cardname = N_qksdnjftja;
		Mana = 7 - cheep, damage = 12, neutralization = 20; destruction = 2;

		lstrcpy(nameStr, L"반월섬");
		skill.Load(TEXT(".//카드관련//스킬초상화//반월섬.png"));
		swprintf_s(str[R_main], 100, L"전방으로 긴창을 바닥에 끌면서 이동하여 %d의 피해를 준다.\n무력화 : 중상\0", damage);
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
			img[R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
			lstrcpy(str[1], L"급소 타격\n전진하지 않으며, 적에게 주는 피해가 증가한다.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//카드관련//트포//탁월한기동성.jpg"));
			lstrcpy(str[1], L"탁월한 기동성\n스킬의 전진 거리가 증가한다.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//카드관련//트포//화력조절1.jpg"));
			lstrcpy(str[1], L"게이지 수급\n각성기 게이지를 추가 수급한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_dusghkstja][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//카드관련//트포//빠른준비2.jpg"));
			lstrcpy(str[2], L"공격 속도 증가\n공격 속도가 증가한다.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//카드관련//트포//뇌진탕.jpg"));
			lstrcpy(str[2], L"뇌진탕\n적에게 주는 무력화가 증가한다.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//카드관련//트포//파괴하는창.jpg"));
			lstrcpy(str[2], L"파괴하는 창\n적에게 주는 피해가 증가한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_dusghkstja][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//카드관련//트포//강력한마무리.jpg"));
			lstrcpy(str[3], L"카드 뽑기\n카드를 한 장 뽑지만, 소모되는 마나를 증가시킨다.\n");
			cheep = true;
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//카드관련//트포//광휘의창.jpg"));
			lstrcpy(str[3], L"검기 생성\n공격이 검기를 생성하지만, 소모되는 마나를 증가시킨다.\n");
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
			img[0].Load(TEXT(".//카드관련//카드//연환섬3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_dusghkstja][1] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//연환섬2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_dusghkstja][0] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//연환섬1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//카드관련//카드//연환섬.jpg"));

		cardname = N_dusghkstja;
		Mana = 2 + cheep, damage = 6, neutralization = 5, destruction = 1;

		lstrcpy(nameStr, L"연환섬");
		skill.Load(TEXT(".//카드관련//스킬초상화//연환섬.png"));
		swprintf_s(str[R_main], 100, L"창을 위로 올려친 후 앞으로 전진하여 베기공격을하여 %d의 피해를 준다.\n부위파괴 : %d\0", damage, destruction);
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
			img[R_tier1].Load(TEXT(".//카드관련//트포//뇌진탕.jpg"));
			lstrcpy(str[1], L"뇌진탕\n적에게 주는 무력화가 증가한다.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
			lstrcpy(str[1], L"급소 타격\n적에게 주는 피해가 증가한다.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//카드관련//트포//넓은공격.jpg"));
			lstrcpy(str[1], L"넓은 공격\n공격 범위가 증가한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_cjdfydwls][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//카드관련//트포//내려치는창.jpg"));
			lstrcpy(str[2], L"창 소환\n창을 찍지 않는 대신 창을 소환하여 떨군다.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//카드관련//트포//집중공략.jpg"));
			lstrcpy(str[2], L"집중 공격\n공격 범위가 감소하지만, 데미지가 크게 증가한다.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//카드관련//트포//대지파괴.jpg"));
			lstrcpy(str[2], L"토속성 부여\n적의 접근을 막는 벽을 생성한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_cjdfydwls][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//카드관련//트포//공격잇기3.jpg"));
			lstrcpy(str[3], L"카드 뽑기\n카드를 한 장 뽑는다.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//카드관련//트포//마력조절3.jpg"));
			lstrcpy(str[3], L"마력 조절\n소모되는 마나를 감소시킨다.\n");
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
			img[0].Load(TEXT(".//카드관련//카드//청룡진3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_cjdfydwls][1] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//청룡진2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_cjdfydwls][0] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//청룡진1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//카드관련//카드//청룡진.jpg"));

		cardname = N_cjdfydwls;
		Mana = 1 - cheep, damage = 5, neutralization = 5, destruction = 1;

		lstrcpy(nameStr, L"청룡진");
		skill.Load(TEXT(".//카드관련//스킬초상화//청룡진.png"));
		swprintf_s(str[R_main], 100, L"제자리에서 창을 강하게 내려찍어 충격파가 퍼져 %d의 피해를 준다.\n부위파괴 : %d\0", damage, destruction);
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
			img[R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
			lstrcpy(str[1], L"급소 타격\n적에게 주는 피해가 증가한다.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//카드관련//트포//치명적인공격.jpg"));
			lstrcpy(str[1], L"공격 강화\n돌진을 하지 않지만, 데미지가 크게 증가한다.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//카드관련//트포//탁월한기동성.jpg"));
			lstrcpy(str[1], L"탁월한 기동성\n사용 후 이동속도가 증가한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_cjdfydcnftn][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//카드관련//트포//나선찌르기.jpg"));
			lstrcpy(str[2], L"풍속성 부여\n위 아래 적을 끌어당긴다.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//카드관련//트포//화력조절2.jpg"));
			lstrcpy(str[2], L"게이지 수급\n각성기 게이지를 추가 수급한다.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//카드관련//트포//넓은타격.jpg"));
			lstrcpy(str[2], L"넓은 공격\n공격 범위가 증가한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_cjdfydcnftn][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//카드관련//트포//돌격베기.jpg"));
			lstrcpy(str[3], L"창 설치\n회전하는 창을 설치한다.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//카드관련//트포//날이선일격.jpg"));
			lstrcpy(str[3], L"위성\n공격 후 주인공 주위를 도는 작은 창을 생성한다.\n");
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
			img[0].Load(TEXT(".//카드관련//카드//청룡출수3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_cjdfydcnftn][1] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//청룡출수2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_cjdfydcnftn][0] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//청룡출수1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//카드관련//카드//청룡출수.jpg"));

		cardname = N_cjdfydcnftn;
		Mana = 3, damage = 5, neutralization = 15, destruction = 0;

		lstrcpy(nameStr, L"청룡출수");
		skill.Load(TEXT(".//카드관련//스킬초상화//청룡출수.png"));
		swprintf_s(str[R_main], 100, L"전방으로 전진한 후 창을 빠르게 휘둘러 %d의 피해를 준다.\n무력화 : 중\0", damage);
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
			img[R_tier1].Load(TEXT(".//카드관련//트포//탁월한기동성.jpg"));
			lstrcpy(str[1], L"탁월한 기동성\n사용 후 이동속도가 증가한다.\n");
			break;
		case 2:
			img[R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
			lstrcpy(str[1], L"급소 타격\n적에게 주는 피해가 증가한다.\n");
			break;
		case 3:
			img[R_tier1].Load(TEXT(".//카드관련//트포//회전올려치기.jpg"));
			lstrcpy(str[1], L"빠른 마무리\n1회만 회전한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier2() {
		switch (Tripord[N_ghltjsckd][1])
		{
		case 1:
			img[R_tier2].Load(TEXT(".//카드관련//트포//정신파괴.jpg"));
			lstrcpy(str[2], L"강한 바람\n마지막 공격이 적을 눕힌다.\n");
			break;
		case 2:
			img[R_tier2].Load(TEXT(".//카드관련//트포//약점타격.jpg"));
			lstrcpy(str[2], L"약점 타격\n보스급 적에게 주는 피해가 증가한다.\n");
			break;
		case 3:
			img[R_tier2].Load(TEXT(".//카드관련//트포//화력조절2.jpg"));
			lstrcpy(str[2], L"게이지 수급\n각성기 게이지를 추가 수급한다.\n");
			break;
		default:
			break;
		}
	}

	void setTier3() {
		switch (Tripord[N_ghltjsckd][2])
		{
		case 1:
			img[R_tier3].Load(TEXT(".//카드관련//트포//연속회전.jpg"));
			lstrcpy(str[3], L"연속 공격\n이 카드를 1회 가져온다.\n");
			break;
		case 2:
			img[R_tier3].Load(TEXT(".//카드관련//트포//공격잇기3.jpg"));
			lstrcpy(str[3], L"카드 뽑기\n덱에서 무작위 집중 카드를 1장 뽑는다.\n");
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
			img[0].Load(TEXT(".//카드관련//카드//회선창3.png"));
			setTier3();
			setTier2();
			setTier1();
		}
		else if (Tripord[N_ghltjsckd][1] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//회선창2.png"));
			setTier2();
			setTier1();
		}
		else if (Tripord[N_ghltjsckd][0] != 0) {
			img[0].Load(TEXT(".//카드관련//카드//회선창1.png"));
			setTier1();
		}
		else
			img[0].Load(TEXT(".//카드관련//카드//회선창.jpg"));

		cardname = N_ghltjsckd;
		Mana = 5, damage = 9, neutralization = 10, destruction = 0;

		lstrcpy(nameStr, L"회선창");
		skill.Load(TEXT(".//카드관련//스킬초상화//회선창.png"));
		swprintf_s(str[R_main], 100, L"전방으로 회전하여 %d의 피해를 준다.\n무력화 : 하\0", damage);
	}
};

class Dmsgkdbtjdxks : public Card {
public:
	Dmsgkdbtjdxks() : Card() {
		//if (Tripord[N_dmsgkdbtjdxks][2] != 0)
		//	img[0].Load(TEXT(".//카드관련//카드//은하유성탄3.png"));
		//else if (Tripord[N_dmsgkdbtjdxks][1] != 0)
		//	img[0].Load(TEXT(".//카드관련//카드//은하유성탄2.png"));
		//else if (Tripord[N_dmsgkdbtjdxks][0] != 0)
		//	img[0].Load(TEXT(".//카드관련//카드//은하유성탄1.png"));
		//else
			img[0].Load(TEXT(".//카드관련//카드//은하유성탄.jpg"));

		cardname = N_dmsgkdbtjdxks;
		Mana = 10, damage = 20, neutralization = 40, destruction = 2;

		lstrcpy(nameStr, L"은하유성탄");
		skill.Load(TEXT(".//카드관련//스킬초상화//은하유성탄.png"));
		swprintf_s(str[R_main], 100, L"위로 점프한 후 창을 던진다. 창이 땅에 떨어지면 %d의 피해를 주고 서서히 폭발한다.\n부위파괴 : %d, 무력화 : 최상\0", damage, destruction);
	}
};

Card* card[30] = { nullptr };
Card* handCard[7] = {nullptr};
int cardCount = 0;
int deadCardCount = 0;

//손에 있는 카드 수
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
			//cardCount 이내의 숫자 하나를 받아옴
			randNum = getRand(cardCount);

			//true면 뽑을 수 있다.
			if (card[randNum]->isValid == true) {
				handCard[handCardCount++] = card[randNum];
				card[randNum]->isValid = false;
				keepIn = false;
			}
		}
}

void drawCard(bool attention) {
	int cardIndex[30];
	if (attention) {//집중카드 뽑을거
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
	else {		//난무카드뽑을거
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



