#include "element_one.h"
#include "element_two.h"
#include "visitor_one.h"
#include "visitor_two.h"

int main(int argc, char **argv)
{
    auto visitorOne = std::unique_ptr<VisitorOne>{ std::make_unique<VisitorOne>()};
    auto visitorTwo = std::unique_ptr<VisitorTwo>{ std::make_unique<VisitorTwo>()};

    auto elementOne = std::unique_ptr<ElementOne>{ std::make_unique<ElementOne>()};
    auto elementTwo = std::unique_ptr<ElementTwo>{ std::make_unique<ElementTwo>()};

    elementOne->Accept(visitorOne.get());
    elementOne->Accept(visitorTwo.get());

    elementTwo->Accept(visitorOne.get());
    elementTwo->Accept(visitorTwo.get());

    return 0;
}
