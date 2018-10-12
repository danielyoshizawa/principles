#include "originator.h"
#include "memento.h"
#include <iostream>

void Originator::State(const std::string & state)
{
    state_ = state;
    std::cout << "Originator on State : " << state_ << std::endl;
}

Memento * Originator::Create()
{
    std::cout << "Creating Memento on state : " << state_ << std::endl;
    return new Memento(state_);
}

void Originator::Restore(const Memento & memento)
{
    std::cout << "Restoring Memento" << std::endl;
    State(memento.State());
}
