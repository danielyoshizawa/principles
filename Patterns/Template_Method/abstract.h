#pragma once
#ifndef TEMPLATE_METHOD_ABSTRACT_H
#define TEMPLATE_METHOD_ABSTRACT_H

class Abstract
{
protected:
    int plus10; // The implementation changes this value but the TemplateMethod is called on Abstract
public:
    virtual ~Abstract() = default;
    Abstract();
    virtual void TemplateMethod() = 0;
    void CallTemplateMethod();
};

#endif // TEMPLATE_METHOD_ABSTRACT_H
