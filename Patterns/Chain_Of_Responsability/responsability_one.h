#pragma once
#ifndef CHAIN_OF_RESPONSABILITY_RESPONSABILITY_ONE_H
#define CHAIN_OF_RESPONSABILITY_RESPONSABILITY_ONE_H

#include "chain_interface.h"

class ResponsabilityOne : public ChainInterface
{
public:
    virtual ~ResponsabilityOne() = default;
    ResponsabilityOne() = default;

    void CallResponsability(const std::string & responsability) override;
};

#endif // CHAIN_OF_RESPONSABILITY_RESPONSABILITY_ONE_H
