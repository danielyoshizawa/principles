#include <iostream>
#include <type_traits>

// SFINAE - Substitution Failure Is Not An Error

// SFINAE is a feature that allows the compiler to choose the best match for a template function
// or class based on the provided arguments. If a substitution fails, the compiler does not
// generate an error but instead tries other matches.

// SFINAE is used to enable or disable templates based on the types of the arguments.

template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
process(T value)
{
    std::cout << "Processing integer: " << value << std::endl;
    return value;
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
process(T value)
{
    std::cout << "Processing floating-point: " << value << std::endl;
    return value;
}

int main()
{
    process(10);
    process(3.14);
    return 0;
}