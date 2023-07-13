#include <iostream>

struct A
{
    int a;
    int b;
    virtual void func(){};
};

struct B
{
    int a;
    int b;
    void func(){};
};

struct C
{
    int a;
    int b;
    virtual void func(){};
    virtual void anotherFunc(){};
};

int main()
{
    // We saw how Structure padding works on our previous example,
    // now let's continue here checking what happens when we add
    // a virtual function to a struct
    A a;
    std::cout << "Size of struct A : " << sizeof(a) << std::endl;
    // It is returning 16 bytes, which means that the virtual function
    // has 8 bytes, hum, I'm not convinced that this is the way it works
    // Let's test with a non-virtual function first
    B b;
    std::cout << "Size of struct B : " << sizeof(b) << std::endl;
    // Hum, 8 Bytes? Maybe is not the function that have weight,
    // maybe is something else.
    // Let's confirm it by using 2 virtual functions in a struct
    C c;
    std::cout << "Size of struct C : " << sizeof(c) << std::endl;
    // Yes, the size is the same with 1 or 2 virtual functions.
    // What is happening here is, when a structure has a virtual function
    // the compiler add a pointer to an address in memory called
    // Virtual Table, or vtable, this structure is responsible for
    // keeping track of which function implementation is associated
    // with this particular object, we will see it in more details
    // when we talk about inheritance, for the purpose of size calculation
    // the only important thing to know is that a pointer is added to
    // the structure. Note: On my architecture and compiler a pointer has
    // 8 bytes.

    return 0;
}