#include "element_two.h"

void ElementTwo::Accept(Visitor * visitor)
{
    visitor->VisitElement(this);
}

std::string ElementTwo::GetNameElementTwo() const
{
    return "Element Two";
}
