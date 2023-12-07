#pragma once

#include "StateMessage.h"

class Monster;
class Papyrus;

class MonsterState
{
public:
	virtual void Enter(Monster*) = 0;

	virtual void Execute(Monster*, float) = 0;

	virtual void Exit(Monster*) = 0;

	virtual MonsterStateType GetStateType() = 0;
};

class MonsterMoveState :public MonsterState
{
public:
	static MonsterMoveState* Instance();

	virtual void Enter(Monster*) {};

	virtual void Execute(Monster*, float);

	virtual void Exit(Monster*) {};

	virtual MonsterStateType GetStateType();
};

class MonsterAttackState :public MonsterState
{
public:
	static MonsterAttackState* Instance();

	virtual void Enter(Monster*) {};

	virtual void Execute(Monster*, float);

	virtual void Exit(Monster*) {};

	virtual MonsterStateType GetStateType();
};

// ================PAPYRUS==================
class BossState
{
public:
	virtual void Enter(Papyrus*) = 0;

	virtual void Execute(Papyrus*, float) = 0;

	virtual void Exit(Papyrus*) = 0;

	virtual BossStateType GetStateType() = 0;
};

class BossMoveState :public BossState
{
public:
	static BossMoveState* Instance();

	virtual void Enter(Papyrus*) {};

	virtual void Execute(Papyrus*, float);

	virtual void Exit(Papyrus*) {};

	virtual BossStateType GetStateType();
};

class BossUnBreakPatternState :public BossState
{
public:
	static BossUnBreakPatternState* Instance();

	virtual void Enter(Papyrus*);

	virtual void Execute(Papyrus*, float);

	virtual void Exit(Papyrus*) {};

	virtual BossStateType GetStateType();
};

class BossBreakPattern1State :public BossState
{
public:
	static BossBreakPattern1State* Instance();

	virtual void Enter(Papyrus*);

	virtual void Execute(Papyrus*, float);

	virtual void Exit(Papyrus*) {};

	virtual BossStateType GetStateType();
};

class BossBreakPattern2State :public BossState
{
public:
	static BossBreakPattern2State* Instance();

	virtual void Enter(Papyrus*);

	virtual void Execute(Papyrus*, float);

	virtual void Exit(Papyrus*) {};

	virtual BossStateType GetStateType();
};

class BossBreakingState :public BossState
{
public:
	static BossBreakingState* Instance();

	virtual void Enter(Papyrus*) {};

	virtual void Execute(Papyrus*, float);

	virtual void Exit(Papyrus*) {};

	virtual BossStateType GetStateType();
};

class BossStunningState :public BossState
{
public:
	static BossStunningState* Instance();

	virtual void Enter(Papyrus*) {};

	virtual void Execute(Papyrus*, float);

	virtual void Exit(Papyrus*) {};

	virtual BossStateType GetStateType();
};

class BossCantMoveState :public BossState
{
public:
	static BossCantMoveState* Instance();

	virtual void Enter(Papyrus*) {};

	virtual void Execute(Papyrus*, float);

	virtual void Exit(Papyrus*) {};

	virtual BossStateType GetStateType();
};