#pragma once

#include "element.h"
#include <string>
#include "visitor.h"

class ElementOne : public Element
{
public:
    virtual ~ElementOne() = default;
    ElementOne() = default;

    void Accept(Visitor * visitor) override;
    std::string GetNameElementOne() const;
};
