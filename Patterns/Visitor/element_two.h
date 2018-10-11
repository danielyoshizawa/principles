#pragma once

#include "element.h"
#include <string>
#include "visitor.h"

class ElementTwo : public Element
{
public:
    virtual ~ElementTwo() = default;
    ElementTwo() = default;

    void Accept(Visitor * visitor) override;
    std::string GetNameElementTwo() const;
};
