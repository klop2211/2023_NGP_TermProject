#pragma once
BOOL Ellipse(HDC memdc, RECT r);

void changeStart() {	// 게임 시작전 페이드인
	CImage closing;
	HBRUSH hBrush, oldBrush;
	static int changeCount = 10;

	closing.Load(TEXT("원.png"));

	hDC = GetDC(hWnd);
	if (hBit1 == NULL)
		hBit1 = CreateCompatibleBitmap(hDC, WINWIDTH, WINHEIGHT);
	memdc = CreateCompatibleDC(hDC);

	oldBit1 = (HBITMAP)SelectObject(memdc, hBit1);

	BackGround[1].Draw(memdc, 0, 0, WINWIDTH, WINHEIGHT,
		0, 0, BackGround[1].GetWidth(), BackGround[1].GetHeight());
	BackGround[0].Draw(memdc, 0 , 0, 259 , 635,
		0, 0, BackGround[0].GetWidth(), BackGround[0].GetHeight());

	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, 0, 0, WINWIDTH, 450 - changeCount);
	Rectangle(memdc, 0, 0, 800 - changeCount, WINHEIGHT);
	Rectangle(memdc, changeCount * 2 + (800 - changeCount), 0, WINWIDTH, WINHEIGHT);
	Rectangle(memdc, 0, changeCount * 2 + 450 - changeCount,WINWIDTH, WINHEIGHT);
	SelectObject(memdc, oldBrush); DeleteObject(hBrush);

	closing.Draw(memdc, 800 - changeCount, 450 - changeCount, changeCount * 2, changeCount * 2,
		0, 0, closing.GetWidth(), closing.GetHeight());

	changeCount += 10;
	if (changeCount >= 1400) {
		changeCount = 0;
		changing = false;
	}

	SelectObject(memdc, oldBit1); DeleteDC(memdc);
	ReleaseDC(hWnd, hDC);
}

BOOL Ellipse(HDC memdc, RECT r) {
	return Ellipse(memdc, r.left, r.top, r.right, r.bottom);
}