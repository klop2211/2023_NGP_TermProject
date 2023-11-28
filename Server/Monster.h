#pragma once
class Monster
{
public:
	virtual void Update(float ElaspedTime) = 0;
	virtual bool IsDead(int Damage);

	//TODO: Collision check
protected:
	int m_iHp;

};

