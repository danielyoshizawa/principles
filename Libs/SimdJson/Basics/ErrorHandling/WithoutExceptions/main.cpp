// Error Handling Examples without Exceptions
//
// This is how the example in "Using the Parsed JSON" could be written using only error code checking
// (without exceptions):

#include <iostream>
#include <simdjson.h>

bool parse()
{
    simdjson::ondemand::parser parser;
    simdjson::padded_string cars_json = R"([
        {"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]},
        {"make":"Kia", "model":"Soul", "year":2012,"tire_pressure":[30.1,31.0,28.6,40.4]},
        {"make":"Toyota", "model":"Tercel", "year":1999,"tire_pressure":[29.8,30.0,30.2,30.5]}
    ])"_padded;
    
    simdjson::ondemand::document doc;

    // Iterating through an array of objects
    auto error = parser.iterate(cars_json).get(doc);
    if (error)
    {
        std::cerr << error << std::endl;
        return false;
    }

    simdjson::ondemand::array cars; // invalid until the get() succeeds
    error = doc.get_array().get(cars);

    for (auto car_value : cars)
    {
        simdjson::ondemand::object car; // invalid until the get() succeeds
        error = car_value.get_object().get(car);
    
        if (error)
        {
            std::cerr << error << std::endl;
            return false;
        }

        // Accessing a field by name
        std::string_view make;
        std::string_view model;
        error = car["make"].get(make);

        if (error)
        {
            std::cerr << error << std::endl;
            return false;
        }

        error = car["model"].get(model);

        if (error)
        {
            std::cerr << error << std::endl;
            return false;
        }

        std::cout << "Make/Model : " << make << "/" << model << std::endl;

        // Casting a JSON element to an integer
        uint64_t year{};
        error = car["year"].get(year);

        if (error)
        {
            std::cerr << error << std::endl;
            return false;
        }

        std::cout << " - This car is " << 2024 - year << " years old." << std::endl;

        // Iterating through an array of floats
        double total_tire_pressure{0};
        simdjson::ondemand::array pressures;
        error = car["tire_pressure"].get_array().get(pressures);

        if (error)
        {
            std::cerr << error << std::endl;
            return false;
        }

        for (auto tire_pressure_value : pressures)
        {
            double tire_pressure;
            error = tire_pressure_value.get_double().get(tire_pressure);

            if (error)
            {
                std::cerr << error << std::endl;
                return false;
            }

            total_tire_pressure += tire_pressure;
        }
        std::cout << " - Average tire pressure: " << (total_tire_pressure / 4) << std::endl;
    }
    return true;
}

// For safety, you should only use our ondemand instances (e.g., ondemand::object)
// after you have initialized them and checked that there is no erro:
//
//     simdjson::ondemand::object car; // invalid until the get() succeeds
//     // the `car` instance should not be used before it is initialized
//     error = car_value.get_object().get(car);
//     if (error) {
//         // the `car` instance should not be used
//     } else {
//         // the `car` instance can be safely used
//     }
//
// The followinf examples illustrates how to iterate through the content of an
// object without having to handle exceptions.

bool object_iteration_without_exception()
{
    auto json = R"({"k\u0065y" : 1})"_padded;
    simdjson::ondemand::parser parser;
    simdjson::ondemand::document doc;
    auto error = parser.iterate(json).get(doc);
    if (error)
    {
        std::cerr << error << std::endl;
        return false;
    }
    simdjson::ondemand::object object; // invalid until the get() succeeds
    error = doc.get_object().get(object);
    if (error)
    {
        std::cerr << error << std::endl;
        return false;
    }
    for (auto field : object)
    {
        // We could replace field.key() with field.unescaped_key(),
        // and ondemand::raw_json_string by std::string_view.
        simdjson::ondemand::raw_json_string keyv;
        error = field.key().get(keyv);
        if (error)
        {
            std::cerr << error << std::endl;
            return false;
        }

        if (keyv == R"(k\u0065y)")
        {
            uint64_t intvalue;
            error = field.value().get(intvalue);
            if (error)
            {
                std::cerr << error << std::endl;
                return false;
            }
            std::cout << intvalue << std::endl;
        }   
    }
    return true;
}

// Disabling Exceptions
//
// The simdjson can be build with exceptions entirely disabled. It checks the __cpp_exceptions macro
// at compile time. Even if exceptions are enabled in your compiler, you may still disable exceptions
// speficically for simdjson, by setting SINDJSON_EXCEPTIONS to 0 (false) at compile-time when 
// building the simdjson library. If you are building with CMake, to ensure you don't write any code
// that uses exceptions, you compile with SIMDJSON_EXCEPTIONS=OFF. For example, if including the
// project via cmake:
//
// target_compile_definitions(simdjson PUBLIC SIMDJSON_EXCEPTIONS=OFF)


int main()
{
    parse();
    object_iteration_without_exception();

    return 0;
}