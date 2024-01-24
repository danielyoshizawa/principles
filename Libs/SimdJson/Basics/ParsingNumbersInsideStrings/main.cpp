// Parsing numbers inside strings
//
// Though the JSON specification allows for numbers and string values, many engineers choose
// to integrate the numbers inside strings, e.g. they prefer {"a" : "1.9"} to {"a" : 1.9}.
// The simdjson library supports parsing valid numbers inside strings which makes it more convenient
// for people working with those types of documents. This feature is supported through three
// methods : get_double_in_string, get_int64_in_string and get_uint64_in_string. However, it is
// important to note that these methods are not substitute to the regular get_double, get_int64 and
// get_uint64. The usage of the get_*_in_string methods is solely to parse valid JSON numbers inside
// strings, and so we expect users to call these methods appropriately. In particular, a valid JSON
// number has no leading and no trailing whitespaces, and the strings "nan", "1e" and "infinity"
// will not be accepted as valid numbers. As an example, suppose we have the following JSON text:
//
// <Json inside test.json file>
//
// Now, suppose that a user wants to get the timestamp from timestampstr key. One could do the
// following:

#include <iostream>
#include <simdjson.h>
#include <limits>

void get_timestampstr_in_string()
{
    simdjson::ondemand::parser parser;
    auto json = simdjson::padded_string::load("test.json");
    auto doc = parser.iterate(json);
    uint64_t time = doc.at_pointer("/timestampstr").get_uint64_in_string();
    std::cout << time << std::endl; // Prints 1399490941
}

// Another thing a user might want to do is extract the markets array and get the market name, price
// and volume. Here is one way to do so:

void get_markets()
{
    simdjson::ondemand::parser parser;
    auto json = simdjson::padded_string::load("test.json");
    auto doc = parser.iterate(json);

    // Getting markets array
    simdjson::ondemand::array markets = doc.find_field("ticker").find_field("markets").get_array();
    // Iterating through markets array
    for (auto value : markets)
    {
        std::cout << "Market : " << value.find_field("market").get_string();
        std::cout << "\tPrice : " << value.find_field("price").get_double_in_string();
        std::cout << "\tVolume :" << value.find_field("volume").get_double_in_string() << std::endl;
    }
}

// Finally, here is an example dealing with erros where the user wants to convert the string
// "Infinity" ("change" key) to a float with infinity value.

void converting_infinity()
{
    simdjson::ondemand::parser parser;
    auto json = simdjson::padded_string::load("test.json");
    auto doc = parser.iterate(json);
    // Get "change"/"Infinity" key/value pair
    simdjson::ondemand::value value = doc.find_field("ticker").find_field("change");
    double d;
    auto error = value.get_double_in_string().get(d);

    // Check if parsed value into double successfully
    if (std::string_view view{}; error)
    {
        error = value.get_string().get(view);
        if (error)
        {
            // Handle error
        }
        else if (view == "Infinity")
        {
            d = std::numeric_limits<double>::infinity();
            std::cout << "Infinity : " << d << std::endl;
        }
    }
    else
    {
        // Handle wrong value
    }
}

// It is also important to note that when dealing an invalid number inside a string, simdjson will
// report a NUMBER_ERROR error, if the string begins with a number whereas simdjson will report
// a INCORRECT_TYPE error otherwise.
//
// The *_in_string methods can also be called on a single document instance: e.g., when your document
// consist solely of a quoated number.

int main()
{
    get_timestampstr_in_string();
    get_markets();
    converting_infinity();

    return 0;
}