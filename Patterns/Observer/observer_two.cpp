#include "observer_two.h"
#include <iostream>

void ObserverTwo::Update()
{
    std::cout << "Observer Two received notification" << std::endl;
}
