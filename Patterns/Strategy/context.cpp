#include "context.h"
#include "strategy.h"
#include <iostream>
#include <string>

void Context::SetStrategy(Strategy * strategy)
{
    strategy_ = strategy;
}

void Context::UseStrategy()
{
    std::cout << "Value 5 + Strategy = " << std::to_string(strategy_->AddTo(5)) << std::endl;
}
