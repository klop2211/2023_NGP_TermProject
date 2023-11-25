#pragma once
#include "Object.h"
#include "StateMachine.h"

#define PLAYER_SIZE 100

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
	virtual CImage GetImg() const { return *m_pImg; }
	Direction GetDir() const { return m_dDir; }

	void SetDir(Direction dir) { m_dDir = dir; }
	void SetImg(const TCHAR* str);
	void SetSpeed(const int speed) { m_iSpeed = speed; }
private:
	Direction	m_dDir;			// 방향
	int			m_iSpeed;		// 이동속도
	CImage*		m_pImg;			// 그릴 이미지

	int			m_iFrameMax;	// 스프라이트 이미지의 프레임 수
	int			m_iFrameIdx;	// 현재 스프라이트 이미지의 프레임 번호

	StateMachine<Player>* m_pStateMachine;

};

