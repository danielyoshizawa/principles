#include "observer_one.h"
#include <iostream>

void ObserverOne::Update()
{
    std::cout << "Observer One received notification" << std::endl;
}
