#include <iostream>

class A
{
};
class B
{
};

int main()
{
    A *a = new A;
    B *b = reinterpret_cast<B *>(a); // Valid C++ code,although dereferencing it is unsafe
    return 0;
}