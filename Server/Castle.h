#pragma once

// RECT 전방선언
struct tagRECT;

class Castle
{
public:
	Castle();
	~Castle();

	// TODO: 게임 종료 판정 추가 필요
	void GetDamage(int hp);

public:
	int GetMaxHp() { return m_iMaxHp; }
	int GetCurrnetHp() {return m_iCurrentHp;}
	tagRECT GetBB() { return *m_pBoundingBox; }

	void SetMaxHp(int hp) { m_iMaxHp = hp; }
	void SetCurrentHp(int hp) { m_iCurrentHp = hp; };

private:
	int m_iMaxHp;
	int m_iCurrentHp;
	tagRECT* m_pBoundingBox;
};

