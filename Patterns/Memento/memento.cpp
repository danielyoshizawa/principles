#include "memento.h"

Memento::Memento(const std::string & state) : state(state)
{

}

std::string Memento::State() const
{
    return state;
}
