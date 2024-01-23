// Exceptions
//
// Users more comfortable with an exception flow may choose to directly cast the simdjson_result<T>
// to the desired type:
//
// simdjson::ondemand::document doc = parser.iterate(json); // Throws an exception if there was an error!
//
// When used this way, a simdjson_erro exception will be thrown if an error occurs, preventing the
// program from continuing if there was an error.
//
// If one is willing to trigger exceptions, it is possible to write simpler code:

#include <iostream>
#include <simdjson.h>

void triggering_exception_untreated()
{
    simdjson::ondemand::parser parser;
    simdjson::padded_string json = simdjson::padded_string::load("test.json");
    simdjson::ondemand::document tweets = parser.iterate(json);
    uint64_t identifier = tweets["statuses"].at(3)["id"];
    std::cout << identifier << std::endl;
}

// You can do handle errors gracefully as well...

void triggering_exception()
{
    simdjson::ondemand::parser parser;
    simdjson::padded_string json_string;
    simdjson::ondemand::document doc;
    try
    {
        json_string = simdjson::padded_string::load("test.json");
        doc = parser.iterate(json_string);
        uint64_t identifier = doc["statuses"].at(3)["id"];
        std::cout << identifier << std::endl;
    } catch (simdjson::simdjson_error &error)
    {
        std::cerr << "JSON error : " << error.what() << " near "
                  << doc.current_location() << " in " << json_string << std::endl;
    }
}

int main()
{
    // triggering_exception_untreated();
    triggering_exception();

    return 0;
}