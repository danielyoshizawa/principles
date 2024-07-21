#include <iostream>

// Variadic templates allow you to create templates that take a variable number of arguments.

template <typename... Args>
void print(Args... args)
{
    (std::cout << ... << args) << std::endl;
}

int main()
{
    print(1, 2, 3);
    print("Hello", " ", "World");
    print(1, "Test", 3.14);

    return 0;
}