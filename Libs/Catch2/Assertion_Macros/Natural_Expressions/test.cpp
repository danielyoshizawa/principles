// Assertion Macros
// Most test frameworks have a large collection of assertion macros to capture
// all possible conditional forms(_EQUALS, _NOTEQUALS, _GREATER_THAN, etc).
// Catch is different, because it decomposes natural C-Style conditional expressions
// most of these forms are reduced to one or two that you will use all the time.
// That said there is a rich set of auxiliary macros as well.

// Natural Expressions
// The REQUIRE family of macros tests an expression and aborts the test case if it fails.
// The CHECK family are equivalent but execution continues in the same test case even if
// the assertion fails. This is useful if you have a series of essentially orthogonal
// assertions and it is useful to see all the results rather than stoppping at the first
// failure.
//
// REQUIRE(expression)
// CHECK(expression)
//
// Evaluates the expression and records the result. If an exception is thrown, it is caught,
// reported, and counted as a failure. These are the macros you will use most of the time.
//
// Examples
//
// CHECK(std == "string value");
// CHECK( thisReturnsTrue() );
// REQUIRE( i == 42 );
//
// Expressions prefixed with ! cannot be decomposed. If you have a type that is convertible
// to boll and you want to assert that it evaluates to false, use the two forms below:
//
// REQUIRE_FALSE(expression)
// CHECK_FALSE(expression)
//
// Note that there is no reason to use these formas for plain bool variables, because there is no
// added value in decomposing them.
//
// Example
//
// Status ret = someFunction();
// REQUIRE_FALSE(ret); // ret must evaluate to false, and Catch2 will print
//                     // out the value of ret if possibly
//
// Other limitations
// Note that expressions containing either of the binary logical operator, && or ||, cannot
// be decomposed and will not compile. The reason behind this is that it is impossible to
// overload && and || in a way that keeps their short-circuiting semantics, and expressions
// decomposition relies on overloaded operators to work.
// Simple example of an issue with overloading binary logical operators is a common pointer idiom,
// p && p->foo == 2. Using the built-in && operator, p is only dereferenced if it is not null.
// With overloaded &&, p is always dereferenced, thus causing a segfault if p == nullptr.
//
// If you want to test expression that contains && or ||, you have two options.
// - Enclose it in parentheses. Parentheses force evaluation of the expression before the expression
//   decomposition can touch it, and thus it cannot be used.
// - Rewrite the expression. REQUIRE(a == 1 && b == 2) can always be split into REQUIRE(a == 1);
//   REQUIRE(b == 2);. Alternatively, if this is  common pattern in your tests, think about using
//   Matchers, instead. There is no simple rewrite rule for ||, but I generally believe that if
//   you have || in your test expression, you should rethink your tests.

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Natural Expressions Check", "[NaturalExpressions]") {
    CHECK(false); // Will continue the test
    CHECK(true);
};

TEST_CASE("Natural Expressions Require", "[NaturalExpressions]") {
    REQUIRE(false); // Will stop the test
    REQUIRE(true); // Will not execute
};

TEST_CASE("Natural Expressions Not Assertions", "[NaturalExpressions]") {
    CHECK_FALSE(false);
    REQUIRE_FALSE(false);
};
