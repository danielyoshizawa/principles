#pragma once
#ifndef CHAIN_OF_RESPONSABILITY_RESPONSABILITY_THREE_H
#define CHAIN_OF_RESPONSABILITY_RESPONSABILITY_THREE_H

#include "chain_interface.h"

class ResponsabilityThree : public ChainInterface
{
public:
    virtual ~ResponsabilityThree() = default;
    ResponsabilityThree() = default;

    void CallResponsability(const std::string & responsability) override;
};

#endif // CHAIN_OF_RESPONSABILITY_RESPONSABILITY_THREE_H
