#pragma once

class Monster;

class MonsterState
{
public:
	//this will execute when the state is entered
	virtual void Enter(Monster*) = 0;

	//this is the state's normal update function
	virtual void Execute(Monster*, float) = 0;

	//this will execute when the state is exited. (My word, isn't
	//life full of surprises... ;o))
	virtual void Exit(Monster*) = 0;
};

class MonsterMoveState :public MonsterState
{
public:
	static MonsterMoveState* Instance();

	virtual void Enter(Monster*);

	virtual void Execute(Monster*, float);

	virtual void Exit(Monster*);
};

class MonsterAttackState :public MonsterState
{
public:
	static MonsterAttackState* Instance();

	virtual void Enter(Monster*);

	virtual void Execute(Monster*, float);

	virtual void Exit(Monster*);
};

// ================PAPYRUS==================
class BossMoveState :public MonsterState
{
public:
	static BossMoveState* Instance();

	virtual void Enter(Monster*);

	virtual void Execute(Monster*, float);

	virtual void Exit(Monster*);
};

class BossUnBreakPatternState :public MonsterState
{
public:
	static BossUnBreakPatternState* Instance();

	virtual void Enter(Monster*);

	virtual void Execute(Monster*, float);

	virtual void Exit(Monster*);
};