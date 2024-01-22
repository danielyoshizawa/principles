// The Basics: Loading and Parsing JSON Docuemtns
//
// The simdjson library allows you to navigate and validate JSON docuemnts (RFC 8259).
// As required by the standard, your JSON document should be in a Unicode (UTF-8) string.
// The whole string, from the beginning to the end, needs to be valid: we do not attempt
// to tolerate bad inputs before or after a document.
//
// For efficiency reasons, simdjson requires a string with a few bytes(simdjson::SIMDJSON_PADDING)
// at the end, these bytes may be read but their content does not afect the parsing. In practice,
// it means that the JSON inputs should be stored in a memory region with simdjson::SIMDJSON_PADDING
// extra bytes at the end. You do not have to set these bytes to specific values though you may
// want to if you want to avoid runtime warnings with some sanitizers.
//
// The simdjson library offers a tree-like API, which you can access by creating a ondemand::parser
// and calling the iterate() method. The iterate method quickly indexes the input string and may 
// detect some errors. The following example illustrates how to get started with an input JSON file.

#include <iostream>
#include <simdjson.h>

void basicOnDemand()
{
    simdjson::ondemand::parser parser;
    auto json = simdjson::padded_string::load("test.json"); // load JSON file
    simdjson::ondemand::document doc = parser.iterate(json); // position a pointer at the beginning of the JSON data
    std::cout << doc << std::endl;
};

// You can also create a padded string--and call iterate():

void paddedString()
{
    simdjson::ondemand::parser parser;
    auto json = "[1,2,3]"_padded; // The _paddes suffix creates a simdjon::padded_string instance
    simdjson::ondemand::document doc = parser.iterate(json); // parse a string
    std::cout << doc << std::endl;
};

// If you have a buffer of your own with enough padding already (SIMDJSON_PADDING extra bytes allocated).
// you can use padding_string_view to pass it in:

void paddingStringView()
{
    simdjson::ondemand::parser parser;
    char json[3+simdjson::SIMDJSON_PADDING];
    strcpy(json, "[1]");
    simdjson::ondemand::document doc = parser.iterate(json, strlen(json), sizeof(json));
    std::cout << doc << std::endl;
};

// The simdjson library will also accept std::string instances. If the provided reference is non-const,
// it will allocate padding as needed.
//
// You can sopy your data directly on a simdjson::padded_string as follows:

void paddedStringChar()
{
    const char * data = "my data"; // 7 bytes
    simdjson::padded_string my_padded_data(data,7); // copies to a padded buffer
    std::cout << my_padded_data << std::endl;
};

// Or as follows...

void paddedStringString()
{
    std::string data = "my data";
    simdjson::padded_string my_padded_data(data); // copies to a padded buffer
    std::cout << my_padded_data << std::endl;
}

// We recommend against creating many std::string or many std::padding_string instances in your
// application to store your JSON data. Consider reusing the same buffers and limiting memory allocations.
//
// By default, the simdjson library throws exceptions (simdjson_error) on errors. We omit try-catch
// clauses from our illustrating examples: if you omit try-catch in you code, an uncaught exception
// will halt your program. It is also possible to use simdjson without generating exceptions, and
// you may even build the library without exception support at all.

int main()
{
    basicOnDemand();
    paddedString();
    paddingStringView();
    paddedStringChar();
    paddedStringString();

    return 0;
}