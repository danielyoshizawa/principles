// Error Handling
//
// Error handling with exception and a single try/catch clause makes the code simple, but it givres
// you little control over errors. For easier debugging or more robust error handling, you may want
// to consider our exception-free approach.
//
// The entire simdjson API is usable with and without exceptions. All simdjson APIs that can fail
// return simdjson_result<T>, which is a <value, error_code> pair. You can retrieve the value with
// .get() without generating an exception, like so:

#include <iostream>
#include <simdjson.h>

void without_genereting_error()
{
    auto json = R"()"_padded;
    simdjson::ondemand::parser parser;
    simdjson::ondemand::document doc;
    auto error = parser.iterate(json).get(doc);
    if (error) {
        std::cerr << error << std::endl;
    }
}

// When there is no error, the error code simdjson::SUCCESS is returned: it evaluates as false as a
// Boolean. We have several error codes to indicate errors, they all evaluate to true as a Boolean:
// your software should not generally not depend on exact error codes. We may change the error codes
// in future releases and the exact error codes could vary depending on your system.
//
// Some errors are recoverable:
// - You may get the error simdjson::INCORRECT_TYPE after trying to convert a value to an incorrect
//   type: e.g., you expected a number and try to convert the value to a number, but it is an array.
// - You may query a key from an object, but the key is missing in which case you get the error
//   simdjson::NO_SUCH_FIELD: e.g., you call obj["myname"] and the object does not have a key "myname".
//
// Other errors (e.g., simdjson::INCOMPLETE_ARRAY_OR_OBJECT) may indicate a fatal error and often
// follow from the fact that the document is not valid JSON. In which case, it is no longer possible
// to continue accessing the document: calling the method is_alive() on the document instance returns
// false. All following accesses will keep returning the same fatal error 
// (e.g. simdjson::INCOMPLETE_ARRAY_OR_OBJECT).
//
// When you use the code without exceptions, it is your responsibility to check for error before using
// the result: if there is an error, the result value will not be valid and using it will cause 
// undefined behavior (UD). Most compilers should be able to help you if you activate the right set
// of warnings: they can identify variables that are written to but nver otherwise accessed.
//
// Let us illustrate with an example where we try to access a number that is not valie (3.14.1).
// If we want to proceed without throwing and catching exceptions, we can do so as follows:

bool simple_error_example()
{
    simdjson::ondemand::parser parser;
    auto json = R"({"bad number" : 3.14.1})"_padded;
    simdjson::ondemand::document doc;
    if (parser.iterate(json).get(doc) != simdjson::SUCCESS)
    { 
        return false;
    }
    double x;
    auto error = doc["bad number"].get_double().get(x);
    // returns "simdjson::NUMBER_ERROR"
    if (error != simdjson::SUCCESS)
    {
        std::cerr << error << std::endl;
        return false;
    }
    std::cout << "Got " << x << std::endl;

    return true;
}

// Observe how we verify the error variable before accessing the retrieved number (variable x)
//
// The equivalent with exception handling might look as follows.

bool simple_error_example_except()
{
    simdjson::ondemand::parser parser;
    auto json = R"({"bad number" : 3.14.1 })"_padded;
    try
    {
        simdjson::ondemand::document doc = parser.iterate(json);
        double x = doc["bad number"].get_double();
        std::cout << "Got " << x << std::endl;
        return true;
    } catch (simdjson::simdjson_error & e) {
        // e.error() == NUMBER_ERROR
        std::cout << e.error() << std::endl;
        return false;
    }
}

// We can write a "quick start" example where we attempt to parse the following JSON file and access
// some data, without triggering exceptions:
//
// {
//   "statuses" : [
//     {
//        "id" : 505874924095815700
//     },
//     {
//        "id" : 505874922023837700
//     }
//   ],
//   "search_metadata" : {
//      "count" : 100
//   }
// }
//
// Our program loads the file, selects value corresponding to key "search_metadata" which expected to
// be an object, and then it selects the key "count" within that object.
//

void handling_error_no_exceptions()
{
    simdjson::ondemand::parser parser;
    simdjson::padded_string json;
    auto error = simdjson::padded_string::load("test.json").get(json);

    if (error)
    {
        std::cerr << error << std::endl;
        return;
    }

    simdjson::ondemand::document tweets;
    error = parser.iterate(json).get(tweets);

    if (error)
    {
        std::cerr << error << std::endl;
        return;
    }

    simdjson::ondemand::value res;
    error = tweets["search_metadata"]["count"].get(res);

    if (error != simdjson::SUCCESS)
    {
        std::cerr << "could not access keys : " << error << std::endl;
        return;
    }
    std::cout << res << " results." << std::endl;
}

// The following is a similar example where one wants to get the id of the first tweet without
// triggering exceptions. To do this, we use ["statuses"].at(0)["id"]. We break that expression down:
// - Get the list of tweets (the "statuses" key of the document) using ["statuses"]). The result is
//   expected to be an array,
// - Get the first tweet using .at(0). The result is expected to be an object.
// - Get the id of the tweet using ["id"]. We expect the value to be a non-negative integer.
//
// Observe how we use the at method when querying an index into an array, and not the bracket operator.

void handling_error_no_exceptions_v2()
{
    simdjson::ondemand::parser parser;
    simdjson::ondemand::document tweets;
    simdjson::padded_string json;
    auto error = simdjson::padded_string::load("test.json").get(json);

    if (error)
    {
        std::cerr << error << std::endl;
        return;
    }
    
    error = parser.iterate(json).get(tweets);
    
    if (error)
    {
        std::cerr << error << std::endl;
        return;
    }

    uint64_t identifier;
    error = tweets["statuses"].at(0)["id"].get(identifier);

    if (error)
    {
        std::cerr << error << std::endl;
        return;
    }

    std::cout << identifier << std::endl;

}

// The at method can only be called once on an array. It cannot be used to iterate through the values
// of an array.

int main()
{
    without_genereting_error();
    simple_error_example();
    simple_error_example_except();
    handling_error_no_exceptions();
    handling_error_no_exceptions_v2();

    return 0;
}