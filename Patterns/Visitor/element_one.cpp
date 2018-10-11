#include "element_one.h"

void ElementOne::Accept(Visitor * visitor)
{
    visitor->VisitElement(this);
}

std::string ElementOne::GetNameElementOne() const
{
    return "Element One";
}
