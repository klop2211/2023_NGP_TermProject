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

    PStateName GetName() { return PStateName::Move; }

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

    PStateName GetName() { return PStateName::Stay; }

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

    float m_fDurationTime;

public:

    static PStun* Instance();

public:

    PStateName GetName() { return PStateName::Stun; }

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

    bool m_bOnemore = false;
    bool m_bUlti = false;

public:

    static PSkill* Instance();

public:

    PStateName GetName() { return PStateName::Skill; }

    virtual void Enter(Player* player);

    virtual void Execute(Player* player, float elapsed);

    virtual void Exit(Player* player);

};


