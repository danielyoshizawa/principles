#pragma once
#ifndef OBSERVER_OBSERVER_H
#define OBSERVER_OBSERVER_H

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void Update() = 0;
};

#endif // OBSERVER_OBSERVER_H
