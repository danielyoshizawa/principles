// Rewinding
//
// In some instances, you may need to go through a document more than once. For that purpose,
// you may call the rewind() method on the document instance. It allows you to restart processing
// from the beginning without rescanning all the input data again. It invalidates all values, objects
// and arrays that you have created so far (including unescaped strings).
//
// In the following example, we print on the screen the number of cars in the JSON input file
// before printout the data.
//

#include <iostream>
#include <simdjson.h>

void rewind()
{
    simdjson::ondemand::parser parser;
    auto cars_json = R"([
        {"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]},
        {"make":"Kia", "model":"Soul", "year":2012,"tire_pressure":[30.1,31.0,28.6,40.4]},
        {"make":"Toyota", "model":"Tercel", "year":1999,"tire_pressure":[29.8,30.0,30.2,30.5]}
    ])"_padded;

    auto doc = parser.iterate(cars_json);
    int64_t count{0};

    for (simdjson::ondemand::object car : doc)
    {
        if (car["make"] == "Toyota")
        {
            count++;
        }
    }
    std::cout << "We have " << count << " Toyota cars." << std::endl;
    doc.rewind(); // requires simdjson 1.0 or better

    for(simdjson::ondemand::object car : doc)
    {
        std::cout << "Make/Model : " << std::string_view(car["make"]) << "/" << std::string_view(car["model"]) << std::endl;
    }
}

// Performance note: the On Demand front-end does not materialize the parsed numbers and other values.
// If you are accessing everything twice, you may need to parse them twice. Thus the rewind functionality
// is best suited for cases where the first pass only scans the structure of the document.
//
// Both arrays and objects have a similar method reset(). It is similar to the document rewind() methods,
// except that it does not rewind the intrnal string buffer. Thus you should consume values only once
// even if you can iterate through the array or object more than once. If you unescape a string within
// an array more than once, you have unsafe code.

int main()
{
    rewind();

    return 0;
}