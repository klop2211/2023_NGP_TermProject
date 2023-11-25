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

	void ChangeState(State<Player>* cState);

public:
	virtual CImage GetImg() const { return *m_pImg; }
	Direction GetDir() const { return m_dDir; }

	void SetDir(Direction dir) { m_dDir = dir; }
	void SetImg(const TCHAR* str);
	void SetSpeed(const int speed) { m_iSpeed = speed; }
private:
	Direction	m_dDir;			// ����
	int			m_iSpeed;		// �̵��ӵ�
	CImage*		m_pImg;			// �׸� �̹���

	int			m_iFrameMax;	// ��������Ʈ �̹����� ������ ��
	int			m_iFrameIdx;	// ���� ��������Ʈ �̹����� ������ ��ȣ

	StateMachine<Player>* m_pStateMachine;

};

