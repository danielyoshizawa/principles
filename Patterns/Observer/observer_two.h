#pragma once
#ifndef OBSERVER_OBSERVER_TWO_H
#define OBSERVER_OBSERVER_TWO_H

#include "observer.h"

class ObserverTwo : public Observer
{
public:
    virtual ~ObserverTwo() = default;
    void Update() override;
};

#endif // OBSERVER_OBSERVER_TWO_H
