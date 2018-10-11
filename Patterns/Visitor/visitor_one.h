#pragma once

#include "visitor.h"

class ElementOne;
class ElementTwo;
class VisitorOne : public Visitor
{
public:
    virtual ~VisitorOne() = default;
    VisitorOne() = default;

    void VisitElement(ElementOne * element) override;
    void VisitElement(ElementTwo * element) override;
};
