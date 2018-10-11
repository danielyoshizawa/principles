#include "visitor_two.h"
#include "element_one.h"
#include "element_two.h"
#include <iostream>

void VisitorTwo::VisitElement(ElementOne * element)
{
    std::cout << "Visitor Two inside " << element->GetNameElementOne() << std::endl;
}

void VisitorTwo::VisitElement(ElementTwo * element)
{
    std::cout << "Visitor Two inside " << element->GetNameElementTwo() << std::endl;
}
