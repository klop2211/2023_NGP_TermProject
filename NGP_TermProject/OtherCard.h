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
	virtual bool GetOnce() { return once; };

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