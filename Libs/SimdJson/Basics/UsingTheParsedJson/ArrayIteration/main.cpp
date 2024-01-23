// Array Iterator
//
// To iterate through an array, use for (auto value : array) {...}. This will step through each value
// in the JSON array.
//
// If you know the type of the value, you can cast it right there, too! for (double value : array){...}.
//
// You may also use explicit iterator: for (auto i = array.begin(); i != array.end(); ++i) {...}.
// You can check that an array is empty with the condition auto i = array.begin(); if(i == array.end()) {...}
//
// - Object Iteration: You can iterate through an object's fields, as well for (auto field : object) {...}.
//                     You may also use explicit iterators: 
//                     for(auto i = object.begin(); i != object.end(); ++i){ auto field = *i; ... }.
//                     You can check that an object is empty with the condition auto i = object.begin();
//                     if (i == object.end()) {...}.
//                     - field.unescaped_key() will get you the unescaped key string. E.g., the JSON
//                       string "\u00e1" becomes the Unicode string <a with accent>. Optionally, you
//                       pass true as a parameter to the unescaped_key method if you want invalid
//                       escaped sequences to be replaced by a default replacement character 
//                       (e.g. \ud800\ud801\ud811): otherwise bad escape sequences lead to an immediate error.
//                      - field.value() will get you the value, which you can then use all these other
//                        methods on.
// - Array Index: Because it is forward-only, you cannot look up an array element by index. Instead,
//                you should iterate through the arrray and keep an index yourself.
// - Output to strings: Given a document, a value, an array or an object in JSON document, you can
//                      output a JSON string version suitable to be parsed again as JSON content:
//                      simdjson::to_json_string(element). A call to to_json_string consumes fully
//                      the element: if you apply it on a document, the JSON pointer is advanced to
//                      the end of the document. The simdjson::to_json_string does not allocate memory.
//                      The to_json_string function should not be confused with retrieving the value
//                      of a string instance which are escaped and represented using a lightweight
//                      std::string_view instance pointing at an internal string buffer inside the
//                      parser instance.
//                      To illustrate, the first of the following two code segments will print the
//                      unescaped string "test" complete with the quote whereas the seconde one will
//                      print the escaped content of the string (without the quotes).

#include <iostream>
#include <simdjson.h>
#include <sstream>

void output_to_string_escaped()
{
    // serialize a JSON to an escaped std::string instance so that it can be parsed again as JSON
    auto silly_json = R"({"test":"result"})"_padded; 
    simdjson::ondemand::parser parser;
    simdjson::ondemand::document doc = parser.iterate(silly_json);

    std::cout << simdjson::to_json_string(doc["test"]) << std::endl; // Requires simdjson 1.0 or better >
}

void output_to_string_unescaped()
{
    // retrieves an unescaped string value as a string_view instance
    auto silly_json = R"({"test":"result"})"_padded; 
    simdjson::ondemand::parser parser;
    simdjson::ondemand::document doc = parser.iterate(silly_json);

    std::cout << std::string_view(doc["test"]) << std::endl;
}

// You can use to_json_string to efficiently extract components of a JSON document to reconstruct
// a new JSON document, as in the following example:

void json_reconstruct()
{
    auto cars_json = R"([{"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]},{"make":"Kia", "model":"Soul", "year":2012,"tire_pressure":[30.1,31.0,28.6,40.4]},{"make":"Toyota", "model":"Tercel", "year":1999,"tire_pressure":[29.8,30.0,30.2,30.5]}])"_padded;
    std::vector<std::string_view> arrays;
    // We are going to collect string_view instances which point inside the cars_json string
    // and are therefore valid as long as cars_json remains in scope.
    simdjson::ondemand::parser parser;
    for (simdjson::ondemand::object car : parser.iterate(cars_json))
    {
        if (uint64_t(car["year"]) > 2000)
        {
            arrays.push_back(simdjson::to_json_string(car["tire_pressure"]));
        }
    }
    // We can now convert to a JSON string
    std::ostringstream oss;
    oss << "[";

    for (size_t i = 0; i < arrays.size(); ++i)
    {
        if (i > 0)
        {
            oss << ",";
        }
        oss << arrays[i];
    }

    oss << "]";

    auto json_string = oss.str();

    std::cout << json_string << std::endl;

}

// Extracting values (without exceptions) : You can use a variant usage of get() with error codes to avoid
// exceptions. You first declare the variable of the appropriate type (double, uint64_t, int64_t, bool
// ondemand::object and ondemand::array) and pass it by reference to get() which gives you back an error code e.g.

void avoiding_exceptions()
{
    auto abstract_json = R"(
        { "str" : { "123" : { "abc" : 3.14 }}}
    )"_padded;
    simdjson::ondemand::parser parser;

    double value;
    auto doc = parser.iterate(abstract_json);
    auto error = doc["str"]["123"]["abc"].get(value);
    if (error)
    {
        std::cerr << error << std::endl;
        return;
    }
    std::cout << value << std::endl; // Prints 3.14
}

// This example also show how we can string several operations and only check for the error once,
// a strategyy we call error chaining. Though error chaining makes the code very compact, it also
// makes error reporting less precise: in this instance, you may get the same error whether the fiels
// "std", "123" or "abc" is missing. If you need to break down error handling per operations, avoid
// errpr chaining. Furthermore, you should be mindful that chaining that harm performance by
// encouraging redundacies: writting both doc["str"]["123"]["abc"].get(value) and doc["str"]["123"]["zyw"].get(value)
// in the same program may force multiple accesses to the same keys ("str" and "123").
//
// Counting elements in arrays: Sometimes it is useful to scan an array to determine its length prior
// to parsing it. For this purpose, array instances have a count_elements method. Users should be
// aware that count_elements method can be costly since it requires scanning the whole array.
// You should only call count_elements as a last resort as it may require scanning the document
// twice or more. You may use it as follows if your document is itself an array:

void counting_elements_array()
{
    auto cars_json = R"([40.1, 39.9, 37.7, 40.4])"_padded;
    simdjson::ondemand::parser parser;
    auto doc = parser.iterate(cars_json);
    size_t count = doc.count_elements(); // requires simdjson 1.0 or better
    std::vector<double> values(count); // Not worth, amortization O(1)
    size_t index = 0;
    for (double x : doc)
    {
        values[index++] = x;
    }
    for (auto v : values)
    {
        std::cout << v << std::endl;
    }
}

// If you access an array inside a document, you can use the count_elements method as follow.
// You should not let the array instance go out of scope before consuming it after calling the
// count_elements method:

void counting_elements_object()
{
    simdjson::ondemand::parser parser;
    auto cars_json = R"({
        "test" : [
            {
                "val1" : 1,
                "val2" : 2
            },
            {
                "val1" : 1,
                "val2" : 2
            }
        ]
    })"_padded;
    auto doc = parser.iterate(cars_json);
    auto test_array = doc.find_field("test").get_array();
    size_t count = test_array.count_elements(); // requires simdjson 1.0 or better
    std::cout << "Number of elements : " << count << std::endl;

    for (simdjson::ondemand::object elem : test_array)
    {
        std::cout << simdjson::to_json_string(elem);
    }
    std::cout << std::endl;
}

// Counting fields in objects : Other times, it is useful to scan an object to determine the number
// of fields prior to parsing it. For this purpose, object instances have a count_field method. Again,
// users should be aware that the count_fields method can be costly since it requires scanning the 
// whole objects. You should only call count_fields as a last resort as it may require scanning the
// document twice or more. You may use it as follows if your documente is itself an object:

void counting_object_field()
{
    simdjson::ondemand::parser parser;
    auto json = R"({"test":{ "val1" : 1, "val2" : 2}})"_padded;
    auto doc = parser.iterate(json);
    size_t count = doc.count_fields(); // requires simdjson 1.0 or better
    std::cout << "Number of field : " << count << std::endl; // Prints "Number of fields: 1"
}

// Similarly to count_elements, you should not let an object instance go out of scope before
// consuming it after calling the count_fields method. If you access an object inside a document,
// you can use the count_fields method as follow.

void counting_fields_inside_doc()
{
    simdjson::ondemand::parser parser;
    auto json = R"({"test":{ "val1" : 1, "val2" : 2}})"_padded;
    auto doc = parser.iterate(json);
    auto test_object = doc.find_field("test").get_object();
    size_t count = test_object.count_fields(); // requires simdjson 1.0 or better
    std::cout << "Number of field : " << count << std::endl; // Prints "Number of fields: 1"
}

// Tree Walking and JSON Element Types: Sometimes you don't necessarily have a document with a 
// known type, and are trying to generically inspect or walk over JSON elements. You can also 
// represent arbitrary JSON values with ondemand::value instances: It can represent anything
// except a scalar doument (lone number, string, null or Boolean). You can check for scalar documents
// with the method scalar(). You can cast a documente that is either an array or an object to an
// ondemand::value instance immediately after you create the document instance: you cannot create a
// ondemand::value instance from a document that has already been accessed as it would mean that
// you would have two instances of the object or array simultaneously (see rewinding). You can
// query the type of a document or a value with the type() method. The type() method does not consume
// or validate documents and values, but it tells you whether they are
//
// - arrays (json_type::array),
// - objects (json_type::object),
// - numbers (json_type::number),
// - strings (json_type::string),
// - booleans (json_type::boolean),
// - null (json_type::null)
//
// You must still validate and consume the value (e.g., call is_null()) after calling type().
// You may also access raw strings. For example, the following is a quick and dirty recursive
// function that verbosely prints the JSON document as JSON. This example also illustrates lifecycle
// requirements: the document instance holds the iterator. The document must remain in scope while
// you are accessing instances of value, object and array.

void recursive_print_json(simdjson::ondemand::value element)
{
    bool add_comma;

    switch (element.type())
    {
        case simdjson::ondemand::json_type::array : 
            std::cout << "[";
            add_comma = false;
            for (auto child : element.get_array())
            {
                if (add_comma)
                {
                    std::cout << ",";
                }
                // We need to call to value() to get
                // an ondemand::value type.
                recursive_print_json(child.value());
                add_comma = true;
            }
            std::cout << "]";
            break;
        case simdjson::ondemand::json_type::object:
            std::cout << "{";
            add_comma = false;
            for (auto field : element.get_object())
            {
                if (add_comma)
                {
                    std::cout << ",";
                }
                // key() returns the key as it appears in the raw
                // JSON document, if we want the unescaped key,
                // we should do field.unescaped_key().
                std::cout << "\"" << field.key() << "\" : ";
                recursive_print_json(field.value());
                add_comma = true;
            }
            std::cout << "}\n";
            break;
        case simdjson::ondemand::json_type::number:
            // assume it fits in a double
            std::cout << element.get_double();
            break;
        case simdjson::ondemand::json_type::string:
            // get_string() would return escaped string, but
            // we are happy with unescaped string.
            std::cout << "\"" << element.get_raw_json_string() << "\"";
            break;
        case simdjson::ondemand::json_type::boolean:
            std::cout << element.get_bool();
            break;
        case simdjson::ondemand::json_type::null:
            // We check that the value is indeed null
            // otherwise: and error is thrown.
            if (element.is_null())
            {
                std::cout << "null";
            }
            break;
    }
}

void basics_treewalk()
{
    simdjson::padded_string json = R"([
        {"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]},
        {"make":"Kia", "model":"Soul", "year":2012,"tire_pressure":[30.1,31.0,28.6,40.4]},
        {"make":"Toyota", "model":"Tercel", "year":1999,"tire_pressure":[29.8,30.0,30.2,30.5]}
    ])"_padded;
    simdjson::ondemand::parser parser;
    simdjson::ondemand::document doc = parser.iterate(json);
    simdjson::ondemand::value val = doc;
    recursive_print_json(val);

    std::cout << std::endl;
}

int main()
{
    output_to_string_escaped();
    output_to_string_unescaped();
    json_reconstruct();
    avoiding_exceptions();
    counting_elements_array();
    counting_elements_object();
    counting_object_field();
    counting_fields_inside_doc();
    basics_treewalk(); // Tree Walking and JSON Element Types

    return 0;
}