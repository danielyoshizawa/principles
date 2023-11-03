// Miscellaneous matchers
// Catch2 also provides some matchers and matcher utilities that do not
// quite fir into other categories.
//
// The first one of them is the Predicate(Callable pred, std::string description) matcher.
// It creates a matcher object that calls pred for the provided argument.
// The description argument allows users to set what the resulting matcher should self-describe
// as if required.
//
// Do note that you will need to explicitly specify the type of the argument, like in this example:
// REQUIRE_THAT("Hello olleH",
//              Predicate<std::string>(
//                  [](std::string const& str) -> bool { return str.front() == std.back(); },
//                  "First and last character should be equal"
// )
//);
//
// The predicte matcher lives in catch2/matchers/catch_matchers_predicate.hpp
//
// The other miscellaneous matcher utility is exception matching.
//
// Matching exceptions
// Catch2 provides a utility macro for asserting that an expression throws exceptions of specific
// type, and that exception has desired properties.
// The macro is REQUIRE_THROWS_MATCH(expr, ExceptionType, Matcher)
//
// REQUIRE_THROWS_MATCH macro lives in catch2/matchers/catch_matchers.hpp
//
// Catch2 currently provides two matchers for exceptions. These are:
// - Message(std::string message)
// - MessageMatches(Matcher matcher)
//
// MessageMatches was introduced in Catch2 3.3.0
//
// Message checks that the exception's message, as returned from what is exactly equal to message.
// MessageMatches applies the provided matcher on the exception's message, as returned from what.
// This is useful in conjunction with the std::string matchers (e.g. StartsWith)
//
// Example use:
// REQUIRE_THROWS_MATCHES(throwsDerivedException(), DerivedException, Message("DerivedException::what"));
// REQUIRE_THROWS_MATCHES(throwsDerivedException(), DerivedException, MessageMatches(StartsWith("DerivedExceptions")));
//
// Note that DerivedException in the example above has to derive from std::exception for the example to work
//
// The exception message matcher lives in catch2/matchers/catch_matchers_exception.hpp

// We covered Exception matchers in Libs/Catch2/Assertion_Macros/Exceptions
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_predicate.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <exception>

void throwsDerivedException()
{
    throw std::runtime_error("DerivedException::what");
};

TEST_CASE("Predicate", "[Miscellaneous]")
{
    REQUIRE_THAT("Hello olleH",
                 Catch::Matchers::Predicate<std::string>(
                     [](std::string const &str) -> bool
                     {
                         return str.front() == str.back();
                     },
                     "First and last character should be equal"));
};

TEST_CASE("Exception", "[Miscellaneous]")
{
    REQUIRE_THROWS_MATCHES(throwsDerivedException(),
                           std::runtime_error,
                           Catch::Matchers::Message("DerivedException::what"));
    REQUIRE_THROWS_MATCHES(throwsDerivedException(),
                           std::runtime_error,
                           Catch::Matchers::MessageMatches(
                               Catch::Matchers::StartsWith("DerivedException")));
};