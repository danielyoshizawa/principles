#include "responsability_one.h"
#include <iostream>

void ResponsabilityOne::CallResponsability(const std::string & responsability)
{
    if (responsability.compare("one") == 0)
    {
        std::cout << "Responsability One was called" << std::endl;
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
