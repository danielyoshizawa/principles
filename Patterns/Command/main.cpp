//
// Created by Daniel Yoshizawa on 10/9/18.
//

#include "manager.h"
#include <memory>

int main(int argc, char **argv)
{
    auto manager = std::unique_ptr<Manager>{ std::make_unique<Manager>()};

    manager->CallCommands();

    return 0;
}
