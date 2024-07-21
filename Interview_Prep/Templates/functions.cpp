#include <iostream>

// Function template
// Function templates allow you to create a single function definition that works with different data types.

template <typename T>
T add(T a, T b)
{
    return a + b;
}

int main()
{
    std::cout << add(1, 2) << std::endl;
    std::cout << add(1.1, 2.2) << std::endl;
    return 0;
}