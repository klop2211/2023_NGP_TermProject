#pragma once
#include "State.h"

class Player;

class PMove :
    public State<Player>
{
private:
    PMove() {}
    PMove(const PMove&);
    PMove& operator=(const PMove&);

public:

    static PMove* Instance();

public:

    virtual void Enter(Player* player);

    virtual void Execute(Player*, float elapsed);

    virtual void Exit(Player* player);

};

class PStay :
    public State<Player>
{
private:
    PStay() {}
    PStay(const PStay&);
    PStay& operator=(const PStay&);

public:

    static PStay* Instance();

public:

    virtual void Enter(Player* player);

    virtual void Execute(Player* player, float elapsed);

    virtual void Exit(Player* player);

};

class PStun :
    public State<Player>
{
private:
    PStun() {}
    PStun(const PStun&);
    PStun& operator=(const PStun&);

public:

    static PStun* Instance();

public:

    virtual void Enter(Player* player);

    virtual void Execute(Player* player, float elapsed);

    virtual void Exit(Player* player);

};

class PSkill :
    public State<Player>
{
private:
    PSkill() {}
    PSkill(const PSkill&);
    PSkill& operator=(const PSkill&);

public:

    static PSkill* Instance();

public:

    virtual void Enter(Player* player);

    virtual void Execute(Player* player, float elapsed);

    virtual void Exit(Player* player);

};


