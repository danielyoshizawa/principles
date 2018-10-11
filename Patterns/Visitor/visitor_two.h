#pragma once

#include "visitor.h"

class ElementOne;
class ElementTwo;
class VisitorTwo : public Visitor
{
public:
    virtual ~VisitorTwo() = default;
    VisitorTwo() = default;

    void VisitElement(ElementOne * element) override;
    void VisitElement(ElementTwo * element) override;
};
