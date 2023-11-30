#pragma once
#include "CommonMonster.h"

class Wolf : public CommonMonster
{
public:
	Wolf(int SN);
	~Wolf() {};

	virtual void Update(float ElaspedTime);
};

