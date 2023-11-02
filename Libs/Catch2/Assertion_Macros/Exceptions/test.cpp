// Exceptions
//
// - REQUIRE_NOTHROW( expression )
// - CHECK_NOTHROW( expression )
//
// Expects that no exception is thrown during evaluation of the expression
//
// - REQUIRE_THROWS( expression )
// - CHECK_THROWS( expression )
//
/// Expects that an exception (of any type) is be thrown during evaluation of
// the expression
//
// - REQUIRE_THROWS_AS( expression, exception type )
// - CHECK_THROWS_AS( expression, exception type )
//
// Expects that an exception of the specified type is thrown during evaluation
// of the expression. Note that the exception is extended with const& and
// you should not include it yourself.
//
// - REQUIRE_THROWS_WITH( expression, string or string matcher)
// - CHECK_THROWS_WITH( expression, string or string matcher)
//
// Expects that an exception is thrown that, when converting to a string,
// matches the string or string matcher provided
//
// Example
//
// REQUIRE_THROWS_WITH( openThePodBayDoors(), Contains("afraid") && Contains("can't do that"));
// REQUIRE_THROWS_WITH( dismantleHal(), "My mind is going");
//
// - REQUIRE_THROWS_MATCHER(expression, exception type, matcher for given exception type)
// - CHECK_THROWS_MATCHER(expression, exception type, matcher for given exception type)
//
// Expects that exception of exception type is thrown and it matches provided matcher
//
// Please note that the THROW family of assertions expects to be passed a single expression,
// not a statement or series of statements. If you want to check a more complicated sequence of
// operations, you can use a C++11 lambda function
//
// REQUIRE_NOTHROW([&]() {
//    int i = 1;
//    int j = 2;
//    auto k = i + j;
//    if (k == 3) {
//      throw 1;
//    }
// }());

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <iostream>
#include <exception>

void noThrow() noexcept
{
    std::cout << "I'll never get here if you dont change the code" << std::endl;
};

void willThrow()
{
    throw "I'm an exception and I'm ok with it";
}

void runtimeErrorException()
{
    throw std::runtime_error("Oh Boy, something went wrong");
}

TEST_CASE("Exceptions No Throw", "[Exceptions]")
{
    CHECK_NOTHROW(noThrow());
    REQUIRE_NOTHROW(noThrow());
}

TEST_CASE("Exceptions Throws", "[Exceptions]")
{
    CHECK_THROWS(willThrow());
    REQUIRE_THROWS(willThrow());
}

TEST_CASE("Exceptions Throws As", "[Exceptions]")
{
    CHECK_THROWS_AS(runtimeErrorException(), std::runtime_error);
    REQUIRE_THROWS_AS(runtimeErrorException(), std::runtime_error);
}

TEST_CASE("Exceptions Throw With", "[Exceptions]")
{
    CHECK_THROWS_WITH(runtimeErrorException(), Catch::Matchers::ContainsSubstring("Oh Boy"));
    REQUIRE_THROWS_WITH(runtimeErrorException(), Catch::Matchers::ContainsSubstring("Oh Boy"));
}