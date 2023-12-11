#pragma once
class Shop
{
public:
	enum Price {Free, Gold5, Gold10, Gold20, Gold30};

	Shop(HWND& hWnd, HINSTANCE& Inst);
	~Shop();

	// 처음시작할때 고르는 무료 카드들
	void StartShop(HDC& hdc);
	// 상점 띄우기
	void ShowShop(HDC& hdc, class Player* player);
	// 상점 버튼 누른거 처리
	void OnProcessingCommandMessage(HWND hWnd, WPARAM wParam, Player* player);
	// 띄울 카드 정하기
	void SetRandValue();
	// 띄울 트라이포드 포함 카드 정하기
	void SetRandValueTripord(Player* player);
private:
	CImage m_cImg;
	CImage m_cBuyButtonImg;

	HWND m_hWnd;
	HINSTANCE m_hInst;
	HBITMAP m_hPriceBitmap[5];
	HWND m_hButton[3];

	// 랜덤한 카드를 생성하기 위함
	int m_iRandValue[3];
	// 카드 가격
	int m_iCardPrice[3];
	// 상점 트포 번호
	int m_iTriNum[3];

	// 정한 카드 그림들
	CImage m_cSkills[3];
	// 그거의 텍스트들
	TCHAR m_tStr[3][10];
};

