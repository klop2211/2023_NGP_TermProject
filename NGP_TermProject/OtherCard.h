#pragma once
#include "Card.h"
//=================================== = 집중============================================

class Wjrfydvh : public Card {
public:
	Wjrfydvh(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;
};

class Sktjsckd : public Card {
public:
	Sktjsckd(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;
};

class Rhlddufvk : public Card {
public:
	Rhlddufvk(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;
};

class Dbtjdrkdcjs : public Card {
public:
	Dbtjdrkdcjs(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;
};

//==========================난무======================================

class Aodfyddufvk : public Card {
public:
	Aodfyddufvk(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;
};

class Qksdnjftja : public Card {
public:
	Qksdnjftja(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;
};

class Dusghkstja : public Card {
public:
	Dusghkstja(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;
};

class Cjdfydwls : public Card {
public:
	Cjdfydwls(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;
};

class Cjdfydcnftn : public Card {
public:
	Cjdfydcnftn(int** Tripord);
	void setTier1();
	void setTier2();
	void setTier3();

	virtual void __init__() override;
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

};

class Dmsgkdbtjdxks : public Card {
public:
	Dmsgkdbtjdxks(CImage* manaImg);
};

Card* card[30] = { nullptr };
Card* handCard[7] = { nullptr };
int cardCount = 0;
int deadCardCount = 0;

//손에 있는 카드 수
int handCardCount = 0;


void makeCard(int randomValue, CImage* namaImg, int** tripord) {
	Card* temp = nullptr;
	Card* temp1 = nullptr;
	switch (randomValue)
	{
	case N_rhlddufvk:
		temp = new Rhlddufvk(namaImg, tripord);
		temp1 = new Rhlddufvk(namaImg, tripord);
		break;
	case N_sktjsckd:
		temp = new Sktjsckd(namaImg, tripord);
		temp1 = new Sktjsckd(namaImg, tripord);
		break;
	case N_dbtjdrkdcjs:
		temp = new Dbtjdrkdcjs(namaImg, tripord);
		temp1 = new Dbtjdrkdcjs(namaImg, tripord);
		break;
	case N_wjrfydvh:
		temp = new Wjrfydvh(namaImg, tripord);
		temp1 = new Wjrfydvh(namaImg, tripord);
		break;
	case N_aodfyddufvk:
		temp = new Aodfyddufvk(namaImg, tripord);
		temp1 = new Aodfyddufvk(namaImg, tripord);
		break;
	case N_qksdnjftja:
		temp = new Qksdnjftja(namaImg, tripord);
		temp1 = new Qksdnjftja(namaImg, tripord);
		break;
	case N_dusghkstja:
		temp = new Dusghkstja(namaImg, tripord);
		temp1 = new Dusghkstja(namaImg, tripord);
		break;
	case N_cjdfydwls:
		temp = new Cjdfydwls(namaImg, tripord);
		temp1 = new Cjdfydwls(namaImg, tripord);
		break;
	case N_cjdfydcnftn:
		temp = new Cjdfydcnftn(namaImg, tripord);
		temp1 = new Cjdfydcnftn(namaImg, tripord);
		break;
	case N_ghltjsckd:
		temp = new Ghltjsckd(namaImg, tripord);
		temp1 = new Ghltjsckd(namaImg, tripord);
		break;
	case N_dmsgkdbtjdxks:
		temp = new Dmsgkdbtjdxks(namaImg);
		temp1 = new Dmsgkdbtjdxks(namaImg);
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
			randNum = getRand(cardCount);

			//true면 뽑을 수 있다.
			if (card[randNum]->isValid == true) {
				handCard[handCardCount++] = card[randNum];
				card[randNum]->isValid = false;
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
			if (card[i]->cardname <= 3 && card[i]->isValid == true) {
				cardIndex[j] = i;
				j++;
			}
		}
		if (j != 0) {
			index = cardIndex[getRand(j)];
			handCard[handCardCount++] = card[index];
			card[index]->isValid = false;
		}
	}
	else {		//난무카드뽑을거
		int j = 0, index;
		for (int i = 0; i < cardCount; i++)
		{
			if (card[i]->cardname >= 4 && card[i]->isValid == true) {
				cardIndex[j] = i;
				j++;
			}
		}
		if (j != 0) {
			index = cardIndex[getRand(j)];
			handCard[handCardCount++] = card[index];
			card[index]->isValid = false;
		}
	}
}

void setCardPoint() {
	if (handCardCount * 187 > 900) {
		int cardTerm = 900 / handCardCount;
		for (int i = 0; i < handCardCount; i++)
		{
			handCard[i]->point.x = 300 + (cardTerm * i);
			handCard[i]->point.y = 800;
		}
	}
	else {
		int temp = handCardCount / 2;
		if (handCardCount % 2 == 0) {
			for (int i = 0; i < handCardCount; i++)
			{
				handCard[i]->point.x = 800 + (187 * (i - temp));
				handCard[i]->point.y = 800;
			}
		}
		else {
			for (int i = 0; i < handCardCount; i++)
			{
				handCard[i]->point.x = 800 - 187 / 2 + (187 * (i - temp));
				handCard[i]->point.y = 800;
			}
		}
	}
}



