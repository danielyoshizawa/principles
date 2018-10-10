#include "responsability_three.h"
#include <iostream>

void ResponsabilityThree::CallResponsability(const std::string & responsability)
{
    if (responsability.compare("three") == 0)
    {
        std::cout << "Responsability Three was called" << std::endl;
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
