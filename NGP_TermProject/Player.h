#pragma once
#include "Object.h"
#include "StateMachine.h"
#include "SkillObject.h"

#define PLAYER_SIZE 100
#define FRAME_SPEED 6
#define PLAYER_MOVE_SPEED 170

enum Direction : BYTE { Left, Right };

class Card;

class Player :    
	public Object
{
public:
	Player();
	~Player();

	void Update(float elapsed);
	void Draw(HDC& memDc);

	void ChangeState(State<Player>* cState);
	void ChangeState(PStateName ps);

	void OnProcessingMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void UiDraw(HDC& memDc);
	void UseCard();
	void SetCardPoint();
	void DrawCard();
	void DrawCard(bool Attention);
	void PlusUltimate();
	void MakeCard(int randomValue, int** tripord);
	int	ActivatedTripordNumber(CardName cardName, int num) { return m_ppTripord[(int)cardName][num]; }
	void AddSkillObject(const SkillObject& skillObject);

public:
	CImage GetImg() const { return *m_pImg; }
	Direction GetDir() const { return m_dDir; }
	CardName GetUseCardName() const;
	int GetStunDamage() const { return m_iStunDamage; }
	int GetDamage() const { return m_iDamage; }
	int GetDestruction() const { return m_iDestruction; }
	int GetNamedDamage() const { return m_iNamedDamage; }
	int GetType() const { return m_iType; }
	PStateName GetStateName() const { return m_pStateMachine->CurrentState()->GetName(); }

	void SetDir(Direction dir) { m_dDir = dir; }
	void SetImg(const TCHAR* str);
	void SetSpeed(const int speed) { m_iSpeed = speed; }
	void SetDamage(const int damege) { m_iDamage = damege; }
	void SetStunDamage(const int stunDamage) { m_iStunDamage = stunDamage; }
	void SetDestruction(const int destruction) { m_iDestruction = destruction; }
	void SetNamedDamage(const int NamedDamage) { m_iNamedDamage = NamedDamage; }
	void SetType(const int type) { m_iType = type; }
	void SetLocation(const POINT point) {
		m_Location.x = point.x;
		m_Location.y = point.y;
	}
	void SetRectByLocation() {
		m_rRect.left = (int)m_Location.x;
		m_rRect.top = (int)m_Location.y;
		m_rRect.right = (int)m_Location.x + PLAYER_SIZE;
		m_rRect.bottom = (int)m_Location.y + PLAYER_SIZE;
	}

private:
	Direction	m_dDir;			// ����
	int			m_iSpeed;		// �̵��ӵ�
	int			m_iDamage;		// ���ݷ�(�浹�� ���ϴ� ������)
	int			m_iStunDamage;	// ����ȭ ��ġ(�������� Neutralization�̶� ǥ�������� ������ ���ܾ�ٴ� ���ذ� ���ϰ� �ٲ�
	int			m_iDestruction;	// �����ı� ��ġ
	int			m_iNamedDamage; // ���ӵ� �߰������� ���� �������� �� ��ġ�� + �Ͽ� ���
	int			m_iType;		// ���� �Ӽ� Ÿ��

	CImage*		m_pImg;			// �׸� �̹���

	int			m_iFrameMax;	// ��������Ʈ �̹����� ������ ��
	int			m_iFrameIdx;	// ���� ��������Ʈ �̹����� ������ ��ȣ
	float		m_fFrameTime;	// ���� ��������Ʈ�� ���� �ð�

	//========================================================================
	CImage* m_pUltiImg;		// ������ �̹���
	CImage* m_pDeck;		// ī�� �޸� �̹���
	CImage* m_pManaImg[2];	// ���� �̹���

	int			m_ppTripord[10][4];		// Ʈ��������
		
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

	Card*		m_pCard[30] = { nullptr };		// �� ī��
	Card*		m_pHandCard[7] = { nullptr };	// �� ī��
	////////////////////////////////////////////////////////////////////////////////


	StateMachine<Player>* m_pStateMachine;
	std::list<SkillObject> m_lSkillObjects;

};

