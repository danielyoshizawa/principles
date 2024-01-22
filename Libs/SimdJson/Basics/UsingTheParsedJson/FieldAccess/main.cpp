// Field Access
//
// To get the value of the "foo" field in an object, use object["foo"]. This will scan through
// the object looking for the field with the matching string, doing a character-by-character
// comparison, if may generate the error simdjson::NO_SUCH_FIELD if there is no such key in the
// object, it may throw and exception (see Error Handling). For efficiency reason, you should avoid
// looking up the field repeatedly: e.g., do not do object["foo"] followed by object["foo"] with
// the same object instance. For best performance, you should try to query the keys in the same order
// they appear in the document. If you need several keys and you cannot predict the order they will
// appear in, it is recommended to iterate through all keys for(auto field : object) {...}. Keep
// in mine that On Demand does not buffer or save the result of the parsing: if you repeatedly
// access object["foo"], then it must repeatedly seek the key and parse the content. The library
// does not provide a distinct function to check if a key is present, instead we recommend you
// attempt to access the key: e.g., by doing ondemand::value val{}; if (!object["foo"].get(val)) {...},
// you have that val contains the requested value inside the if clause. It is your responsibility as
// a user to temporarily keep a reference to the value (auto v = object["foo"]), or to consume the
// content and store it in your own data structures. If you consume an object twice: 
// std::string_view(object["foo"]) followed by std::string_view(object["foo"]) then your code is in 
// error. Furthermore, you can only consume one field at a time, on the same object. The value 
// instance you get from content["bids"] becomes invalid when you call content["asks"]. If you have
// retrieved content["birds"].get_array() and you later call content["asks"].get_array(), then the
// first array should no longer be accessed: it would be unsafe to do so. You can detect such mistakes
// by first compiling and running the code in Debug mode: an OUT_OF_ORDER_ITERATION error is generated.
//
// NOTE: JSON allows you to escape characters in keys. E.g., the key "date" may be written as
//       "\u0064\u0061\u0074\u0065". By default, simdjson does not unescape keys when matching by
//       default. Thus if you search for the key "date" and the JSON document uses "\u0064\u0061\u0074\u0065"
//       as a key, it will not be recognized. This is not generally a problem. Nevertheless, if you
//       do need to support escaped keys, the method unescaped_key() provides the desired unescaped keys
//       by parsing and writting out the unescaped keys to a string buffer and returning a std::string_view
//       instance. the unescaped_key takes an optionla Boolean value: passing it true will decode
//       invalid Unicode sequences with replacement, meaning that the decoding always succeeds but
//       bogus Unicode replacement characters are inserted. In general, you should expect a performance
//       penalty when using unescaped_key() comprared to key() because of the string processing:
//       the key() function just points inside the source JSON document.

#include <iostream>
#include <simdjson.h>

void unescaped_keys()
{
    auto json = R"({"k\u0065y" : 1})"_padded;
    simdjson::ondemand::parser parser;
    auto doc = parser.iterate(json);
    simdjson::ondemand::object object = doc.get_object();

    for(auto field : object)
    {
        // calling key will return "k\u0065y"
        // auto key = field.key();
        // std::cout << key << std::endl;

        // parses and writes out the key, after unescaping it,
        // to a string buffer. It causes a performance penalty.
        std::string_view keyv = field.unescaped_key();

        if (keyv == "key")
        {
            std::cout << uint64_t(field.value()) << std::endl;
        }
    }
};

// By default, field lookup is order-insensitive, so you can look up values in any order. However,
// we still encourage you to look up fields in the order you expect them in the JSON, as it is still faster.
//
// If you want to enforce finding fields in order, you can use object.find_field("foo") instead. This
// will only look forward, and will fail to find fields in the wrong order: for example, this will fail:

void order_sensitive()
{
    simdjson::ondemand::parser parser;
    auto json = R"({ "x" : 1, "y" : 2})"_padded;
    auto doc = parser.iterate(json);
    double y = doc.find_field("y"); // The cursor is now after the 2 (at })
    try
    {
        double x = doc.find_field("x"); // This fails, because there are no more fields afeter "y"
    } catch (...)
    {
        std::cout << "Order Sensitive : Couldn't find field \"x\" after finding field \"y\"" << std::endl;
    }
}

// By contrast, using the default (order-insensitive) lookup succeed:
void order_insensitive()
{
    simdjson::ondemand::parser parser;
    auto json = R"({ "x" : 1, "y" : 2})"_padded;
    auto doc = parser.iterate(json);
    double y = doc["y"]; // The cursor is now after the 2 (at })
    try
    {
        double x = doc["x"]; // Success: [] loops back around to find "x"
        std::cout << "X : " << x << " | Y : " << y << std::endl;
    } catch (...)
    {
        std::cout << "Order Insensitive : Couldn't find field \"x\" after finding field \"y\"" << std::endl;
    }
}

int main()
{
    unescaped_keys();
    order_sensitive();
    order_insensitive();

    return 0;
}