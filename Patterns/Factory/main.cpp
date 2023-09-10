#include <iostream>
#include "creator.h"

// We don't even need to know about the products
void CallShowProduct(const Creator &creator)
{
    std::cout << "Calling Show Product on the Creator Interface" << std::endl;
    creator.ShowProduct();
};

int main()
{
    std::unique_ptr<Creator> creatorProdOne{new CreatorProductOne()};
    std::unique_ptr<Creator> creatorProdTwo{new CreatorProductTwo()};

    CallShowProduct(*creatorProdOne);
    CallShowProduct(*creatorProdTwo);

    return 0;
}