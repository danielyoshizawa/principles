#include "state_one.h"
#include "state_two.h"
#include "context.h"
#include <iostream>

void StateOne::FirstOperation(Context * context)
{
    std::cout << "Operation from state one" << std::endl;
    auto stateTwo = std::unique_ptr<StateTwo>{ std::make_unique<StateTwo>()};
    context->ChangeToState(stateTwo.get());
}

void StateOne::SecondOperation(Context * context)
{
    std::cout << "Could not perform operation, still on state one" << std::endl;
}
