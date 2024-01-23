// Using the Parsed JSON : Additional Examples
//
// Let us review these concepts with some additional examples. 
//
// The first example illustrates how we can chain operations. In this instance, we repeatedly
// select keys using the bracket operator (doc["str"]) and then finally request a number
// (using get_double()). It is safe to write code in this manner: if any step causes an error,
// the error status propagates and an exception is thrown at the end. You do not need to constantly
// check for errors.

#include <iostream>
#include <simdjson.h>

void using_brackets()
{
    auto abstract_json = R"(
        {"str" : { "123" : { "abc" : 3.14 }}}
    )"_padded;
    simdjson::ondemand::parser parser;
    auto doc = parser.iterate(abstract_json);
    std::cout << doc["str"]["123"]["abc"].get_double() << std::endl; // Prints 3.14
}

// In the following example, we start with a JSON document that contains an array of objects.
// We iterate through the objects using a for-loop. Within each object, we use the bracket operator
// (e.g., car["make"]) to select values. We also show how we can iterate through an array,
// corresponding to the key tire_pressure, that is contained inside each object.

void iterate_array_of_objects()
{
    simdjson::padded_string cars_json = R"([
        {"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]},
        {"make":"Kia", "model":"Soul", "year":2012,"tire_pressure":[30.1,31.0,28.6,40.4]},
        {"make":"Toyota", "model":"Tercel", "year":1999,"tire_pressure":[29.8,30.0,30.2,30.5]}
    ])"_padded;
    simdjson::ondemand::parser parser;
    for (simdjson::ondemand::object car : parser.iterate(cars_json))
    {
        std::cout << "Make/Model : " << std::string_view(car["make"]) << "/" << std::string_view(car["model"]) << std::endl;

        // Casting a JSON element to an integer
        uint64_t year = car["year"];
        std::cout << " - This car is " << 2024 - year << " years old." << std::endl;

        // Iterating through an array of floats
        double total_tire_pressure = 0;
        for (double tire_pressure : car["tire_pressure"])
        {
            total_tire_pressure += tire_pressure;
        }
        std::cout << " - Averaga tire pressure : " << (total_tire_pressure / 4) << std::endl;
    }
}

void iterate_objects_of_objects()
{
    simdjson::padded_string cars_json = R"({
        "identifier1" : {"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]},
        "identifier2" : {"make":"Kia", "model":"Soul", "year":2012,"tire_pressure":[30.1,31.0,28.6,40.4]},
        "identifier3" : {"make":"Toyota", "model":"Tercel", "year":1999,"tire_pressure":[29.8,30.0,30.2,30.5]}
    })"_padded;
    simdjson::ondemand::parser parser;
    // Iterating through an array of objects
    simdjson::ondemand::document doc = parser.iterate(cars_json);

    for (simdjson::ondemand::field key_car : doc.get_object())
    {
        // If I need a string_view and/or, I can use key_car.unescaped_key() instead, but
        // key_car.key() will be more performat otherwise.
        std::cout << "identifier : " << key_car.key() << std::endl;
        // I can now access the subobject:
        simdjson::ondemand::object car = key_car.value();
        // Accessing a field by name
        std::cout << "Make/Model : " << std::string_view(car["make"]) << "/" << std::string_view(car["model"]) << std::endl;

        // Casting a JSON element to an integer
        uint64_t year = car["year"];
        std::cout << " - This car is " << 2024 - year << "years old." << std::endl;

        // Iterating through an array of floats
        double total_tire_pressure = 0;
        for (double tire_pressure : car["tire_pressure"])
        {
            total_tire_pressure += tire_pressure;
        }
        std::cout << " - Average tire pressure : " << (total_tire_pressure / 4) << std::endl;
    }
}

// The follwoing example illustrates how you may also iterate through object values, effectively
// visiting all key-value pairs in the object.

void iterate_object_values()
{
    auto points_json = R"([
        { "12345" : {"x" : 12.34, "y" : 56.78 , "z" : 9998877}},
        { "12545" : {"x" : 11.44, "y":12.78, "z":1111111}}
    ])"_padded;
    simdjson::ondemand::parser parser;

    // Parse and iterate through an array of objects
    for (simdjson::ondemand::object points : parser.iterate(points_json))
    {
        // Iterating through an object, you iterate through key-value pairs (a 'field').
        for (auto point : points)
        {
            // Get the key corresponding the field 'point'.
            std::cout << "id: " << std::string_view(point.unescaped_key()) << " : (";
            // Get the value corresponding the field 'point'.
            simdjson::ondemand::object xyz = point.value();
            std::cout << xyz["x"].get_double() << ", ";
            std::cout << xyz["y"].get_double() << ", ";
            std::cout << xyz["z"].get_int64() << ")" << std::endl;
        }
    }
}

int main()
{
    using_brackets();
    iterate_array_of_objects();
    iterate_objects_of_objects();
    iterate_object_values();

    return 0;
}