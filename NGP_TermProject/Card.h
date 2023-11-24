#pragma once
#include "Object.h"

class Card : public Object
{
public:
	Card();
	~Card();
protected:
	POINT m_pPoint;
	RECT m_rRect[4];
	CardName m_eCardname;

	CImage m_cImg[4];			//카드, 트포3개
	CImage m_cEffect;
	CImage m_cSkill;
	static CImage m_cManaImg[2];

	TCHAR m_tNameStr[11];
	TCHAR m_tStr[4][100];

	//피해수치 마나 부파수치 무력화수치
	int m_iDamage, m_iMana, m_iDestruction, m_iNeutralization;
	bool m_bIsValid, m_bCheep;

	//카드의 트라이포드 확인
	int** m_iTripord = nullptr;

	virtual void __init__() { }
	//virtual bool getOnce() { return NULL; }

	//Render
public:
	virtual void Draw(HDC& memdc) override;
	void handDraw(HDC& memdc);
	void closeDraw(HDC& memdc);
	void dragDraw(HDC& memdc);
	void mainDraw(HDC& memdc, int tempX, int tempY);

	//Gettor, Settor
public:
	POINT GetPoint()			{ return m_pPoint; }
	RECT* GetRect()				{ return m_rRect; }
	CardName GetCardName()		{ return m_eCardname; }
	//string* GetCardname();	// enum을 한글로 바꿔서 출력하기 위함

	int GetDamage()				{ return m_iDamage; }
	int GetMana()				{ return m_iMana; }
	int GetDestruction()		{ return m_iDestruction; }
	int GetNeutralization()		{ return m_iNeutralization; }

	bool GetIsValid()			{ return GetIsValid(); }
	bool GetCheep()				{ return m_bCheep; }

	void SetIsValid(bool Valid) { m_bIsValid = Valid; }
	void SetPoint(int x, int y) { m_pPoint.x = x; m_pPoint.y = y; }
};