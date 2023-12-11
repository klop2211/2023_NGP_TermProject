#pragma once
class Shop
{
public:
	enum Price {Free, Gold5, Gold10, Gold20, Gold30};

	Shop(HWND& hWnd, HINSTANCE& Inst);
	~Shop();

	// ó�������Ҷ� ���� ���� ī���
	void StartShop(HDC& hdc);
	// ���� ����
	void ShowShop(HDC& hdc, class Player* player);
	// ���� ��ư ������ ó��
	void OnProcessingCommandMessage(HWND hWnd, WPARAM wParam, Player* player);
	// ��� ī�� ���ϱ�
	void SetRandValue();
	// ��� Ʈ�������� ���� ī�� ���ϱ�
	void SetRandValueTripord(Player* player);
private:
	CImage m_cImg;
	CImage m_cBuyButtonImg;

	HWND m_hWnd;
	HINSTANCE m_hInst;
	HBITMAP m_hPriceBitmap[5];
	HWND m_hButton[3];

	// ������ ī�带 �����ϱ� ����
	int m_iRandValue[3];
	// ī�� ����
	int m_iCardPrice[3];
	// ���� Ʈ�� ��ȣ
	int m_iTriNum[3];

	// ���� ī�� �׸���
	CImage m_cSkills[3];
	// �װ��� �ؽ�Ʈ��
	TCHAR m_tStr[3][10];
};

