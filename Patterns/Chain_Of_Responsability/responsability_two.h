#pragma once
#ifndef CHAIN_OF_RESPONSABILITY_RESPONSABILITY_TWO_H
#define CHAIN_OF_RESPONSABILITY_RESPONSABILITY_TWO_H

#include "chain_interface.h"

class ResponsabilityTwo : public ChainInterface
{
public:
    virtual ~ResponsabilityTwo() = default;
    ResponsabilityTwo() = default;

    void CallResponsability(const std::string & responsability) override;
};

#endif // CHAIN_OF_RESPONSABILITY_RESPONSABILITY_TWO_H
