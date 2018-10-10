//
// Created by Daniel Yoshizawa on 10/9/18.
//

#pragma once
#ifndef PRINCIPLES_MANAGER_H
#define PRINCIPLES_MANAGER_H

#include <vector>
#include "iCommand.h"

class Manager
{
private:
    std::vector<ICommand *> commands_vector;
public:
    virtual ~Manager();
    Manager();
    void CallCommands();
};

#endif //PRINCIPLES_MANAGER_H
