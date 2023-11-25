#pragma once
#include "Object.h"
#include "StateMachine.h"

enum Direction{ Left, Right };

class Player :    
	public Object
{
public:
	Player();
	~Player();

	void Update(float elapsed);
	void Draw(HDC& memDc);

public:
	CImage GetImg() const { return *m_pImg; }
	Direction GetDir() const { return m_dDir; }

	void SetDir(Direction dir) { m_dDir = dir; }
	void SetImg(const TCHAR* str);
	void SetSpeed(const int speed) { m_iSpeed = speed; }
private:
	Direction	m_dDir;		// 방향
	int			m_iSpeed;	// 이동속도
	CImage*		m_pImg;		// 그릴 이미지
	StateMachine<Player>* m_pStateMachine;

};

