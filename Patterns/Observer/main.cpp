#include "observer_one.h"
#include "observer_two.h"
#include "subject.h"

int main(int argc, char **argv)
{
    auto obsOne = std::unique_ptr<ObserverOne> {std::make_unique<ObserverOne>()};
    auto obsTwo = std::unique_ptr<ObserverTwo> {std::make_unique<ObserverTwo>()};

    auto subject = std::unique_ptr<Subject> {std::make_unique<Subject>()};

    subject->Register(obsOne.get());
    subject->Register(obsTwo.get());

    subject->Notify();

    subject->Unregister(obsOne.get());
    subject->Unregister(obsTwo.get());

    return 0;
}
