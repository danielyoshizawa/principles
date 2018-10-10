//
// Created by Daniel Yoshizawa on 10/9/18.
//
#pragma once
#ifndef PRINCIPLES_OTHER_COMMAND_H
#define PRINCIPLES_OTHER_COMMAND_H

#include "iCommand.h"

class Other_Command : public ICommand
{
public:
    virtual ~Other_Command() = default;
    Other_Command() {};
    void Execute() override;
};

#endif //PRINCIPLES_OTHER_COMMAND_H
