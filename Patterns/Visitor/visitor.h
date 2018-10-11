#pragma once

#include <string>

class ElementOne;
class ElementTwo;
class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void VisitElement(ElementOne * element) = 0;
    virtual void VisitElement(ElementTwo * element) = 0;
};
