#pragma once
#include "Object.h"
#include "StateMachine.h"
#include "SkillObject.h"

#define PLAYER_SIZE 100
#define FRAME_SPEED 6
#define PLAYER_MOVE_SPEED 170

typedef int(*PPint)[4];

enum Direction : BYTE { Left, Right };

class Card;
class MemoryWriteStream;

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
	void OnProcessingCommandMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void UiDraw(HDC& memDc);
	void UseCard();
	void SetCardPoint();
	void DrawCard();
	void DrawCard(bool Attention);
	void PlusUltimate();
	void MakeCard(int randomValue);
	int	ActivatedTripordNumber(CardName cardName, int num) { return m_ppTripord[(int)cardName][num]; }
	void AddSkillObject(const ObjectType& type);

	bool IsSkillMsg() { return m_bSkillCheck; }
	UseCardStateMsg* CreateUseCardStateMsg(int clientNum);
	void CreateSOLMsg(int clientNum, MemoryWriteStream* mws);

	void MinusMoney(int money) { m_iMoney -= money; }
	void AddMoney(int money) { m_iMoney += money; }
	void AddExp(int exp);
	void SetCardTripod(int cardEnum);
	void ResetCard();

public:
	CImage GetImg() const { return *m_pImg; }
	Direction GetDir() const { return m_dDir; }
	CardName GetUseCardName() const;
	int GetStunDamage() const { return m_iStunDamage; }
	int GetDamage() const { return m_iDamage; }
	int GetDestruction() const { return m_iDestruction; }
	int GetNamedDamage() const { return m_iNamedDamage; }
	int GetType() const { return m_iType; }
	int GetFrameIndex() const { return m_iFrameIdx; }
	PStateName GetStateName() const { return m_pStateMachine->CurrentState()->GetName(); }
	CardName GetCurrentCardName() const { return m_CurrentCardName; }
	int GetCardCount() const { return m_iCardCount; }
	int(*GetTripord())[4] {return m_ppTripord; }
	int GetMoney() { return m_iMoney; }
	float GetStateTime() { return m_fStateTime; }
	int GetLevel() { return m_iLevel; }
	bool GetLevelUp() { return m_bLevelUp; }
	
	void SetDir(Direction dir) { m_dDir = dir; }
	void SetImg(const TCHAR* str);
	void SetSpeed(const int speed) { m_iSpeed = speed; }
	void SetDamage(const int damege) { m_iDamage = damege; }
	void SetStunDamage(const int stunDamage) { m_iStunDamage = stunDamage; }
	void SetDestruction(const int destruction) { m_iDestruction = destruction; }
	void SetNamedDamage(const int NamedDamage) { m_iNamedDamage = NamedDamage; }
	void SetType(const int type) { m_iType = type; }
	void SetFrameIndex(const int idx) { m_iFrameIdx = idx; }
	void SetLocation(const POINT point) {
		m_Location.x = point.x;
		m_Location.y = point.y;
	}
	void SetSkillCheck(const bool b) { m_bSkillCheck = b; }
	void SetCurrentCardName() { m_CurrentCardName = GetUseCardName(); }
	void SetCurrentCardName(CardName cn) { m_CurrentCardName = cn; }
	void SetRectByLocation() {
		m_rRect.left = (int)m_Location.x;
		m_rRect.top = (int)m_Location.y;
		m_rRect.right = (int)m_Location.x + PLAYER_SIZE;
		m_rRect.bottom = (int)m_Location.y + PLAYER_SIZE;
	}
	void SetStateTime(const float time) { m_fStateTime = time; }
	void SetLevelUp(bool levelup) { m_bLevelUp = levelup; }

private:
	Direction	m_dDir;			// 방향
	int			m_iSpeed;		// 이동속도
	int			m_iDamage;		// 공격력(충돌시 가하는 데미지)
	int			m_iStunDamage;	// 무력화 수치(기존에는 Neutralization이라 표기했지만 생소한 영단어보다는 이해가 편하게 바꿈
	int			m_iDestruction;	// 부위파괴 수치
	int			m_iNamedDamage; // 네임드 추가데미지 기존 데미지에 이 수치를 + 하여 계산
	int			m_iType;		// 현재 속성 타입

	bool		m_bSkillCheck;	// 스킬 사용 및 종료시 메시지를 보내기 위한 트리거

	CImage*		m_pImg;			// 그릴 이미지

	int			m_iFrameMax;	// 스프라이트 이미지의 프레임 수
	int			m_iFrameIdx;	// 현재 스프라이트 이미지의 프레임 번호
	float		m_fFrameTime;	// 현재 스프라이트가 사용된 시간

	float		m_fStateTime;	// 현재 상태에 들어오고 지난 시간

	CardName	m_CurrentCardName; // 현재 사용중인 카드 이름

	//========================================================================
	CImage* m_pUltiImg;		// 각성기 이미지
	CImage* m_pDeck;		// 카드 뒷면 이미지
	CImage* m_pManaImg[2];	// 마나 이미지

	int			m_ppTripord[10][4];		// 트라이포드
		
	int			m_iUltimate;		// 궁극기 게이지
	int			m_iCardCount;		// 덱 카드개수 
	int			m_iHandCardCount;	// 손에있는 카드 개수
	int			m_iDeadCardCount;	// 쓴 카드 개수
	int			m_iMaxMana;			// 최대 마나
	int			m_iManaCount;		// 사용가능한 남은 마나
	int			m_iLevel;			// 레벨
	int			m_iMoney;			// 가진돈
	bool		m_bOnemore;			// 스킬 한번더 사용?
	float		m_fDrawTimer;		// 카드 뽑는 타이머
	float		m_fManaTimer;		// 마나 회복 타이머

	int			m_iExperience;			// 경험치
	int			m_iExperienceBar[10];	// 현 레벨의 경험치 최대량

	bool		m_bIsClick;				// 카드를 집고있는지
	bool		m_bCardDrawing;			// 카드를 뽑아야하는지
	bool		m_bLevelUp;				// 레벨업했는지
	int			m_iStartX, m_iStartY;	// 카드를 집은 위치
	int			m_iClickSelect;			// 잡고있는 카드
	int			m_iSelectCard;			// 마우스로 인해 커지는 카드
	POINT		m_pPrevCardPoint;		// 카드를 놓았을때 돌아가야하는 위치

	Card*		m_pCard[30] = { nullptr };		// 덱 카드
	Card*		m_pHandCard[7] = { nullptr };	// 손 카드
	////////////////////////////////////////////////////////////////////////////////


	StateMachine<Player>* m_pStateMachine;
	std::list<SkillObject> m_lSkillObjects;

};

