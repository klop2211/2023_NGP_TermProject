#pragma once

class Card {
public:
	Card(CImage* manaImg);
	~Card();
private:
	POINT m_pPoint;
	RECT m_rRect[4];
	CardName m_eCardname;

	CImage m_cImg[4];			//카드, 트포3개
	CImage m_cEffect;
	CImage m_cSkill;
	CImage* m_cManaImg;

	TCHAR m_tNameStr[11];
	TCHAR m_tStr[4][100];

	//피해수치 마나 부파수치 무력화수치
	int m_iDamage, m_iMana, m_iDestruction, m_iNeutralization;
	bool m_bIsValid, m_bCheep;

	virtual void __init__() { }
	//virtual bool getOnce() { return NULL; }

	//Render
public:
	//virtual void Draw(HDC& memdc) override;
	void handDraw(HDC& memdc);
	void closeDraw(HDC& memdc);
	void dragDraw(HDC& memdc);
	void mainDraw(HDC& memdc, int tempX, int tempY);

	//Gettor, Settor
public:
	POINT GetPoint()			{ return m_pPoint; }
	RECT* GetRect()				{ return m_rRect; }
	//string* GetCardname();	// enum을 한글로 바꿔서 출력하기 위함

	int GetDamage()				{ return m_iDamage; }
	int GetMana()				{ return m_iMana; }
	int GetDestruction()		{ return m_iDestruction; }
	int GetNeutralization()		{ return m_iNeutralization; }

	bool GetIsValid()			{ return m_bIsValid; }
	bool GetCheep()				{ return m_bCheep; }
};