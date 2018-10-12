#include "mediator.h"
#include "colleague.h"

int main(int argc, char **argv)
{
    auto mediator = std::unique_ptr<Mediator>{ std::make_unique<Mediator>() };
    auto colleagueOne = std::unique_ptr<Colleague>{ std::make_unique<Colleague>("One") };
    auto colleagueTwo = std::unique_ptr<Colleague>{ std::make_unique<Colleague>("Two") };
    auto colleagueThree = std::unique_ptr<Colleague>{ std::make_unique<Colleague>("Three") };

    mediator->AddColleague(colleagueOne.get());
    mediator->AddColleague(colleagueTwo.get());
    mediator->AddColleague(colleagueThree.get());

    mediator->CallColleague(colleagueOne.get());
    mediator->CallColleague(colleagueTwo.get());
    mediator->CallColleague(colleagueThree.get());

    return 0;
}
