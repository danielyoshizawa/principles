#include "responsability_two.h"
#include <iostream>

void ResponsabilityTwo::CallResponsability(const std::string & responsability)
{
    if (responsability.compare("two") == 0)
    {
        std::cout << "Responsability Two was called" << std::endl;
    }
    else
    {
        if (nextInChain == nullptr)
        {
            std::cout << "The end of the chain was reached" << std::endl;
            return;
        }

        nextInChain->CallResponsability(responsability);
    }


}
