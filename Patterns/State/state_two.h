#pragma once
#ifndef STATE_STATE_TWO_H
#define STATE_STATE_TWO_H

#include "state.h"

class Context;
class StateTwo : public State
{
public:
    virtual ~StateTwo() = default;
    StateTwo() = default;

    void FirstOperation(Context * context) override;
    void SecondOperation(Context * context) override;
};

#endif // STATE_STATE_TWO_H
