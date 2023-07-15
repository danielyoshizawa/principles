#include <iostream>

class A
{
public:
    A()
    {
        std::cout << "Construtor of A" << std::endl;
    }
    ~A()
    {
        std::cout << "Destructor of A" << std::endl;
    }
};

class B
{
private:
    A *a; // regular pointer
public:
    B() : a(new A)
    {
        std::cout << "Constructor of B" << std::endl;
    }
    ~B()
    {
        std::cout << "Destructor of B" << std::endl;
    }
};

int main()
{
    // Memory allocation
    // Creating an instance o B will initialize an instance of A
    B *b = new B;
    // Calling the delete on object B will not relese the memory for A
    // check that the destructor of A is never called,
    // creating a memory leak
    delete b;

    return 0;
}

// Valgrind Output
// ==2060== HEAP SUMMARY:
// ==2060==     in use at exit: 1 bytes in 1 blocks
// ==2060==   total heap usage: 4 allocs, 3 frees, 73,737 bytes allocated
// ==2060== 
// ==2060== LEAK SUMMARY:
// ==2060==    definitely lost: 1 bytes in 1 blocks
// ==2060==    indirectly lost: 0 bytes in 0 blocks
// ==2060==      possibly lost: 0 bytes in 0 blocks
// ==2060==    still reachable: 0 bytes in 0 blocks
// ==2060==         suppressed: 0 bytes in 0 blocks
