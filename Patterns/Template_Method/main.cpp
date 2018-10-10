#include <iostream>

#include "implementation.h"

int main(int argc, char **argv)
{
    auto impl = std::unique_ptr<Implementation>{ std::make_unique<Implementation>()};
    impl->CallTemplateMethod();
    return 0;
}
