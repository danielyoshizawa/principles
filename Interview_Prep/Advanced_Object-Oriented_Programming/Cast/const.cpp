#include <iostream>

// Const cast is used to add or remove the const qualifier from a variable.
// It is the only cast that can be used to change the const or volatile qualifiers

// Use const_cast sparingly: Modifying const variables can lead to undefined behavior.

// const_cast | Add or remove const or volatile qualifiers | No runtime checks

void modifyValue(const int* ptr) {
    int* modifiablePtr = const_cast<int*>(ptr);
    *modifiablePtr = 10;

    std::cout << ptr << " " << *modifiablePtr << std::endl;
}

int main() {
    const int value = 5;
    std::cout << "Before: " << value << std::endl;

    modifyValue(&value);
    std::cout << &value << std::endl;
    std::cout << "After: " << value << std::endl; // Undefined behavior
    // On GCC, it is returning the same value even after the modification.

    return 0;
}