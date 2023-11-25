#pragma once
#include "State.h"

template<class entity_type>
class StateMachine
{
	entity_type* m_pOwner;

	State<entity_type>* m_pCurrentState;

	State<entity_type>* m_pPreviousState;

public:

    StateMachine(entity_type* owner) :
        m_pOwner(owner),
        m_pCurrentState(NULL),
        m_pPreviousState(NULL)
    {}

    virtual ~StateMachine() {}

    //use these methods to initialize the FSM
    void SetCurrentState(State<entity_type>* s) { m_pCurrentState = s; }
    void SetPreviousState(State<entity_type>* s) { m_pPreviousState = s; }

    //call this to update the FSM
    void  Update(float elapsed)const
    {
        //same for the current state
        if (m_pCurrentState) m_pCurrentState->Execute(m_pOwner, elapsed);
    }

    //change to a new state
    void  ChangeState(State<entity_type>* pNewState)
    {

        //keep a record of the previous state
        m_pPreviousState = m_pCurrentState;

        //call the exit method of the existing state
        m_pCurrentState->Exit(m_pOwner);

        //change state to the new state
        m_pCurrentState = pNewState;

        //call the entry method of the new state
        m_pCurrentState->Enter(m_pOwner);
    }

    //change state back to the previous state
    void  RevertToPreviousState()
    {
        ChangeState(m_pPreviousState);
    }

    //returns true if the current state's type is equal to the type of the
    //class passed as a parameter. 
    bool  isInState(const State<entity_type>& st)const
    {
        return typeid(*m_pCurrentState) == typeid(st);
    }

    State<entity_type>* CurrentState()  const { return m_pCurrentState; }
    State<entity_type>* PreviousState() const { return m_pPreviousState; }


};

