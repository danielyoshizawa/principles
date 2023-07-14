#include <iostream>

struct A
{
    int a;
    double b;
    char c;
};

struct B
{
    int a;
    double b;
    char c;
} __attribute__((packed)); // Tells the compiler to use packing on this struct

#pragma pack(1) // Tells the compiler to use packing from here on

struct C
{
    int a;
    double b;
    char c; 
};

#pragma pack(0) // Tells the compiler to not use packing anymore

struct D
{
    int a;
    double b;
    char c; 
};

int main()
{
    // As we see on the Padding examples, some bytes are added
    // to the structures to align them in memory, here we show
    // 2 different techniques to avoid the padding process,
    // this is called packing.
    // Struct A and D are using padding, B and C not, 
    // the sizeof A and D is 24 bytes, while B and C is 13.
    std::cout << sizeof(A) << std::endl;
    std::cout << sizeof(B) << std::endl;
    std::cout << sizeof(C) << std::endl;
    std::cout << sizeof(D) << std::endl;
    return 0;
}