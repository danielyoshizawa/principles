#include "context.h"
#include <iostream>
#include "state_one.h"

Context::Context()
{
    auto stateOne = std::unique_ptr<StateOne>{ std::make_unique<StateOne>()};
    currentState = stateOne.get();
}

void Context::ChangeToState(State * newState)
{
    currentState = newState;
}

void Context::FirstOperation()
{
    currentState->FirstOperation(this);
}

void Context::SecondOperation()
{
    currentState->SecondOperation(this);
}
