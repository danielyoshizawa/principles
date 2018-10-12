#include "originator.h"
#include "memento.h"

int main(int argc, char **argv)
{
    auto originator = std::unique_ptr<Originator> { std::make_unique<Originator>()};
    originator->State("State One");
    originator->State("State Two");
    auto memento = originator->Create();
    originator->State("State Three");
    originator->Restore(*memento);

    return 0;
}
