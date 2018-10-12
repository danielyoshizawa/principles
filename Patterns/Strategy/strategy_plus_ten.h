#pragma once

#include "strategy.h"

class StrategyPlusTen : public Strategy
{
public:
    virtual ~StrategyPlusTen() = default;
    StrategyPlusTen() = default;

    int AddTo(int value) override;
};
