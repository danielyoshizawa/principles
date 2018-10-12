#pragma once

#include "strategy.h"

class StrategyPlusOne : public Strategy
{
public:
    virtual ~StrategyPlusOne() = default;
    StrategyPlusOne() = default;

    int AddTo(int value) override;
};
