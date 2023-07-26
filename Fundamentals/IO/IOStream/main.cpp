#include <iostream>

// Object of class ostream that represents the standard output stream oriented to 
// narrow characters (of type char). It corresponds to the C stream stdout.

int main()
{
    // cout
    // The standard output stream is the default destination of characters determined by 
    // the environment. This destination may be shared with more standard objects 
    // (such as cerr or clog).
    std::cout << "Enter a number between 1 and 9 : " << std::endl;
    // cin
    // The standard input stream is a source of characters determined by the environment. 
    // It is generally assumed to be input from an external source, such as the keyboard or a file.
    int input {0};
    std::cin >> input;
    // cerr
    // The standard error stream is a destination of characters determined by the environment. 
    // This destination may be shared by more than one standard object (such as cout or clog).
    if (input < 1 || input > 9) {
        std::cerr << "Invalid input" << std::endl;
    } else {
    // clog
    // The standard logging stream is a destination of characters determined by the environment. 
    // This destination may be shared by more than one standard object (such as cout or cerr).
        std::clog << "Valid input : " << input << std::endl;
    }

    return 0;
}