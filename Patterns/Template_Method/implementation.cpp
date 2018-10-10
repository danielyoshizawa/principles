#include "implementation.h"
#include <iostream>

void Implementation::TemplateMethod()
{
    std::cout << "Inside TemplateMethod on implementation class" << std::endl;
    plus10 += 10;
}
