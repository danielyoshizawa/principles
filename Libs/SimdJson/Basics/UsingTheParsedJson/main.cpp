// Using tje Parsed JSON
//
// We recommend that you first compile and run your code in Debug mode: under Visual Studio,
// it means having the _DEBUG macro defined, and, for other compilers, it means leaving the 
// __OPTIMIZE__ macro undefined. The simdjson code will set SIMDJSON_DEVELOPMENT_CHECKS=1.
// Alternatively, you can set the macro SIMDJSON_DEVELOPMENT_CHECKS to 1 prior to including the
// simdjson.h header to enable these additional checks: just make sure you remove the definition
// once your code has been tested. When SIMDJSON_DEVELOPMENT_CHECKS is set to 1, the simdjson
// library runs additional (expensive) tests on your code to help ensure that you are using the
// library in a safe manner. Once your code has been tested, you can then run it in Release mode:
// under Visual Studio, it means having the _DEBUG macho undefined, and, for other compilers,
// it means setting __OPTIMIZE__ to a positive integer. You can also forcefully disable these
// checks by setting SIMDJSON_DEVELOPMENT_CHECKS to 0. Once your code is tested, we further
// encourage you to define NDEBUG in your Release builds to disable additional runtime testing
// and get the best performance.
//
// Once you have a document (simdjson::ondemand::document), you can navigate it with idiomatic C++
// iterator, operators and casts. Besides the document instances and native types (double, uint64_t,
// int64_t, bool), we also access Unicode (UTF-8) strings (std::string_view), objects 
// (simdjson::ondemand::object) and arrays (simdjson::ondemand::array). We also have a generice
// ephemeral type (simdjson::ondemand::value) which represents a potential array or object, or
// scalar type(double, uint64_t, int64_t, bool, null, string) inside an array or an object.
// Both generic types(simdjson::ondemand::object and simdjson::ondemand::value) have a type() method
// returning a json_type value describing the value(json_type::array, json_type::number, 
// json_type::string, json_type::boolean, json_type::null). A generic value (simdjson::ondemand::value)
// is only valid temporarily, as soon as you access other values, other keys in objects, etc. it
// becomes invalid: you should therefore consume the value immediately by converting it to a scalar
// type, an array or an object.
//
// Advanced users who need to determine the number types (integer or float) dynamically, should
// review our section dynamic number types. Indeed, we have an additional ondemand::number type
// which may represent either integers or floating-point values, depending on how the numbers are
// formatted. floating-point values followed by an integer.
//
// We invite you to keep the following rules in mind:
//
// 1. While you are accessing the document, the document instance should remain in scope:
//    it is your "iterator" which keeps track of where you are in the JSON document. By design,
//    there is one and only one document instance per JSON docuemnt.
// 2. Because on Demand is really just an iterator, you must fully consume the current object
//    or array before accessing a sibling object or array.
// 3. Values can only be consumed once, you should get the values and store them if you plan
//    to need them multiple times. You are expected to access the keys of an object just once.
//    You are expected to go through the values of an array just once.
//
// The simdjson library makes generous use of std::string_view instances. If you are unfamiliar with
// std::string_view in C++, make sure to read the section on std::string_view. They behave much like
// an immutable std::string but they require no memory allocation. You can create a std::string
// instance from an std::string_view when you need it.
//
// The following specific instructions indicate how to use the JSON when exceptions are enables,
// but simdjson has full, idiomatic support for users who avoid exceptions.
//
// - Validate What You Use: When calling iterage, the document is quickly indexed. If it is not a
//   valid Unicode(UTF-8) string or if there is an unclosed string, an error may be reported right
//   away. However, it is not fully validated. On Demand only fully validates the values you use
//   and the structure leading to it. It means that at every step as you traverse the document,
//   you may encounter an error. You can handle errors either with exceptions or with error codes.
// - Extracting Values: You can cast a JSON element to a native type: double(element). This works
//   for std::string_view, double, uint64_t, int64_t, bool, ondemand::object and ondemand::array.
//   We also have explicit methods such as get_string(), get_double(), get_uint64(), get_int64(),
//   get_bool(), get_object() and get_array(). After a cast or an explicit method, the number,
//   string or boolean will be parsed, or the initial { or [ will be verified for ondemand::object
//   and ondemand::array. An exception may be thrown if the cast is not possible: there error code
//   is simdjson::INCORRECT_TYPE (see Error Handling). Importantly, when getting an ondemand::object
//   or ondemand::array instance, its content is not validated: you only guaranteed that the 
//   corresponding initial character ( { or [ ) is present. Thus, for example, you could have an
//   ondemand::object instance pointing at the invalid JSON { "this is not a valid object"}:
//   The validation occurs as you access the content.
//   The get_string() returns a valid UTF-8 string, after unescaping characters as needed: unmatched
//   surrogate pairs are treated as an error unless you pass true (get_string(true)) as a parammeter
//   to get replacement character where errors occur. If you somehow need to access non-UTF-8 strings
//   in a lossless manner (e.g. if you strings contain unpaired surrogates), you may use the 
//   get_wobbly_string() function to get a string in the WTF-8 format. When calling get_uint64_t()
//   and get_int64(), if the number does not fit in a correspoing 64-bit integer type, it is also
//   considered an error. When parsing numbers or other scalar values, the library checks that the
//   value is followed by an expected character, thus you may get a number parsing error when accessing
//   the digits as an integer in the following strings: {"number":123332a, {"number":12332\0, 
//   {"number":12332 (the digits appear in the end). We always abide by the RFC 8259 JSON specification
//   so that, for example, numbers prefixed by the + sign are in error.
//
// IMPORTANT NOTE: values can only be parsed once. Since documents are iterators, once you have parsed
//                 a value (such as by casting to double), you cannot get at it again. It is an error
//                 to call get_string() twice on an object (or to cast an object twice to std::string_view).
//

#ifdef DEBUG
    #define SIMDJSON_DEVELOPMENT_CHECKS 1
#endif

#include <iostream>
#include <simdjson.h>

int main()
{
    simdjson::ondemand::parser parser;
    auto json = simdjson::padded_string::load("test.json"); // load JSON file
    simdjson::ondemand::document doc = parser.iterate(json); // position a pointer at the beginning of the JSON data
    simdjson::ondemand::array arr = doc.get_array();
    // Not sure about it, arr.at(0) is returning both objects
    // While arr.at(1) is returning the correct object (index 1)
    simdjson::ondemand::object obj = arr.at(1); // Maybe this is not an object but a string_view
    // simdjson::ondemand::json_type type = obj[0].type();

    std::cout << "Array" << std::endl;
    std::cout << arr << std::endl;
    std::cout << "Object" << std::endl;
    std::cout << obj << std::endl;

    return 0;
}

// TODO : Still some pieces missing at this point, I'll move on and get back when I learn more.