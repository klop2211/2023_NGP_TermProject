#pragma once
class Monster
{
public:
	virtual void Update(float ElaspedTime) = 0;

protected:
	int m_iHp;

};

