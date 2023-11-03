// Matchers
// Matchers, as popularized by the Hamcrest framework are an alternative way to write assertions,
// useful for tests where you work with complex types or need to assert more complex properties.
// Matchers are easily composable and users can write their own and combine them with the
// Catch2-provided matchers seamlessly
//
// Using Matchers
// Matchers are most commonly used in tandem with the REQUIRE_THAT or CHECK_THAT macros.
// The REQUIRE_THAT macro takes two arguments, the first one is the input (object/value) to test,
// the second argument is the matcher itself.
//
// For example, to assert that a string ends with the "as a service" substring, you can write
// the following assertion.
//
// using Catch::Matchers::EndsWith;
// REQUIRE_THAT( getSomething(), EndsWith("as a service"));
//
// Individual matchers can also be combined using the C++ logical operators,
// that is &&, || and !, like so:
//
// using Catch::Matchers::EndsWith;
// using Catch::Matchers::ContainsSubstring;
// REQUIRE_THAT( getSomeString(),
//               EndsWith("as a service") && ContainsSubstring("web scale"));
//
// The example above asserts that the string returned from getSomeString both ends with the suffix
// "as a service" and contains the string "web scale" somewhere.
// Both of the string matchers used in the examples above live in the catch_matchers_string.hpp
// header, so to compile the code above also requires
// #include <catch2/matchers/catch_matchers_string.hpp>
//
// IMPORTANT: The combining operators do not take ownership of the matcher objects being combined.
// This means that if you store combined matcher object, you have to ensure that the matchers being
// combined outlive its last use. What this means is that the following code
// leads to a use-after-free (UAF):
//
// #include <catch2/catch_test_macros.hpp>
// #include <catch2/matchers/catch_matchers_string.hpp>
//
// TEST_CASE("Bugs, bugs, bugs", "[Bugs]") {
//   std::string str = "Bugs as a service";
//
//   auto match_expression = Catch::Matchers::EndsWith("as a service") ||
//     (Catch::Matchers::StartsWith("Big data") && !Catch::Matchers::ContainsSubstrings("web scale"));
//   REQUIRE_THAT(str, match_expression);
// }
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

using Catch::Matchers::EndsWith;
using Catch::Matchers::ContainsSubstring;

TEST_CASE("Matchers in use", "[Matchers]"){
    REQUIRE_THAT("Some important text about web scale as a service",
                 EndsWith("as a service") &&
                     ContainsSubstring("web scale"));
};