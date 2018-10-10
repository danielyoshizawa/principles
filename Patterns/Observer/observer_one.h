#pragma once
#ifndef OBSERVER_OBSERVER_ONE_H
#define OBSERVER_OBSERVER_ONE_H

#include "observer.h"

class ObserverOne : public Observer
{
public:
    virtual ~ObserverOne() = default;
    void Update() override;
};

#endif // OBSERVER_OBSERVER_ONE_H
