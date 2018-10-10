#pragma once
#ifndef TEMPLATE_METHOD_IMPLEMENTATION_H
#define TEMPLATE_METHOD_IMPLEMENTATION_H

#include "abstract.h"

class Implementation : public Abstract
{
public:
    virtual ~Implementation() = default;
    Implementation() = default;
    void TemplateMethod() override;
};

#endif // TEMPLATE_METHOD_IMPLEMENTATION_H
