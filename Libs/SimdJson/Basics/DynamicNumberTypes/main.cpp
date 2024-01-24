// Dynamic Number Types
//
// The JSON standard does not offer strongly typed numbers. It suggests that using the binary64 type
// (double in C++) is a safe choice, but little else. Given the JSON array [1.0,1], it is not
// specified wether it is an array of two floating-point numbers, two integers, or one floating-point
// number followed by an integer.
//
// Given an ondemand::value instance, you may ask wheteher it is a negative value with the
// is_negative() method. The function is inexpensive.
//
// To occasionally distinguish between floating-point values and integers given and ondemand::value
// instance, you may call the is_integer() method. We recognize an integer number by the lack decimal
// point and the lack of exponential suffix. E.g., 1e1 is always considered to be a floating-point
// number. The is_integer() method does not consume the value, but it scans the number string.
// You shoudl avoid calling it repeatedly.
//
// If you need to determine both the type of the number (integer or floating-point) and its value
// efficiently, you may call get_number() method on the ondemand::value instance, Upon success, it
// returns an ondemmand::number instance.
//
// An ondemand::number instance may contain an integer value or a floating-point value. Thus it is a
// dynamically typed number. Before accessing the value, you must determine the detected type:
//
// - number.get_number_type() has value number_type::signed_integer if we have an integer in 
//   [-9223372036854775808,9223372036854775808). You can recover the value by the get_int64()
//   method applied on the ondemand::number instance. When number.get_number_type() has value
//   number_type::signed_integer, you also have that number.is_int64_t is true. Calling get_int64()
//   on the ondemand::number instance when number.get_number_type() is not number_type::signet_integer
//   is unsafe. You may replace get_int64() by a cast to a int64_t value.
// - number.get_number_type() has value number_type::unsigned_integer if we have a integer in 
//   [9223372036854775808,18446744073709551616). You can recover the value by the get_uint64()
//   method applied on the ondemand::number instance. When number.get_number_type() has value 
//   number_type::unsigned_integer, you also have that number.is_uint64() is true. Calling get_uint64()
//   on the ondemand::number instance when number.get_number_type() is not number_type::unsigned_integer
//   is unsafe. You may replace get_uint64() by a cast to a uint64_t value.
// - number.get_number_type() has value number_type::floating_point_number if we have a floating-point
//   (binary64) number. You can recover the value by the get_double() method applied on the 
//   ondemand::number instance. When number.get_number_type() has value number_type::floating_point_number,
//   you also have that number.is_double() is true. Calling get_double() on the ondemand::number
//   instance when number.get_number_type() is not number_type::floating_point_number is unsafe. 
//   You may replace get_double() by a cast to a double value.
//
// You must check the type before accessing the value: it is an error to call get_int64() when
// number.get_number_type() is not number_type::signed_integer and when number.is_int64() is false.
// You are responsible for this check as the user of the library.
//
// The get_number() function is designed with performance in mind. When calling get_number(), you
// scan the number string only once, determining effiiently the type and storing it in an efficient manner.
//
// Consider the following example:

#include <iostream>
#include <simdjson.h>

void dynamic_number_types()
{
    simdjson::ondemand::parser parser;
    simdjson::padded_string docdata = R"([1.0, 3, 1, 3.1415, -13231232, 9999999999999999999])"_padded;
    simdjson::ondemand::document doc = parser.iterate(docdata);
    simdjson::ondemand::array arr = doc.get_array();

    for (simdjson::ondemand::value val : arr)
    {
        std::cout << val << " | ";
        std::cout << std::boolalpha << "negative : " << val.is_negative() << " | ";
        std::cout << "is_integer : " << val.is_integer() << " | ";
        simdjson::ondemand::number num = val.get_number();
        simdjson::ondemand::number_type t = num.get_number_type();

        switch(t)
        {
            case simdjson::ondemand::number_type::signed_integer:
                std::cout << "integer : " << int64_t(num) << " | ";
                std::cout << "integer : " << num.get_int64() << std::endl;
                break;
            case simdjson::ondemand::number_type::unsigned_integer:
                std::cout << "large 64-bit integer : " << uint64_t(num) << " | ";
                std::cout << "large 64-bit integer : " << num.get_uint64() << std::endl;
                break;
            case simdjson::ondemand::number_type::floating_point_number:
                std::cout << "float : " << double(num) << " | ";
                std::cout << "float : " << num.get_double() << std::endl;
                break;
        }
    }
}

int main()
{
    dynamic_number_types();

    return 0;
}