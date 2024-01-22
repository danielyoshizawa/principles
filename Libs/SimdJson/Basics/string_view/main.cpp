// string_view
//
// The simdjson library builds on compilers supporting the C++11 standard. It is also a strict
// requirement: we have no plan to support older C++ compilers.
//
// We present parsed Unicode (UTF-8) strings in simdjson using the std::string_view class.
// It avoids the need to copy the data, as would be necessary with the std::string class.
// It also avoids the pitfalls of null-terminated C strings. It makes it easier for our users
// to copy the data into their own favorite class instances (e.g. alternatives to std::string).
//
// A std::string_view instance is effectively just a pointer to a region in memory representing a
// string. In simdjson, we return std::string_view instances that either point within the input
// string you parsed (when using raw String), or to a temporary string buffer inside our parser
// class instances that is valid until the parser object is destroyed or you use it to parse another
// document. When using std::string_view instances, it is your responsibility to ensure that
// std::string_view instance does not outlive the pointer-to memory (e.g. either the input buffer
// or the parser instance).
// Furthermore, some operations reset the string buffer inside our parser instances: e.g. when
// we parse a new document. Thus a std::string_view instance is often best viewed as a temporary
// string value that is tied to the document you are parsing. At the cost of some memory allocation,
// you may convert your std::string_view instances for long-term storage into std::string instances:
// std::string mycopy(view) (C++17) or std::string mycopy(view.begin(), view.end()) (prior to C++17).
// For convenience, we also allow storing an escaped string directly into an existing string instance.
//
// The std::string_view class has become standard as part of C++17 but it is not always available
// on compilers which only supports C++11. When we detect that string_view is natively available,
// we define the macro SIMDJSON_HAS_STRING_VIEW.
//
// When we detect that it is unavailable, we use string-view-lite as a substitute. In such cases,
// we use the type alias using string_view = nostd:::string_view; to offer the same API, irrespective
// of the compiler and standard library. The macro SIMDJSON_HAS_STRING_VIEW will be undefined to
// indicate that we emulate string_view.
//
// Some users prefer to use non-JSON native encoding formats such as UTF-16 or UTF-32. Users
// may trancode the UTF-8 strings produced by the simdjson library to other formats.

#include <iostream>
#include <simdjson.h>
#include <string_view> // Compiler have string_view, however

int main()
{
#ifdef SIMDJSON_HAS_STRING_VIEW // This macro is not defined, need to check what is going on
    std::cout << "Has native string_view" << std::endl;
#else
    std::cout << "Does not have native string_view" << std::endl;
#endif // SIMDJSON_HAS_STRING_VIEW

    std::string_view str{"Hello!! String View"};

    std::cout << str << std::endl;

    return 0;
}