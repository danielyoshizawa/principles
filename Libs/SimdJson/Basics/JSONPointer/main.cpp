// JSON Pointer
//
// The simdjson library also supports JSON pointer through the at_pointer() method, letting you
// reach further down into the document in a single call. JSON pointer is supported by both the
// DOM approach as well as the On Demand Approach.
//
// Note: The On Demand implementation of JSON pointer relies on find_field which implies that it
//        odes not unescape keys when matching.
//
// Consider the following example:

#include <iostream>
#include <simdjson.h>

void json_pointer()
{
    simdjson::padded_string cars_json = R"([
        {"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]},
        {"make":"Kia", "model":"Soul", "year":2012,"tire_pressure":[30.1,31.0,28.6,40.4]},
        {"make":"Toyota", "model":"Tercel", "year":1999,"tire_pressure":[29.8,30.0,30.2,30.5]}
    ])"_padded;
    simdjson::ondemand::parser parser;
    auto cars = parser.iterate(cars_json);
    std::cout << cars.at_pointer("/0/tire_pressure/1") << std::endl; // Prints 39.9
}

// A JSON Path is a sequence of segments each starting with the '/' character. Within arrays,
// an integer index allows you to select the indexed node. Within objects, the string value of
// the key allows you to select the value. If your keys contain the character '/' or '~',
// they must be escaped as '~1' and '~0' respectively. An empty JSON Path refers to the whole document.
//
// For multiple JSON pointer queries on a document, one can call at_pointer multiple times.

void json_pointer_multiple_queries()
{
    simdjson::padded_string cars_json = R"([
        {"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]},
        {"make":"Kia", "model":"Soul", "year":2012,"tire_pressure":[30.1,31.0,28.6,40.4]},
        {"make":"Toyota", "model":"Tercel", "year":1999,"tire_pressure":[29.8,30.0,30.2,30.5]}
    ])"_padded;
    simdjson::ondemand::parser parser;
    auto cars = parser.iterate(cars_json);
    size_t size = cars.count_elements();

    for (size_t i{0}; i < size; ++i)
    {
        std::string json_pointer = "/" + std::to_string(i) + "/tire_pressure/1";
        double x = cars.at_pointer(json_pointer);

        std::cout << x << std::endl; // Prints 39.9, 31 and 30
    }
}

// Note that at_pointer calls rewind to reset the parser at the beginning of the docuemnt. Hence,
// it invalidates all previously parsed values, objects and arrays: make sure to consume the values
// between each call to at_pointer. Consider the following example where one wants to store each
// object from the JSON into a vector of struct car_type:

void storing_values_in_vector()
{
    struct car_type
    {
        std::string make;
        std::string model;
        uint64_t year;
        std::vector<double> tire_pressure;
        car_type(std::string_view _make, std::string_view _model, uint64_t _year,
            std::vector<double>&& _tire_pressure) 
                : make{_make}, model{_model}, year{_year}, tire_pressure{_tire_pressure} {}
    };

    simdjson::padded_string cars_json = R"([
        {"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]},
        {"make":"Kia", "model":"Soul", "year":2012,"tire_pressure":[30.1,31.0,28.6,40.4]},
        {"make":"Toyota", "model":"Tercel", "year":1999,"tire_pressure":[29.8,30.0,30.2,30.5]}
    ])"_padded;
    simdjson::ondemand::parser parser;
    std::vector<double> measured;
    simdjson::ondemand::document cars = parser.iterate(cars_json);
    std::vector<car_type> content;

    for (int i{0}; i < 3; ++i)
    {
        std::string json_pointer = "/" + std::to_string(i);
        // Each successive at_pointer call invalidates
        // previoulsy parsed values, strings, objects and array.
        simdjson::ondemand::object obj(cars.at_pointer(json_pointer).get_object());
        // We materialize the object.
        std::string_view make = obj["make"];
        std::string_view model = obj["model"];
        uint64_t year(obj["year"]);
        // We materialize the array
        simdjson::ondemand::array arr(obj["tire_pressure"].get_array());
        std::vector<double> values;
        for (auto x : arr)
        {
            double value_double(x.get_double());
            values.push_back(value_double);
        }
        content.emplace_back(make, model, year, std::move(values));
    }

    for (auto c : content)
    {
        std::cout << c.make << " : " << c.model << " : " << c.year << " : ";
        for (auto tp : c.tire_pressure)
        {
            std::cout << tp << " | ";
        }
        std::cout << std::endl;
    }
}

// Furthermore, at_pointer calls rewind at the beginning of the call (i.e. the document is not
// reset after at_pointer). Consider the following example,

void using_rewind()
{
    auto json = R"( {
        "k0": 27,
        "k1": [13,26],
        "k2": true
    })"_padded;
    simdjson::ondemand::parser parser;
    auto doc = parser.iterate(json);
    std::cout << doc.at_pointer("/k1/1") << std::endl; // Prints 26
    std::cout << doc.at_pointer("/k2") << std::endl; // Prints true
    doc.rewind(); // Need to manually rewind to be able to use find_field properly from start of document
    std::cout << doc.find_field("k0") << std::endl; // Prints 27
}

// When the JSON path is the empty string ("") applied to a scalar document (lone string, number, 
// boolean or null), a SCALAR_DOCUMENT_AS_VALUE error is returned because scalar document cannot
// be represented as value instances. You can check that a document is a scalar with the method scalar().

int main()
{
    json_pointer();
    json_pointer_multiple_queries();
    storing_values_in_vector();
    using_rewind();

    return 0;
}