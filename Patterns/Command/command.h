//
// Created by Daniel Yoshizawa on 10/9/18.
//
#pragma once
#ifndef PRINCIPLES_COMMAND_H
#define PRINCIPLES_COMMAND_H

#include "iCommand.h"

class Command : public ICommand
{
public:
    virtual ~Command() = default;
    Command() {};
    void Execute() override;
};

#endif //PRINCIPLES_COMMAND_H
