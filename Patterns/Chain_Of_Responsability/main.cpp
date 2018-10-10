#include "responsability_one.h"
#include "responsability_two.h"
#include "responsability_three.h"

int main(int argc, char **argv)
{
    auto responsabilityOne = std::unique_ptr<ResponsabilityOne>{ std::make_unique<ResponsabilityOne>()};
    auto responsabilityTwo = std::unique_ptr<ResponsabilityTwo>{ std::make_unique<ResponsabilityTwo>()};
    auto responsabilityThree = std::unique_ptr<ResponsabilityThree>{ std::make_unique<ResponsabilityThree>()};

    responsabilityOne->setNextInChain(responsabilityTwo.get());
    responsabilityTwo->setNextInChain(responsabilityThree.get());

    responsabilityOne->CallResponsability("one");
    responsabilityOne->CallResponsability("two");
    responsabilityOne->CallResponsability("three");
    responsabilityOne->CallResponsability("four");

    return 0;
}
