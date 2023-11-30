#pragma once
#include "CommonMonster.h"

class Bat : public CommonMonster
{
public:
	Bat(int SN);
	~Bat() {};

	virtual void Update(float ElaspedTime);
};

