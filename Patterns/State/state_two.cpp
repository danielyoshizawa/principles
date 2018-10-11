#include "state_two.h"
#include "state_one.h"
#include <iostream>
#include "context.h"

void StateTwo::FirstOperation(Context * context)
{
    std::cout << "Could not perform operation, still on state two" << std::endl;
}

void StateTwo::SecondOperation(Context * context)
{
    std::cout << "Operation from state two" << std::endl;
    auto stateOne = std::unique_ptr<StateOne>{ std::make_unique<StateOne>()};
    context->ChangeToState(stateOne.get());
}
