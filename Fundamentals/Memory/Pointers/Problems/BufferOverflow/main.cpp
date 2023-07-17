// From snyk.io
// A buffer overflow is a type of runtime error that allows a program to write
// past the end of a buffer or array - hence the name overflow - and corrupt
// adjacent memory. Like most bugs, a buffer overflow doesn't manifest at every
// program execution. Instead, the vulnerability is triggered under certain
// circumstances, such as unexpected user input.
// A buffer overflow attackis the exploitation of a buffer overflow vulnerability,
// typically by a malicious actor who wants to gain access or information.

// To understand how a buffer overflow occurs, let's look at the following code,
// which performs a simple password check, and is susceptible to a buffer overflow
// attack

#include <iostream>
#include <cstdio>
#include <cstring>

const char * PASSWORD_FILE = "rictro";

int main()
{
    char password[8];
    char input[8];

    std::sscanf(PASSWORD_FILE, "%s", password);

    std::cout << "Enter password: ";
    std::cin >> input;

    // Debug prints:
    std::cout << "Address of input: " << &input << std::endl;
    std::cout << "Address of password: " << &password << std::endl;
    std::cout << "Input : " << input << std::endl;
    std::cout << "Password: " << password << std::endl;

    if (std::strncmp(password, input, 8) == 0)
        std::cout << "Access granted" << std::endl;
    else
        std::cout << "Access denied" << std::endl;

    return 0;
}

// Output of the overflow attack
// Enter password: passwordpassword
// Address of input: 0x7ffcdb45bd40
// Address of password: 0x7ffcdb45bd48
// Input : passwordpassword
// Password: password
// Access granted

// We use two 8=byte arrays: password stores the application password
// and input stores the user input. The compiler we use in this example
// places password eight bytes after input (0x7ffcdb45bd48 - 0x7ffcdb45bd40 = 8),
// so the arrays are adjacent in memory.
// Passwords shorten than eight characters produce memory blocks that look something like this
// input           | password
// h e l l o \0 - - r i c t r o \0 -
// If, however we enter "passwordpassword", the memory looks like this
// input          | password
// s u n s h i n e s u n s h i n e
// The null-terminator \0 is written past the end of password, overriding whatever happens to
// reside in the stack at the time.
// This happens because std::cin doesn't perform any bounds checks. It reads from the console
// until it encounters a new line - until the user presses Enter - without ensuring that the
// receiving buffer is large enough to hold the user's input.
// Because we only compare the first eight characters of both password and input using std::strncmp
// to avoid reading past the end of either array, we get a match where there shouldn't be one.

// Best practices to avoid buffe overflow
// Use managed buffers and strings rather than raw arrays and pointer.

// Source : https://snyk.io/blog/buffer-overflow-attacks-in-c

