//
// Created by Daniel Yoshizawa on 10/9/18.
//

#include "manager.h"
#include "command.h"
#include "other_command.h"

Manager::~Manager()
{
    commands_vector.erase(commands_vector.begin(), commands_vector.end());
}

Manager::Manager()
{
    commands_vector.push_back(new Command());
    commands_vector.push_back(new Other_Command());
}

void Manager::CallCommands()
{
    for (auto command : commands_vector)
    {
        command->Execute();
    }
}
