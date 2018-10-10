#pragma once
#ifndef OBSERVER_SUBJECT_H
#define OBSERVER_SUBJECT_H

#include "observer.h"
#include <vector>

class Subject
{
private:
    std::vector<Observer *> observersVector;
public:
    virtual ~Subject() = default;
    Subject() = default;
    void Register(Observer * observer);
    void Unregister(Observer * observer);
    void Notify();
};

#endif // OBSERVER_SUBJECT_H
