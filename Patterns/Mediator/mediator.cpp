#include "mediator.h"
#include "colleague.h"
#include <iostream>

void Mediator::AddColleague(Colleague * colleague)
{
    colleagueVector.push_back(colleague);
}

void Mediator::CallColleague(Colleague * colleague) // Change states of the colleagues, when one is On the others are Off.
{
    auto found = std::find(std::begin(colleagueVector), std::end(colleagueVector), colleague);

    if (found != std::end(colleagueVector))
    {
        for (auto it = std::begin(colleagueVector); it != std::end(colleagueVector); ++it)
        {
            auto tmp = *it;
            if (it == found)
            {
                tmp->isOn(true);
            }
            else
            {
                tmp->isOn(false);
            }

            std::cout << "Colleague " << tmp->Name() << " is " << std::string(tmp->isOn() ? "On" : "Off") << std::endl;
        }

        std::cout << "-------------------------------------------------------------------------" << std::endl;
    }
}
