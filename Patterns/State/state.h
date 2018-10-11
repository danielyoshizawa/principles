#pragma once
#ifndef STATE_STATE_H
#define STATE_STATE_H

class Context;
class State
{
public:
    virtual ~State() = default;
    virtual void FirstOperation(Context * context) = 0;
    virtual void SecondOperation(Context * context) = 0;
};

#endif // STATE_STATE_H
