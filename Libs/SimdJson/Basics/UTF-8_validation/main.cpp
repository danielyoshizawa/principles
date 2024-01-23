// UTF-8 validation (alone)
//
// The simdjson library has fast functions to validate UTF-8 strings. They are many times faster
// than most functins commonly found in libraries. You can use our fast functions, even if you do
// not care about JSON.

#include <iostream>
#include <simdjson.h>

void validate_utf8()
{
    const char * some_string = "[ 1, 2, 3, 4]";
    size_t length = std::strlen(some_string);
    bool is_ok = simdjson::validate_utf8(some_string, length);

    std::cout << std::boolalpha << is_ok << std::endl;
}

// The UTF-8 validation function merely checks that the input is valid UTF-8: it works with strings
// in general, not just JSON strings.
//
// Your input string does not need any padding. Any string will do. The validate_utf8 function does
// not do any memory allocation on the heap, and it does not throw exceptions.
//
// If you find yourself needing only fast Unicode functions, consider using the simdutf library instead:
// https://github.com/simdutf/simdutf

int main()
{
    validate_utf8();

    return 0;
}