//
// Created by Daniel Yoshizawa on 10/9/18.
//
#pragma once
#ifndef PRINCIPLES_ICOMMAND_H
#define PRINCIPLES_ICOMMAND_H

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void Execute() = 0;
};

#endif //PRINCIPLES_ICOMMAND_H
