#pragma once
#ifndef STATE_STATE_ONE_H
#define STATE_STATE_ONE_H

#include "state.h"

class Context;
class StateOne : public State
{
public:
    virtual ~StateOne() = default;
    StateOne() = default;

    void FirstOperation(Context * context) override;
    void SecondOperation(Context * context) override;
};

#endif // STATE_STATE_ONE_H
