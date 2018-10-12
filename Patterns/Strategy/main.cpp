#include "context.h"
#include "strategy_plus_one.h"
#include "strategy_plus_ten.h"
#include <memory>

int main(int argc, char **argv)
{
    auto context = std::unique_ptr<Context>{ std::make_unique<Context>() };
    auto plusOne = std::unique_ptr<StrategyPlusOne>{ std::make_unique<StrategyPlusOne>() };
    auto plusTen = std::unique_ptr<StrategyPlusTen>{ std::make_unique<StrategyPlusTen>() };

    context->SetStrategy(plusOne.get());
    context->UseStrategy();

    context->SetStrategy(plusTen.get());
    context->UseStrategy();

    return 0;
}
