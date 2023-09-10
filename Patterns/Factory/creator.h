#pragma once
#include <iostream>
#include <memory>
#include "product.h"

class Creator
{
public:
    virtual ~Creator() = default;
    virtual Product *FactoryMethod() const = 0;
    void ShowProduct() const
    {
        std::unique_ptr<Product> prod{this->FactoryMethod()}; // Template Method
        std::cout << "This is the ";
        prod->Print();
    }
};

class CreatorProductOne : public Creator
{
public:
    Product *FactoryMethod() const
    {
        return new ProductOne();
    }
};

class CreatorProductTwo : public Creator
{
public:
    Product *FactoryMethod() const
    {
        return new ProductTwo();
    }
};