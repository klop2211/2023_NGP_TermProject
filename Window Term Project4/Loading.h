#pragma once
void gameLoading() {		//게임 시작전 선택화면
	CImage LoadBit, startBit, quitBit;
	static int count = 0;
	LoadBit.Load(TEXT("레온하트성.png"));
	startBit.Load(TEXT("Start.png"));
	quitBit.Load(TEXT("Quit.png"));

	hDC = GetDC(hWnd);
	if (hBit1 == NULL)
		hBit1 = CreateCompatibleBitmap(hDC, WINWIDTH, WINHEIGHT);
	memdc = CreateCompatibleDC(hDC);
	oldBit1 = (HBITMAP)SelectObject(memdc, hBit1);

	LoadBit.Draw(memdc, 0, 0, WINWIDTH, WINHEIGHT,
		0, 0, LoadBit.GetWidth(), LoadBit.GetHeight());
	startBit.Draw(memdc, 500, 550, 600, 100,
		0, 0, startBit.GetWidth(), startBit.GetHeight());
	quitBit.Draw(memdc, 500, 700, 600, 100,
		0, 0, quitBit.GetWidth(), quitBit.GetHeight());

	SelectObject(memdc, oldBit1); DeleteDC(memdc);
	ReleaseDC(hWnd, hDC);
}

void gameLoadClick(LPARAM lParam) {	// 선택화면의 클릭 처리
	int mx, my;
	mx = LOWORD(lParam);
	my = HIWORD(lParam);

	if (mx >= 500 && mx <= 1100) {
		if (my >= 550 && my <= 650) {
			changing = true;
		}
		else if (my >= 700 && my <= 800) {
			PostQuitMessage(0);
		}
	}
}

void changeLoading() {		// 게임 시작전 페이드아웃
	CImage closing;
	static int changeCount = 0;
	closing.Load(TEXT("원.png"));

	hDC = GetDC(hWnd);
	if (hBit1 == NULL)
		hBit1 = CreateCompatibleBitmap(hDC, WINWIDTH, WINHEIGHT);
	memdc = CreateCompatibleDC(hDC);
	oldBit1 = (HBITMAP)SelectObject(memdc, hBit1);
	
	closing.Draw(memdc, -200 + changeCount, -550 + changeCount, 2000 - changeCount*2, 2000 - changeCount*2,
		0, 0, closing.GetWidth(), closing.GetHeight());

	changeCount += 10;
	if (changeCount >= 1000) {
		changeCount = 0;
		start = true;
	}

	SelectObject(memdc, oldBit1); DeleteDC(memdc);
	ReleaseDC(hWnd, hDC);
}