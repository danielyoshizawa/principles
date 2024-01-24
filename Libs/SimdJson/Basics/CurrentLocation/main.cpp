// Current location in document
//
// Sometimes, it might be helpful to know the current location in the document during iteration.
// This is especially useful when encountering errors. The current_location() method on a document
// instances makes it easy to identify common JSON errors. Users can call the current_locations()
// method on a valid document instance to retrieve a const char * pointer to the current location
// in the document. This method also works even after an error has invalidated the document and the
// parser (e.g. TAPE_ERROR, INCOMPLETE_ARRAY_OR_OBJCET). When the input was a padding_string or 
// another null-terminated source, theny you may use the const char * pointer as a C string.
// As an example, consider the following example where we used the exception-free simdjson interface:

#include <iostream>
#include <simdjson.h>

void current_location_example()
{
    auto broken_json = R"( {"double" : 13.06 , false , "integer" : -343} )"_padded; // Missing key
    simdjson::ondemand::parser parser;
    auto doc = parser.iterate(broken_json);
    int64_t i;
    auto error = doc["integer"].get_int64().get(i); // Expect to get integer from "integer" key, but get TAPE_ERROR
    if (error)
    {
        std::cout << error << std::endl; // Prints TAPE_ERROR error message
        // Recover a pointer to the location of the first error:
        const char * ptr;
        error = doc.current_location().get(ptr);
        // ptr points at 'false, "integer" : -343}" which is the location of the error
        //
        // Because we pad simdjson::padded_string instances with null characters,
        // you may algo do the following:
        std::cout << doc.current_location() << std::endl; // Prints "false, "integer" : -343} " (location of TAPE_ERROR)
    }
}

int64_t current_location_example_with_exceptions()
{
    auto broken_json = R"( {"double" : 13.06 , false , "integer" : -343} )"_padded; // Missing key
    simdjson::ondemand::parser parser;
    auto doc = parser.iterate(broken_json);
    try
    {
        return int64_t(doc["integer"]);
    }
    catch(const simdjson::simdjson_error & err)
    {
        std::cerr << doc.current_location() << std::endl;
        return -1;
    }
    
}

// In these examples, we tried to access the "integer" key, but since the parser had to go through
// a value without a key before ('false'), a TAPE_ERROR is thrown. The pointer returned by the
// current_location() method then points at the location of the error. The current_location() may
// also be used when the error is triggered by a user action, even if the JSON input is valid.
// Consider the following example:

void user_triggered_error()
{
    auto json = R"([1,2,3])"_padded;
    simdjson::ondemand::parser parser;
    auto doc = parser.iterate(json);
    int64_t i;
    auto error = doc["integer"].get_int64().get(i); // Incorrect call on array, INCORRECT_TYPE error
    if (error)
    {
        std::cout << error << std::endl; // Prints INCORRECT_TYPE error message
        std::cout << doc.current_location() << std::endl; // Prints "[1,2,3]" (locataion of INCORRECT_TYPE error)
    }
}

// If the location is invalid (i.e. at the end of a document), the current_location() methods returns
// an OUT_OF_BOUNDS error. For example.

void out_of_bounds()
{
    auto json = R"([1,2,3])"_padded;
    simdjson::ondemand::parser parser;
    auto doc = parser.iterate(json);
    for (auto val : doc)
    {
        // Do something wit val
    }
    try
    {
        std::cout << doc.current_location() << std::endl; // Throws OUT_OF_BOUNDS
    } catch (const simdjson::simdjson_error &err)
    {
        std::cerr << err.what() << std::endl;
    }
}

// Conversely, if doc.current_location().erro() == simdjson::SUCCESS, then the docuemnt has more
// content.
//
// Finally, the current_location() method may also be used even when no exceptions/errors are thrown.
// This can be helpful for users that want to know the current state of iteration during parsing.
// For example:

void parsing_current_state()
{
    auto json = R"([[1,2,3], -23.4, {"key" : "value"}, true])"_padded;
    simdjson::ondemand::parser parser;
    auto doc = parser.iterate(json);
    for (auto val : doc)
    {
        simdjson::ondemand::object obj; // invalid until the get() succeeds
        auto error = val.get_object().get(obj); // Only get objects
        if (!error)
        {
            std::cout << doc.current_location() << std::endl; // Prints ""key" : "value"}, true]"
        }
    }
}

// The current_location() method requires a valid document instance. If the iterate function fails to
// return a valid document, then you cannot use current_location() to identify the location of an error
// in the input string. The errors reported by iterate function include EMPTY if no JSON document is
// detected, UTF8_ERROR if the string is no a valid UTF-8 string, UNESCAPED_CHARS if a string contains
// control characters that must be escaped and UNCLOSED_STRINGS if there is an unclosed string in the
// document. We do not provide location information for these errors.

int main()
{
    current_location_example();
    current_location_example_with_exceptions();
    user_triggered_error();
    out_of_bounds();
    parsing_current_state();

    return 0;
}