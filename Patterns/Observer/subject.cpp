#include "subject.h"

void Subject::Register(Observer * observer)
{
    observersVector.push_back(observer);
}

void Subject::Unregister(Observer * observer)
{
    observersVector.erase(std::remove(observersVector.begin(), observersVector.end(), observer), observersVector.end());
}

void Subject::Notify()
{
    for (auto observer : observersVector)
    {
        observer->Update();
    }
}
