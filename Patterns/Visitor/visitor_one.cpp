#include "visitor_one.h"
#include "element_one.h"
#include "element_two.h"
#include <iostream>

void VisitorOne::VisitElement(ElementOne * element)
{
    std::cout << "Visitor One inside " << element->GetNameElementOne() << std::endl;
}

void VisitorOne::VisitElement(ElementTwo * element)
{
    std::cout << "Visitor One inside " << element->GetNameElementTwo() << std::endl;
}
