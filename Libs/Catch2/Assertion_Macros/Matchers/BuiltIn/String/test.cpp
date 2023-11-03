// Built-in matchers
// Every matcher provided by Catch2 is split into 2 parts, a factory function that lives in the
// Catch::Matchers namespace, and the actual matcher type that is in some deeper namespace and
// should not be used by the user. In the examples above, we used Catch::Matchers::Contains.
// This is the factory function for the Catch::Matchers::StdString::ContainsMatcher types
// that does the actual matching.
//
// Out of the box, Catch2 provides the following matchers:
//
// std::string matchers
// Catch2 provides 5 different matchers that work with std::string
// - StartsWith(std::string str, CaseSensitive)
// - EndsWith(std::string str, CaseSensitive)
// - ContainsSubstring(std::string str, CaseSensitive)
// - Equals(std::string str, CaseSensitive)
// - Matches(std::string str, CaseSensitive)
//
// The first three should be fairly self-explanatory, they succeed if the argument starts with str,
// ends with str, or contains str somewhere inside it.
//
// The Equals matcher matches a string if (and only if) the argument string is equal to str.
//
// Finally, the Matches matchers performs an ECMAScript regex match using str against the argument
// string. It is important to know that the match is performed against the string as a whole, meaning
// that the regex "abc" will not match input string "abcd". To match "abcd", you need to use
// e.g. "abc.*" as your regex.
//
// The second argument sets whether the matching should be case-sensitive or not. By default,
// it is case-sensitive.
//
// std::string matchers live in catch2/matchers/catch_matchers_string.hpp

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("Starts, Ends and Contains", "[String]")
{
    CHECK_THAT("Some very important text that must be present in the program",
               Catch::Matchers::StartsWith("Some very important") &&
                   Catch::Matchers::EndsWith("in the program") &&
                   Catch::Matchers::ContainsSubstring("must"));
};

TEST_CASE("Equals, I mean, exactly equal", "[String]"){
    REQUIRE_THAT("This one cant be out", Catch::Matchers::Equals("This one cant be out"));
    REQUIRE_THAT("This one cant be out", !Catch::Matchers::Equals("This one can be out"));
};

TEST_CASE("Matches using Regex", "[String]"){
    REQUIRE_THAT("Some Alphanumeric Pattern 123", Catch::Matchers::Matches("^[a-zA-Z0-9 ]*$"));
    REQUIRE_THAT("Some Non-Alphanumeric &*&/ Pattern 123", !Catch::Matchers::Matches("^[a-zA-Z0-9 ]*$"));
};
