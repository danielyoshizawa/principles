#include "abstract.h"

#include <iostream>

Abstract::Abstract() : plus10(0)
{

}

void Abstract::CallTemplateMethod()
{
    std::cout << "Call to TemplateMethod on abstract class" << std::endl;

    TemplateMethod(); // Pure virtual implemented on implementation class

    std::cout << "plus10 now is " << plus10 << std::endl;
}
