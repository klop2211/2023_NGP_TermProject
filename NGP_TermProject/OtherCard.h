#pragma once
#include "Card.h"
#include "Random.h"
//=================================== = 집중============================================

class Wjrfydvh : public Card {
public:
	Wjrfydvh(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;

	virtual CImage GetImg() const { return m_cImg[0]; }
};

class Sktjsckd : public Card {
public:
	Sktjsckd(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;

	virtual CImage GetImg() const { return m_cImg[0]; }
};

class Rhlddufvk : public Card {
public:
	Rhlddufvk(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;

	virtual CImage GetImg() const { return m_cImg[0]; }
};

class Dbtjdrkdcjs : public Card {
public:
	Dbtjdrkdcjs(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;

	virtual CImage GetImg() const { return m_cImg[0]; }
};

//==========================난무======================================

class Aodfyddufvk : public Card {
public:
	Aodfyddufvk(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;

	virtual CImage GetImg() const { return m_cImg[0]; }
};

class Qksdnjftja : public Card {
public:
	Qksdnjftja(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;

	virtual CImage GetImg() const { return m_cImg[0]; }

};

class Dusghkstja : public Card {
public:
	Dusghkstja(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;

	virtual CImage GetImg() const { return m_cImg[0]; }
};

class Cjdfydwls : public Card {
public:
	Cjdfydwls(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;

	virtual CImage GetImg() const { return m_cImg[0]; }
};

class Cjdfydcnftn : public Card {
public:
	Cjdfydcnftn(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;

	virtual CImage GetImg() const { return m_cImg[0]; }
};

class Ghltjsckd : public Card {
public:
	Ghltjsckd(int** Tripord, bool a = false);

	bool once;
	bool getOnce() { return once; };

	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;

	virtual CImage GetImg() const { return m_cImg[0]; }

};

class Dmsgkdbtjdxks : public Card {
public:
	Dmsgkdbtjdxks();

	virtual CImage GetImg() const { return m_cImg[0]; }
};

Card* card[30] = { nullptr };
Card* handCard[7] = { nullptr };
int cardCount = 0;
int deadCardCount = 0;

//손에 있는 카드 수
int handCardCount = 0;


void makeCard(int randomValue, CImage namaImg, int** tripord) {
	Card* temp = nullptr;
	Card* temp1 = nullptr;
	switch (randomValue)
	{
	case (int)CardName::N_rhlddufvk:
		temp = new Rhlddufvk(tripord);
		temp1 = new Rhlddufvk(tripord);
		break;
	case (int)CardName::N_sktjsckd:
		temp = new Sktjsckd(tripord);
		temp1 = new Sktjsckd(tripord);
		break;
	case (int)CardName::N_dbtjdrkdcjs:
		temp = new Dbtjdrkdcjs(tripord);
		temp1 = new Dbtjdrkdcjs(tripord);
		break;
	case (int)CardName::N_wjrfydvh:
		temp = new Wjrfydvh(tripord);
		temp1 = new Wjrfydvh(tripord);
		break;
	case (int)CardName::N_aodfyddufvk:
		temp = new Aodfyddufvk(tripord);
		temp1 = new Aodfyddufvk(tripord);
		break;
	case (int)CardName::N_qksdnjftja:
		temp = new Qksdnjftja(tripord);
		temp1 = new Qksdnjftja(tripord);
		break;
	case (int)CardName::N_dusghkstja:
		temp = new Dusghkstja(tripord);
		temp1 = new Dusghkstja(tripord);
		break;
	case (int)CardName::N_cjdfydwls:
		temp = new Cjdfydwls(tripord);
		temp1 = new Cjdfydwls(tripord);
		break;
	case (int)CardName::N_cjdfydcnftn:
		temp = new Cjdfydcnftn(tripord);
		temp1 = new Cjdfydcnftn(tripord);
		break;
	case (int)CardName::N_ghltjsckd:
		temp = new Ghltjsckd(tripord);
		temp1 = new Ghltjsckd(tripord);
		break;
	case (int)CardName::N_dmsgkdbtjdxks:
		temp = new Dmsgkdbtjdxks();
		temp1 = new Dmsgkdbtjdxks();
		break;
	default:
		temp = nullptr;
		temp1 = nullptr;
		break;
	}

	card[cardCount++] = temp;
	card[cardCount++] = temp1;
}

void drawCard() {
	int randNum;
	bool keepIn = true;
	if (cardCount - (handCardCount + deadCardCount) != 0)
		while (keepIn) {
			//cardCount 이내의 숫자 하나를 받아옴
			randNum = RandomGen::GetRand(cardCount);

			//true면 뽑을 수 있다.
			if (card[randNum]->GetIsValid() == true) {
				handCard[handCardCount++] = card[randNum];
				card[randNum]->SetIsValid(false);
				keepIn = false;
			}
		}
}

void drawCard(bool attention) {
	int cardIndex[30];
	if (attention) {//집중카드 뽑을거
		int j = 0, index;
		for (int i = 0; i < cardCount; i++)
		{
			if ((int)card[i]->GetCardName() <= 3 && card[i]->GetIsValid() == true) {
				cardIndex[j] = i;
				j++;
			}
		}
		if (j != 0) {
			index = cardIndex[RandomGen::GetRand(j)];
			handCard[handCardCount++] = card[index];
			card[index]->SetIsValid(false);
		}
	}
	else {		//난무카드뽑을거
		int j = 0, index;
		for (int i = 0; i < cardCount; i++)
		{
			if ((int)card[i]->GetCardName() >= 4 && card[i]->GetIsValid() == true) {
				cardIndex[j] = i;
				j++;
			}
		}
		if (j != 0) {
			index = cardIndex[RandomGen::GetRand(j)];
			handCard[handCardCount++] = card[index];
			card[index]->SetIsValid(false);
		}
	}
}

void setCardPoint() {
	if (handCardCount * 187 > 900) {
		int cardTerm = 900 / handCardCount;
		for (int i = 0; i < handCardCount; i++)
		{
			handCard[i]->SetPoint(300 + (cardTerm * i), 800);
		}
	}
	else {
		int temp = handCardCount / 2;
		if (handCardCount % 2 == 0) {
			for (int i = 0; i < handCardCount; i++)
			{
				handCard[i]->SetPoint(800 + (187 * (i - temp)), 800);
			}
		}
		else {
			for (int i = 0; i < handCardCount; i++)
			{
				handCard[i]->SetPoint(800 - 187 / 2 + (187 * (i - temp)), 800);
			}
		}
	}
}



