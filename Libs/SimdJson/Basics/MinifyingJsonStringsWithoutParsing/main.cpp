// Minifying JSON strings without parsing
//
// In some cases, you may have valid JSON strings that you do not wish to parse but that you wish
// to minify. That is, you wish to remove all unnecessary spaces. We have a fast function for this
// purspose (simdjson::minify(const char * input, size_t length, const char * output, size_t & new_length)).
// This function does not validate your content, and it does not parse it. It is much faster than
// parsing the string and re-serilizing it in minified form (simdjson::minify(parser.parse())).
// Usage is relatively simple. You must pass an input pointer with a length parameter, as well as
// an output pointer and an output length parameter (by reference). The output length parameter is not
// read, but written to. The output pointer should point to a valid memory region that is as large as the
// original string length. The input pointer and input length are read, but not written to.

#include <iostream>
#include <simdjson.h>

void minifying()
{
    // Starts with a valid JSON document as a string.
    // It does not have to be null-terminated.
    const char * some_string = " [ 1, 2, 3, 4 ] ";
    size_t length = std::strlen(some_string);
    // Create a buffer to receive the minified string.
    // Make sure that there is enough room (length bytes).
    std::unique_ptr<char[]> buffer{new char[length]};
    size_t new_length{}; // It will receive the minified length.
    auto error = simdjson::minify(some_string, length, buffer.get(), new_length);
    // The buffer variable now has "[1,2,3,4]" and new_length has value 9.
    std::cout << some_string << " : " << length << std::endl;
    std::cout << buffer.get() << " : " << new_length << std::endl;
}

// Though it does not validate the JSON input, it will detect when the document ends with an untermidated
// string. E.g., it would refuse to minify the string "this string is not terminated because of the
// missing final quote.

int main()
{
    minifying();

    return 0;
}