#include "context.h"
#include <memory>

int main(int argc, char **argv)
{
    auto context = std::unique_ptr<Context>{ std::make_unique<Context>()};
    context->SecondOperation();
    context->FirstOperation();
    context->FirstOperation();
    context->SecondOperation();
    context->SecondOperation();

    return 0;
}
