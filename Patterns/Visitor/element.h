#pragma once

#include <string>
#include "visitor.h"

class Element
{
public:
    virtual ~Element() = default;
    virtual void Accept(Visitor * visitor) = 0;
};
