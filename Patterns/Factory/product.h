#pragma once

#include <iostream>

class Product
{
public:
    virtual ~Product() = default;
    virtual void Print() = 0;
};

class ProductOne : public Product
{
public:
    void Print() override
    {
        std::cout << "Product One" << std::endl;
    }
};

class ProductTwo : public Product
{
public:
    void Print() override
    {
        std::cout << "Product Two" << std::endl;
    }
};