#pragma once
#include "Packet.h"

class GameFramework
{
public:
	virtual bool Init() = 0;

private:
	Packet m_Packet;
};

