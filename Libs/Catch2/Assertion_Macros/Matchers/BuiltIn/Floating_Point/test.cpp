// Floating point matchers
// Catch2 provides 4 matchers that target floating point numbers, these are:
// - WithAbs(double target, double margin)
// - WithULP(FloatingPoint target, uint64_t maxUlpDiff)
// - WithRel(FloatingPoint target, FloatingPoint eps)
// - IsNaN()
// 
// WithinRel matcher was introduced in Catch2 2.10.0
// IsNan matcher was introduced in Catch2 3.3.2
//
// The first serve to compare two floating point numbers.
//
// IsNaN then does exactly what it says on the tin. It matches the input if it is a Nan (Not a Number).
// The advantage of using it over just plain REQUIRE(std::isnan(x)), is that if the check fails,
// with REQUIRE you won't see the valur of x, but with REQUIRE_THAT(x, IsNan()), you will.
//
// We covered floating point comparisons already at 
// Libs/Catch2/Assertion_Macros/Floating_Point_Comparisons
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <cmath>

TEST_CASE("Floating Point Comparison", "[FloatingPoint]")
{
    REQUIRE_THAT(1.0, Catch::Matchers::WithinAbs(1.2, 0.2));
    REQUIRE_THAT(1.0, Catch::Matchers::WithinRel(1.1, 0.1));
    REQUIRE_THAT(-0.f, Catch::Matchers::WithinULP(0.f, 0));
    REQUIRE_THAT(std::nan("Not a Number"), Catch::Matchers::IsNaN());
 };
