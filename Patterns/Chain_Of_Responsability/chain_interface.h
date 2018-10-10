#pragma once
#ifndef CHAIN_OF_RESPONSABILITY_CHAIN_INTERFACE_H
#define CHAIN_OF_RESPONSABILITY_CHAIN_INTERFACE_H

#include <string>

class ChainInterface
{
protected:
    ChainInterface * nextInChain;
public:
    virtual ~ChainInterface() = default;
    virtual void CallResponsability(const std::string & responsability) = 0;

    void setNextInChain(ChainInterface * nextChain)
    {
        nextInChain = nextChain;
    }

};

#endif // CHAIN_OF_RESPONSABILITY_CHAIN_INTERFACE_H
