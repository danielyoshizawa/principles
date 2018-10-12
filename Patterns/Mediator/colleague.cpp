#include "colleague.h"

Colleague::Colleague(const std::string & name) : name(name), status(false)
{

}

std::string Colleague::Name() const
{
    return name;
}

void Colleague::isOn(bool is)
{
    status = is;
}

bool Colleague::isOn() const
{
    return status;
}
