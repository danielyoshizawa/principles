#pragma once
#ifndef STATE_CONTEXT_H
#define STATE_CONTEXT_H

class State;
class Context
{
private:
    State * currentState;
public:
    virtual ~Context() = default;
    Context();
    void ChangeToState(State * newState);
    void FirstOperation();
    void SecondOperation();
};

#endif // STATE_CONTEXT_H
