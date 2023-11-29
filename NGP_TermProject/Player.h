#pragma once
#include "Object.h"
#include "StateMachine.h"

#define PLAYER_SIZE 100
#define FRAME_SPEED 6
#define PLAYER_MOVE_SPEED 170

enum Direction{ Left, Right };
enum ObjectType {
	Drop_Spear = 100, Meteor_Spear, Explosion, Wall, Hurricane, None, Ice, Fire, Knockdown, SowrdLight,
	Rotation_Spear, Airborne_Spear, Red_Spear, Earthquake, Flame_Zone, Drop_Red_Spear, Yellow_Spear, Purple_Spear
};

class Player :    
	public Object
{
public:
	Player();
	~Player();

	void Update(float elapsed);
	void Draw(HDC& memDc);

	void ChangeState(State<Player>* cState);

	void OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void UiDraw(HDC& memDc);
	void UseCard();
	void SetCardPoint();
	void DrawCard();
	void DrawCard(bool Attention);
	void PlusUltimate();
	void MakeCard(int randomValue, int** tripord);

public:
	virtual CImage GetImg() const { return *m_pImg; }
	Direction GetDir() const { return m_dDir; }

	void SetDir(Direction dir) { m_dDir = dir; }
	void SetImg(const TCHAR* str);
	void SetSpeed(const int speed) { m_iSpeed = speed; }
	void SetRectByLocation() {
		m_rRect.left = (int)m_Location.x;
		m_rRect.top = (int)m_Location.y;
		m_rRect.right = (int)m_Location.x + PLAYER_SIZE;
		m_rRect.bottom = (int)m_Location.y + PLAYER_SIZE;
	}

private:
	Direction	m_dDir;			// ����
	int			m_iSpeed;		// �̵��ӵ�
	CImage*		m_pImg;			// �׸� �̹���

	int			m_iFrameMax;	// ��������Ʈ �̹����� ������ ��
	int			m_iFrameIdx;	// ���� ��������Ʈ �̹����� ������ ��ȣ
	float		m_fFrameTime;	// ���� ��������Ʈ�� ���� �ð�

	//========================================================================
	CImage* m_pUltiImg;		// ������ �̹���
	CImage* m_pDeck;		// ī�� �޸� �̹���
	CImage* m_pManaImg[2];	// ���� �̹���

	int**		m_ppTripord;		// Ʈ��������
		
	int			m_iUltimate;		// �ñر� ������
	int			m_iCardCount;		// �� ī�尳�� 
	int			m_iHandCardCount;	// �տ��ִ� ī�� ����
	int			m_iDeadCardCount;	// �� ī�� ����
	int			m_iMaxMana;			// �ִ� ����
	int			m_iManaCount;		// ��밡���� ���� ����
	int			m_iLevel;			// ����
	bool		m_bOnemore;			// ��ų �ѹ��� ���?

	int			m_iExperience;			// ����ġ
	int			m_iExperienceBar[10];	// �� ������ ����ġ �ִ뷮

	bool		m_bIsClick;				// ī�带 �����ִ���
	int			m_iStartX, m_iStartY;	// ī�带 ���� ��ġ
	int			m_iClickSelect;			// ����ִ� ī��
	POINT		m_pPrevCardPoint;		// ī�带 �������� ���ư����ϴ� ��ġ

	class Card* m_pCard[30] = { nullptr };		// �� ī��
	Card*		m_pHandCard[7] = { nullptr };	// �� ī��
	////////////////////////////////////////////////////////////////////////////////


	StateMachine<Player>* m_pStateMachine;

};

