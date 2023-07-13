#include <iostream>

struct A
{
    int a;  // 4 Bytes
    int b;  // 4 Bytes
    char c; // 1 Byte
};

struct B
{
    int a;
    double b; // 8 Bytes
    char c;
};

struct C
{
    char a;
    char b;
    int c;
    double d;
};

struct D
{
    char a;
    char b;
    short c;
    int d;
    double e;
};

struct E
{
    int a;
    short b;
    char c;
    D d;
};

struct F
{
    int a[3];
    short b[3];
};

int main()
{
    // The sum of the size of all data members of the struct A is 9 Bytes
    A a;
    std::cout << "Size of struct A : " << sizeof(a) << " bytes" << std::endl;

    // however, calling the function sizeof on the object a, returns 12 Bytes
    // just to be sure that our previous math is correct, let's call sizeof each
    // individual data member.
    int sumOfAllDataMembers = sizeof(int) + sizeof(int) + sizeof(char);
    std::cout << "Sum of all data members : " << sumOfAllDataMembers << " bytes" << std::endl;

    // Ok, so what is happening here?
    // The answer is Structure Padding.
    // Structure padding is the addition of some empty bytes of memory
    // in the structure to naturally align the data members in the memory.
    // let's test structure B
    B b;
    std::cout << "Size of struct B : " << sizeof(b) << " bytes" << std::endl;

    // Here we have an int, a double and a char
    // and the expected sizeof would be 4 + 8 + 1 = 13 Bytes,
    // however sizeof is returning 24 Bytes.
    // We can see that we have an overhead of 11 bytes,
    // these are empty spaces to align the data members in memory
    // to do this the compiler will always consider the biggest of
    // the data types.

    // We can take advantage of this mechanic by the order that we declare our
    // data members. Let's take a look on struct C.
    C c;
    std::cout << "Size of struct C : " << sizeof(c) << " bytes" << std::endl;

    // Oh wait, 16 bytes? We have 4 data members, and the biggest one is a double
    // so it should be 32 bytes, shouldn't?
    // Fortunately, the answer is no, each block of memory separated for this
    // struct is the size 8, but it doesn't mean that every data member will
    // have its own block.
    // In this example, char has 1 byte each, and int 4, so we end up with 6 bytes
    // that fits inside a single block.
    // Following this new information, we could add 2 more chars, or a short,
    // before the double, that the size of this struct would be the same.
    D d;
    std::cout << "Size of struct D : " << sizeof(d) << " bytes" << std::endl;

    // See, this is the concept of Structure padding, using empty spaces to align
    // blocks, or banks, of memory.
    // Let's go a little further now.
    // What if we had a nested struct?
    E e;
    std::cout << "Size of struct E : " << sizeof(e) << " bytes" << std::endl;

    // One might think, that since the size of struct D is 16, and all the other
    // data members fit inside 16 bytes, the size of the struct E would be 32 bytes.
    // 16 bytes for struct D and 16 for the others.
    // But no, it is 24.
    // Alright, that is confusing, what is going on here?
    // What is happening is that the compiler consider the biggest of
    // all data types to define the block size, in our example
    // the biggest one is double, so the block size will be 8.
    // Doing the calculation by hand
    // sizeof(int) + sizeof(short) + sizeof(char) + 1 (padding) +
    // sizeof(char) + sizeof(char) + sizeof(short) + sizeof(int) + sizeof(double)
    // will be
    // 4 + 2 + 1 + 1 + 1 + 1 + 2 + 4 + 8 = 24 Bytes.

    // To finish this part of Structure Padding
    // Arrays!
    F f;
    std::cout << "Size of struct F : " << sizeof(f) << " bytes" << std::endl;

    // Follows the same principal, the block size is 4 (int), we have 3 ints
    // and 3 shorts, each element will be in sequency in memory, so we have
    // sizeof(int) + sizeof(int) + sizeof(int) +
    // sizeof(short) + sizeof(short) + sizeof(short) + 2 (padding)
    // 4 + 4 + 4 + 2 + 2 + 2 + 2 = 20 Bytes

    return 0;
}