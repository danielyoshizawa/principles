#include <iostream>

// reinterpret_cast is used for low-level reintepreting of bit patterns. It can cast one type
// to any other type of the same size. It is the most dangerous cast and should be used with caution.

// Use reinterpet_cast with caution: It is the most dangerous cast and can lead to unpredictable results if misused.

// reinterpret_cast | Compile-time type conversions | No runtime checks | Related Types, numeric conversion

int main() {
    int num = 65;
    char* charPtr = reinterpret_cast<char*>(&num);

    std::cout << "Integer: " << num << std::endl;
    std::cout << "Character: " << *charPtr << std::endl; // Output: 'A' (ASCII 65)

    return 0;
}

