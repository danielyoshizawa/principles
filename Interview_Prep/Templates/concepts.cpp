#include <iostream>
#include <concepts>

// Concepts are a feature introduced in C++20 that allow you to specify constraints on template
// parameters. They help in ensuring that the template parameters meet certain requirements,
// which can help in catching errors at compile time.

template <typename T>
concept Integral = std::is_integral_v<T>;

template <typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template <Integral T>
T add(T a, T b)
{
    return a + b;
}

template <FloatingPoint T>
T add(T a, T b)
{
    return a + b;
}

int main()
{
    int a = 10;
    int b = 20;
    std::cout << "Integer Sum: " << add(a, b) << std::endl;

    double c = 3.14;
    double d = 2.71;
    std::cout << "Floating-point Sum: " << add(c, d) << std::endl;

    return 0;
}